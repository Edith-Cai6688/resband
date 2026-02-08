/*
 * tension.c
 *
 *  Created on: Nov 12, 2025
 *      Author: Stank
 */

#include "tension.h"
#include "config.h"
#include "CH57x_common.h"

// 弹力带参数
static BandParameters_t band_params = {
    .pound = 50,        // 默认50磅
    .length = 60,      // 默认60cm
    .zero_angle = 0,
    .calibrated = 0,
    .k_factor = 0.0f,
    .k = 20
};

// 训练统计参数
static TrainingStats_t training_stats = {
    .total_pulls = 0,
    .current_pull_duration = 0,
    .total_training_time = 0,
    .current_pull_start_time = 0,
    .is_pulling = 0,
    .max_tension = 0.0f,
    .average_tension = 0.0f
};

// 拉力阈值配置
static TensionThreshold_t tension_threshold = {
    .start_threshold = 2.0f,    // 2kgf开始计数
    .stop_threshold = 1.0f,     // 1kgf停止计数
    .min_duration = 1000        // 最小持续时间1秒
};

// 常量定义
#define WHEEL_RADIUS        0.0075f      // 轮子直径15mm
#define POUND_TO_NEWTON     4.448f      // 磅到牛顿的转换系数
#define GRAVITY_ACCEL       9.8f        // 重力加速

/*********************************************************************
 * @fn      TensionCalculator_Init
 *
 * @brief   初始化拉力计算模块
 */
void TensionCalculator_Init(void)
{
    // 初始化默认参数
    band_params.pound = 50;
    band_params.length = 60;
    band_params.zero_angle = 0;
    band_params.calibrated = 0;

    float max_stretch_length = band_params.length / 100.0f;  // 转换为米
    float max_force_N = band_params.pound * POUND_TO_NEWTON;
    band_params.k_factor = max_force_N / max_stretch_length;
}

/*********************************************************************
 * @fn      TensionCalculator_SetParameters
 *
 * @brief   设置弹力带参数
 *
 * @param   pound - 磅数
 * @param   length - 长度(cm)
 */
void TensionCalculator_SetParameters(uint16_t pound, uint16_t length)
{
    band_params.pound = pound;
    band_params.length = length;

    float max_stretch_length = band_params.length / 100.0f;  // 转换为米
    float max_force_N = band_params.pound * POUND_TO_NEWTON;
    band_params.k_factor = max_force_N / max_stretch_length;

    PRINT("弹力带参数更新: %d磅, %dcm\n", pound, length);
}

/*********************************************************************
 * @fn      TensionCalculator_CalibrateZero
 *
 * @brief   校准零位（弹力带松弛状态）
 *
 * @param   current_angle - 当前角度值
 */
void TensionCalculator_CalibrateZero(uint16_t current_angle)
{
    band_params.zero_angle = current_angle;
    band_params.calibrated = 1;

    PRINT("零位校准完成: 0x%04X\n", current_angle);
}

/*********************************************************************
 * @fn      CalculateRelativeAngle
 *
 * @brief   计算相对于零位的角度变化（弧度）
 *
 * @param   current_angle - 当前角度值
 * @return  相对角度(弧度)
 */
static float CalculateRelativeAngle(uint16_t current_angle)
{
    if (!band_params.calibrated) {
        return 0.0f;
    }

    // 计算原始角度差
    int32_t angle_diff = (int32_t)current_angle - (int32_t)band_params.zero_angle;

    // 处理角度循环 (AS5600是12位，0-4095)
    if (angle_diff > 2048) {
        angle_diff -= 4096;
    } else if (angle_diff < -2048) {
        angle_diff += 4096;
    }

    // 转换为弧度：AS5600的4096对应360度
    float angle_rad = (angle_diff * 2.0f * 3.14159f) / 4096.0f;

    return angle_rad;
}

/*********************************************************************
 * @fn      TensionCalculator_CalculateTension
 *
 * @brief   计算拉力值(N)
 *
 * @param   current_angle - 当前角度值
 * @return  拉力值(牛顿)
 */
float TensionCalculator_CalculateTension(uint16_t current_angle)
{
    // 计算相对角度(弧度)
    float relative_angle_rad = CalculateRelativeAngle(current_angle);

    // 计算拉伸长度 (基于轮子半径和角度)
    float stretch_length = WHEEL_RADIUS * fabsf(relative_angle_rad) * 2;

    float tension_N = band_params.k_factor * stretch_length * band_params.k;

    // 转换为千克力 (可选，根据需求)
    float tension_kgf = tension_N / GRAVITY_ACCEL;

    // 限制最小值
    if (tension_kgf < 0) {
        tension_kgf = 0;
    }

    return tension_kgf;
}

/*********************************************************************
 * @fn      TensionCalculator_GetTensionValue
 *
 * @brief   获取整型拉力值(用于传输)
 *
 * @param   current_angle - 当前角度值
 * @return  拉力值(放大100倍，保留2位小数)
 */
uint16_t TensionCalculator_GetTensionValue(uint16_t current_angle)
{
    float tension_kgf = TensionCalculator_CalculateTension(current_angle);


    // 放大100倍转换为整型，保留2位小数
    uint16_t tension_value = (uint16_t)(tension_kgf * 100.0f);

    // 限制最大值 (655.35N)
    if (tension_value > 65535) {
        tension_value = 65535;
    }

    return tension_value;
}

/*********************************************************************
 * @fn      TensionCalculator_UpdateTrainingStats
 *
 * @brief   更新训练统计数据（需要周期性调用）
 *
 * @param   current_angle - 当前角度值
 */
void TensionCalculator_UpdateTrainingStats(uint16_t current_angle)
{
    static uint32_t last_update_time = 0;
    uint32_t current_time = TMOS_GetSystemClock();

    // 计算时间间隔
    uint32_t time_elapsed = current_time - last_update_time;
    if (time_elapsed < 10) { // 最小更新间隔10ms
        return;
    }

    last_update_time = current_time;

    // 计算当前拉力
    float current_tension = TensionCalculator_CalculateTension(current_angle);

    // 更新最大拉力
    if (current_tension > training_stats.max_tension) {
        training_stats.max_tension = current_tension;
    }

    // 拉力状态检测
    if (!training_stats.is_pulling) {
        // 未在拉动状态，检测是否开始拉动
        if (current_tension >= tension_threshold.start_threshold) {
            training_stats.is_pulling = 1;
            training_stats.current_pull_start_time = current_time;
            training_stats.current_pull_duration = 0;
            PRINT("开始拉动: %.1f kgf\n", current_tension);
        }
    } else {
        // 正在拉动状态，检测是否停止拉动
        if (current_tension <= tension_threshold.stop_threshold) {
            training_stats.is_pulling = 0;
            uint32_t pull_duration = current_time - training_stats.current_pull_start_time;

            // 只有持续时间超过阈值才计数
            if (pull_duration >= tension_threshold.min_duration) {
                training_stats.total_pulls++;
                training_stats.total_training_time += pull_duration;

                pull_duration = pull_duration / 1000;

                // 记录本次拉动的时长
                training_stats.current_pull_duration = pull_duration;

                PRINT("完成第%d次拉动: 时长=%lums, 最大拉力=%.1fkgf\n",
                      training_stats.total_pulls, pull_duration, training_stats.max_tension);


            } else {
                PRINT("拉动时间过短: %lums < %lums\n", pull_duration, tension_threshold.min_duration);
            }
        }
    }
}

/*********************************************************************
 * @fn      TensionCalculator_GetTrainingStats
 *
 * @brief   获取训练统计数据
 *
 * @param   stats - 训练统计数据结构体指针
 */
void TensionCalculator_GetTrainingStats(TrainingStats_t *stats)
{
    if (stats != NULL) {
        memcpy(stats, &training_stats, sizeof(TrainingStats_t));

        // 计算平均拉力（如果有拉动次数）
        if (training_stats.total_pulls > 0) {
            stats->average_tension = training_stats.max_tension / training_stats.total_pulls;
        } else {
            stats->average_tension = 0.0f;
        }
    }
}

/*********************************************************************
 * @fn      TensionCalculator_ResetTrainingStats
 *
 * @brief   重置训练统计数据
 */
void TensionCalculator_ResetTrainingStats(void)
{
    memset(&training_stats, 0, sizeof(TrainingStats_t));
    training_stats.current_pull_start_time = TMOS_GetSystemClock();

    PRINT("训练数据已重置\n");
}

/*********************************************************************
 * @fn      TensionCalculator_GetCurrentPullDuration
 *
 * @brief   获取当前正在进行的拉动时长(ms)
 *
 * @return  当前拉动时长，如果未在拉动状态返回0
 */
uint32_t TensionCalculator_GetCurrentPullDuration(void)
{
    if (training_stats.is_pulling) {
        return TMOS_GetSystemClock() - training_stats.current_pull_start_time;
    }
    return 0;
}

/*********************************************************************
 * @fn      TensionCalculator_IsPulling
 *
 * @brief   检查是否正在拉动状态
 *
 * @return  1-正在拉动, 0-未拉动
 */
uint8_t TensionCalculator_IsPulling(void)
{
    return training_stats.is_pulling;
}

/*********************************************************************
 * @fn      TensionCalculator_GetTotalPulls
 *
 * @brief   获取总拉动次数
 *
 * @return  总拉动次数
 */
uint32_t TensionCalculator_GetTotalPulls(void)
{
    return training_stats.total_pulls;
}

/*********************************************************************
 * @fn      TensionCalculator_GetTotalTrainingTime
 *
 * @brief   获取总训练时间(ms)
 *
 * @return  总训练时间
 */
uint32_t TensionCalculator_GetTotalTrainingTime(void)
{
    return training_stats.total_training_time;
}
