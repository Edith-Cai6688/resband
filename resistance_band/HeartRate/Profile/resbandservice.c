/********************************** (C) COPYRIGHT *******************************
 * File Name          : heartrateservice.C
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/11
 * Description        : 心率服务
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "config.h"
#include "battservice.h"
#include "resbandservice.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

// Position of heart rate measurement value in attribute array
#define RESBAND_MEAS_VALUE_POS    2
#define RESBAND_TRAINING_DATA_VALUE_POS 11  // 训练数据特征值位置
/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

// 添加参数保存变量
static uint16_t bandPound = 50;     // 默认50磅
static uint16_t bandLength = 60;   // 默认100cm

// Heart rate service
const uint8_t resBandServUUID[ATT_BT_UUID_SIZE] = {
    LO_UINT16(RESBAND_SERV_UUID), HI_UINT16(RESBAND_SERV_UUID)};

// Heart rate measurement characteristic
const uint8_t resBandMeasUUID[ATT_BT_UUID_SIZE] = {
    LO_UINT16(RESBAND_MEAS_UUID), HI_UINT16(RESBAND_MEAS_UUID)};

// Command characteristic
const uint8_t resBandCommandUUID[ATT_BT_UUID_SIZE] = {
    LO_UINT16(RESBAND_CTRL_PT_UUID), HI_UINT16(RESBAND_CTRL_PT_UUID)};

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

static resBandServiceCB_t resBandServiceCB;

/*********************************************************************
 * Profile Attributes - variables
 */

// Heart Rate Service attribute
static const gattAttrType_t resBandService = {ATT_BT_UUID_SIZE, resBandServUUID};

// Heart Rate Measurement Characteristic
// Note characteristic value is not stored here
static uint8_t       resBandMeasProps = GATT_PROP_NOTIFY;
static uint8_t       resBandMeas = 0;
static gattCharCfg_t resBandMeasClientCharCfg[GATT_MAX_NUM_CONN];

// Sensor Location Characteristic
static uint8_t resBandSensLocProps = GATT_PROP_READ;
static uint8_t resBandSensLoc = 0;

// Command Characteristic
static uint8_t resBandCommandProps = GATT_PROP_WRITE;
static uint8_t resBandCommand = 0;

// 参数特征值
static uint8_t resBandParamsProps = GATT_PROP_READ | GATT_PROP_WRITE;  // 可读可写
static uint8_t resBandParams[4] = {0};  // 4字节存储参数

/*********************************************************************
 * Profile Attributes - Table
 */

static gattAttribute_t resBandAttrTbl[] = {
    // 定义服务的UUID为0xABCD
    {
        {ATT_BT_UUID_SIZE, primaryServiceUUID}, /* type */
        GATT_PERMIT_READ,                       /* permissions */
        0,                                      /* handle */
        (uint8_t *)&resBandService            /* pValue */
    },

    // 定义特征（notify）
    {
        {ATT_BT_UUID_SIZE, characterUUID},
        GATT_PERMIT_READ,
        0,
        &resBandMeasProps
    },

    // 定义特征值
    {
        {ATT_BT_UUID_SIZE, resBandMeasUUID},
        0,   // 手机端可以notify
        0,
        &resBandMeas
    },

    // 定义notify的CCCD（手机可以控制接收notify）
    {
        {ATT_BT_UUID_SIZE, clientCharCfgUUID},
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8_t *)&resBandMeasClientCharCfg
    },

    // // 定义命令特征
    // {
    //     {ATT_BT_UUID_SIZE, characterUUID},
    //     GATT_PERMIT_READ,
    //     0,
    //     &resBandCommandProps
    // },

    // // 定义命令特征值
    // {
    //     {ATT_BT_UUID_SIZE, resBandCommandUUID},
    //     GATT_PERMIT_WRITE,
    //     0,
    //     &resBandCommand
    // },

};

#define RESBAND_NUM_ATTRS (sizeof(resBandAttrTbl) / sizeof(gattAttribute_t))
/*********************************************************************
 * LOCAL FUNCTIONS
 */
static uint8_t   resBand_ReadAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                      uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                      uint16_t maxLen, uint8_t method);
static bStatus_t resBand_WriteAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                       uint8_t *pValue, uint16_t len, uint16_t offset,
                                       uint8_t method);

/*********************************************************************
 * PROFILE CALLBACKS
 */
// Heart Rate Service Callbacks
gattServiceCBs_t resBandCBs = {
    resBand_ReadAttrCB,  // Read callback function pointer
    resBand_WriteAttrCB, // Write callback function pointer
    NULL                   // Authorization callback function pointer
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      ResBand_AddService
 *
 * @brief   Initializes the Heart Rate service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 *
 * @return  Success or Failure
 */
bStatus_t ResBand_AddService(uint32_t services)
{
    uint8_t status = SUCCESS;

    // Initialize Client Characteristic Configuration attributes
    GATTServApp_InitCharCfg(INVALID_CONNHANDLE, resBandMeasClientCharCfg);

    if(services & RESBAND_SERVICE)
    {
        // Register GATT attribute list and CBs with GATT Server App
        status = GATTServApp_RegisterService(resBandAttrTbl,
                                             GATT_NUM_ATTRS(resBandAttrTbl),
                                             GATT_MAX_ENCRYPT_KEY_SIZE,
                                             &resBandCBs);
    }

    return (status);
}

/*********************************************************************
 * @fn      ResBand_Register
 *
 * @brief   Register a callback function with the Heart Rate Service.
 *
 * @param   pfnServiceCB - Callback function.
 *
 * @return  None.
 */
extern void ResBand_Register(resBandServiceCB_t pfnServiceCB)
{
    resBandServiceCB = pfnServiceCB;
}

/*********************************************************************
 * @fn      ResBand_SetParameter
 *
 * @brief   Set a Heart Rate parameter.
 *
 * @param   param - Profile parameter ID
 * @param   len - length of data to right
 * @param   value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16_t will be cast to
 *          uint16_t pointer).
 *
 * @return  bStatus_t
 */
bStatus_t ResBand_SetParameter(uint8_t param, uint8_t len, void *value)
{
    bStatus_t ret = SUCCESS;
    switch(param)
    {
        case RESBAND_MEAS_CHAR_CFG:
            // Need connection handle
            //resBandMeasClientCharCfg.value = *((uint16_t*)value);
            break;

        case RESBAND_SENS_LOC:
            resBandSensLoc = *((uint8_t *)value);
            break;

        default:
            ret = INVALIDPARAMETER;
            break;
    }

    return (ret);
}

/*********************************************************************
 * @fn      ResBand_GetParameter
 *
 * @brief   Get a Heart Rate parameter.
 *
 * @param   param - Profile parameter ID
 * @param   value - pointer to data to get.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16_t will be cast to
 *          uint16_t pointer).
 *
 * @return  bStatus_t
 */
bStatus_t ResBand_GetParameter(uint8_t param, void *value)
{
    bStatus_t ret = SUCCESS;

    switch(param)
    {
        case RESBAND_MEAS_CHAR_CFG:
            // 需要连接句柄
            break;

        case RESBAND_SENS_LOC:
            *((uint8_t *)value) = resBandSensLoc;
            break;

        case RESBAND_COMMAND:
            *((uint8_t *)value) = resBandCommand;
            break;

        case RESBAND_PARAMS:  // 新增：获取参数
            if(value != NULL)
            {
                // 返回4字节参数数据
                uint8_t *pData = (uint8_t *)value;
                pData[0] = LO_UINT16(bandPound);
                pData[1] = HI_UINT16(bandPound);
                pData[2] = LO_UINT16(bandLength);
                pData[3] = HI_UINT16(bandLength);
            }
            break;

        default:
            ret = INVALIDPARAMETER;
            break;
    }

    return ret;
}

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
bStatus_t ResBand_MeasNotify(uint16_t connHandle, attHandleValueNoti_t *pNoti)
{
    uint16_t value = GATTServApp_ReadCharCfg(connHandle, resBandMeasClientCharCfg);

    // If notifications enabled
    if(value & GATT_CLIENT_CFG_NOTIFY)
    {
        // Set the handle
        pNoti->handle = resBandAttrTbl[RESBAND_MEAS_VALUE_POS].handle;

        // Send the notification
        return GATT_Notification(connHandle, pNoti, FALSE);
    }

    return bleIncorrectMode;
}

// bStatus_t ResBand_TrainingDataNotify(uint16_t connHandle, attHandleValueNoti_t *pNoti)
// {
//     uint16_t value = GATTServApp_ReadCharCfg(connHandle, resBandTrainingClientCharCfg);

//     if(value & GATT_CLIENT_CFG_NOTIFY)
//     {
//         pNoti->handle = resBandAttrTbl[RESBAND_TRAINING_DATA_VALUE_POS].handle;
//         return GATT_Notification(connHandle, pNoti, FALSE);
//     }

//     return bleIncorrectMode;
// }

/*********************************************************************
 * @fn          resBand_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 *
 * @return      Success or Failure
 */
static uint8_t resBand_ReadAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                    uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                    uint16_t maxLen, uint8_t method)
{
    bStatus_t status = SUCCESS;

    uint16_t uuid = BUILD_UINT16(pAttr->type.uuid[0], pAttr->type.uuid[1]);

    // Make sure it's not a blob operation (no attributes in the profile are long)
    if(offset > 0)
    {
        return (ATT_ERR_ATTR_NOT_LONG);
    }

    switch(uuid)
    {

        // case RESBAND_PARAMS_UUID:  // 参数特征值
        //     if(maxLen >= 4)
        //     {
        //         *pLen = 4;
        //         // 小端格式返回当前参数
        //         pValue[0] = LO_UINT16(bandPound);
        //         pValue[1] = HI_UINT16(bandPound);
        //         pValue[2] = LO_UINT16(bandLength);
        //         pValue[3] = HI_UINT16(bandLength);
        //         PRINT("读取参数 - 磅数: %d, 长度: %dcm\n", bandPound, bandLength);
        //     }
        //     else
        //     {
        //         status = ATT_ERR_INSUFFICIENT_RESOURCES;
        //     }
        //     break;

        default:
            status = ATT_ERR_ATTR_NOT_FOUND;
            break;
    }

    return (status);
}

/*********************************************************************
 * @fn      resBand_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 *
 * @return  Success or Failure
 */
static bStatus_t resBand_WriteAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                       uint8_t *pValue, uint16_t len, uint16_t offset,
                                       uint8_t method)
{
    bStatus_t status = SUCCESS;

    uint16_t uuid = BUILD_UINT16(pAttr->type.uuid[0], pAttr->type.uuid[1]);
    switch(uuid)
    {
        case RESBAND_CTRL_PT_UUID:
            if(offset > 0)
            {
                status = ATT_ERR_ATTR_NOT_LONG;
            }
            else if(len != 1)
            {
                status = ATT_ERR_INVALID_VALUE_SIZE;
            }
            else
            {
                uint8_t command = pValue[0];
                *(pAttr->pValue) = command;

                // 支持多种命令
                switch(command)
                {
                    case RESBAND_COMMAND_ENERGY_EXP:
                        PRINT("收到能量重置命令\n");
                        (*resBandServiceCB)(RESBAND_COMMAND_SET);
                        break;

                    case RESBAND_COMMAND_CALIBRATE_ZERO:
                        PRINT("收到校准零位命令\n");
                        (*resBandServiceCB)(RESBAND_COMMAND_SET);
                        break;

                    case RESBAND_COMMAND_RESET_STATS:
                        PRINT("收到训练数据校准零位命令\n");
                        (*resBandServiceCB)(RESBAND_COMMAND_SET);
                        break;

                    default:
                        PRINT("未知命令: 0x%02X\n", command);
                        status = RESBAND_ERR_NOT_SUP;
                        break;
                }
            }
            break;

        case GATT_CLIENT_CHAR_CFG_UUID:
            // 接收到CCCD改变的信息（手机端启用notify）
            if(pAttr->pValue == (uint8_t *)&resBandMeasClientCharCfg) //识别任务，开始
            {
                status = GATTServApp_ProcessCCCWriteReq(connHandle, pAttr, pValue, len,
                                                        offset, GATT_CLIENT_CFG_NOTIFY);
                if(status == SUCCESS)
                {
                    uint16_t charCfg = BUILD_UINT16(pValue[0], pValue[1]);
                    (*resBandServiceCB)((charCfg == GATT_CFG_NO_OPERATION) ?
                                       RESBAND_MEAS_NOTI_DISABLED : RESBAND_MEAS_NOTI_ENABLED);
                }
            }
            break;

        default:
            status = ATT_ERR_ATTR_NOT_FOUND;
            break;
    }

    return (status);
}

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
void ResBand_HandleConnStatusCB(uint16_t connHandle, uint8_t changeType)
{
    // Make sure this is not loopback connection
    if(connHandle != LOOPBACK_CONNHANDLE)
    {
        // Reset Client Char Config if connection has dropped
        if((changeType == LINKDB_STATUS_UPDATE_REMOVED) ||
           ((changeType == LINKDB_STATUS_UPDATE_STATEFLAGS) &&
            (!linkDB_Up(connHandle))))
        {
            GATTServApp_InitCharCfg(connHandle, resBandMeasClientCharCfg);
        }
    }
}

/*********************************************************************
 * @fn      ResBand_GetBandParameters
 *
 * @brief   获取弹力带参数
 *
 * @param   pPound - 磅数指针
 * @param   pLength - 长度指针
 *
 * @return  None
 */
void ResBand_GetBandParameters(uint16_t *pPound, uint16_t *pLength)
{
    if(pPound) *pPound = bandPound;
    if(pLength) *pLength = bandLength;
}
/*********************************************************************
*********************************************************************/
