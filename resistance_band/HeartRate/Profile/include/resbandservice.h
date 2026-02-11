/********************************** (C) COPYRIGHT *******************************
 * File Name          : heartrateservice.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/11
 * Description        :
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef RESBANDSERVICE_H
#define RESBANDSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */


// ResBand serv uuid
#define RESBAND_SERV_UUID     0xABCD   // 自定义服务UUID
#define RESBAND_MEAS_UUID     0xABCE   // 自定义特征值UUID
#define RESBAND_CTRL_PT_UUID  0xABCF   // 自定义command uuid


// Heart Rate Service Parameters
#define RESBAND_MEAS                   0
#define RESBAND_MEAS_CHAR_CFG          1
#define RESBAND_SENS_LOC               2
#define RESBAND_COMMAND                3
#define RESBAND_PARAMS                 4  //特征参数值
#define RESBAND_TRAINING_DATA          5  // 新增训练数据特征


// Maximum length of heart rate measurement characteristic
#define RESBAND_MEAS_MAX                 (ATT_MTU_SIZE - 5)
#define RESBAND_TRAINING_DATA_LEN       8  // 训练数据长度8字节

// Values for flags
#define RESBAND_FLAGS_FORMAT_UINT16      0x01
#define RESBAND_FLAGS_CONTACT_NOT_SUP    0x00
#define RESBAND_FLAGS_CONTACT_NOT_DET    0x04
#define RESBAND_FLAGS_CONTACT_DET        0x06
#define RESBAND_FLAGS_ENERGY_EXP         0x08
#define RESBAND_FLAGS_RR                 0x10

// Values for sensor location
#define RESBAND_SENS_LOC_OTHER           0x00
#define RESBAND_SENS_LOC_CHEST           0x01
#define RESBAND_SENS_LOC_WRIST           0x02
#define RESBAND_SENS_LOC_FINGER          0x03
#define RESBAND_SENS_LOC_HAND            0x04
#define RESBAND_SENS_LOC_EARLOBE         0x05
#define RESBAND_SENS_LOC_FOOT            0x06

// Value for command characteristic
#define RESBAND_COMMAND_ENERGY_EXP       0x01
#define RESBAND_COMMAND_CALIBRATE_ZERO   0x02  // 校准零位命令
#define RESBAND_COMMAND_RESET_STATS      0x03  // 重置统计数据命令

// ATT Error code
// Control point value not supported
#define RESBAND_ERR_NOT_SUP              0x80



// Heart Rate Service bit fields
#define RESBAND_SERVICE                  0x00000001

// Callback events
#define RESBAND_MEAS_NOTI_ENABLED        1
#define RESBAND_MEAS_NOTI_DISABLED       2
#define RESBAND_COMMAND_SET              3
#define RESBAND_PARAMS_UPDATED           4
#define RESBAND_TRAINING_NOTI_ENABLED    5    // 训练数据通知启用
#define RESBAND_TRAINING_NOTI_DISABLED   6    // 训练数据通知禁用



/*********************************************************************
 * TYPEDEFS
 */

// Heart Rate Service callback function
typedef void (*resBandServiceCB_t)(uint8_t event);

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * Profile Callbacks
 */

/*********************************************************************
 * API FUNCTIONS
 */

/*
 * ResBand_AddService- Initializes the Heart Rate service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 */

extern bStatus_t ResBand_AddService(uint32_t services);

/*
 * ResBand_Register - Register a callback function with the
 *          Heart Rate Service
 *
 * @param   pfnServiceCB - Callback function.
 */

extern void ResBand_Register(resBandServiceCB_t pfnServiceCB);

/*
 * ResBand_SetParameter - Set a Heart Rate parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16_t will be cast to
 *          uint16_t pointer).
 */
extern bStatus_t ResBand_SetParameter(uint8_t param, uint8_t len, void *value);

/*
 * ResBand_GetParameter - Get a Heart Rate parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16_t will be cast to
 *          uint16_t pointer).
 */
extern bStatus_t ResBand_GetParameter(uint8_t param, void *value);

/*********************************************************************
 * @fn          ResBand_MeasNotify
 *
 * @brief       Send a notification containing a heart rate
 *              measurement.
 *
 * @param       connHandle - connection handle
 * @param       pNoti - pointer to notification structure
 *
 * @return      Success or Failure
 */
extern bStatus_t ResBand_MeasNotify(uint16_t connHandle, attHandleValueNoti_t *pNoti);

/*********************************************************************
 * @fn      CalculateRelativeAngle
 *
 * @brief   计算相对于零位的角度变化（弧度）
 *
 * @param   current_angle - 当前角度值
 * @return  相对角度(弧度)
 */
extern void ResBand_GetBandParameters(uint16_t *pPound, uint16_t *pLength);

/*********************************************************************
 * @fn          ResBand_HandleConnStatusCB
 *
 * @brief       Heart Rate Service link status change handler function.
 *
 * @param       connHandle - connection handle
 * @param       changeType - type of change
 *
 * @return      none
 */
extern void ResBand_HandleConnStatusCB(uint16_t connHandle, uint8_t changeType);

extern bStatus_t ResBand_TrainingDataNotify(uint16_t connHandle, attHandleValueNoti_t *pNoti);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* RESBANDSERVICE_H */
