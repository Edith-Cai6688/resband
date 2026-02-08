/*
 * tension.h
 *
 *  Created on: Nov 12, 2025
 *      Author: Stank
 */

#ifndef APP_INCLUDE_TENSION_H_
#define APP_INCLUDE_TENSION_H_

#include "stdint.h"
#include "math.h"

// 弹力带参数结构
typedef struct {
    uint16_t pound;     // 磅数
    uint16_t length;    // 长度(cm)
    uint16_t zero_angle;// 零位基准角度
    uint8_t calibrated; // 是否已校准
    float k_factor;
    float k;
} BandParameters_t;

// 训练统计结构体
typedef struct {
    uint32_t total_pulls;           // 总拉动次数
    uint32_t current_pull_duration; // 当前拉动时长(ms)
    uint32_t total_training_time;   // 总训练时间(ms)
    uint32_t current_pull_start_time; // 当前拉动开始时间
    uint8_t is_pulling;             // 是否正在拉动
    float max_tension;              // 最大拉力值(kgf)
    float average_tension;          // 平均拉力值(kgf)
} TrainingStats_t;

// 拉力阈值结构体
typedef struct {
    float start_threshold;  // 开始计数阈值(kgf)
    float stop_threshold;   // 停止计数阈值(kgf)
    uint32_t min_duration;  // 最小持续时间(ms)
} TensionThreshold_t;

// 函数声明
void TensionCalculator_Init(void);
void TensionCalculator_SetParameters(uint16_t pound, uint16_t length);
void TensionCalculator_CalibrateZero(uint16_t current_angle);
float TensionCalculator_CalculateTension(uint16_t current_angle);
uint16_t TensionCalculator_GetTensionValue(uint16_t current_angle);
void TensionCalculator_GetTrainingStats(TrainingStats_t *stats);
void TensionCalculator_ResetTrainingStats(void);
void TensionCalculator_UpdateTrainingStats(uint16_t current_angle);
uint32_t TensionCalculator_GetCurrentPullDuration(void);
uint8_t TensionCalculator_IsPulling(void);
uint32_t TensionCalculator_GetTotalPulls(void);
uint32_t TensionCalculator_GetTotalTrainingTime(void);


#endif /* APP_INCLUDE_TENSION_H_ */
