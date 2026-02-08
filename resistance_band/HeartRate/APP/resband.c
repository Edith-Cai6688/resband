/********************************** (C) COPYRIGHT *******************************
 * File Name          : heartrate.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2020/08/06
 * Description        : 心率计应用程序，初始化广播连接参数，然后广播，直至连接主机后，定时上传心率
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
#include "devinfoservice.h"
#include "resband.h"
#include "resbandservice.h"
#include "AS5600.h"
#include "tension.h"

/*********************************************************************
 * MACROS
 */


/*********************************************************************
 * CONSTANTS
 */

// Fast advertising interval in 625us units
#define DEFAULT_FAST_ADV_INTERVAL            32

// Duration of fast advertising duration in (625us)
#define DEFAULT_FAST_ADV_DURATION            30000

// Slow advertising interval in 625us units
#define DEFAULT_SLOW_ADV_INTERVAL            1600

// Duration of slow advertising duration in (625us) (set to 0 for continuous advertising)
#define DEFAULT_SLOW_ADV_DURATION            0

// How often to perform heart rate periodic event
#define DEFAULT_RESBAND_PERIOD             100

// Minimum connection interval (units of 1.25ms)
#define DEFAULT_DESIRED_MIN_CONN_INTERVAL    8

// Maximum connection interval (units of 1.25ms)
#define DEFAULT_DESIRED_MAX_CONN_INTERVAL    8

// Slave latency to use if parameter update request
#define DEFAULT_DESIRED_SLAVE_LATENCY        0

// Supervision timeout value (units of 10ms)
#define DEFAULT_DESIRED_CONN_TIMEOUT         100

// Delay of start connect paramter update
#define DEFAULT_CONN_PARAM_UPDATE_DELAY      1600

// Battery level is critical when it is less than this %
#define DEFAULT_BATT_CRITICAL_LEVEL          6

// Battery measurement period in (625us)
#define DEFAULT_BATT_PERIOD                  24000

// Some values used to simulate measurements
#define ANGLE_DEFAULT                          0x1234
#define ANGLE_MAX                            0xFFF
#define ENERGY_INCREMENT                     10
#define FLAGS_IDX_MAX                        7

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */


// ResBand测量数据订阅状态：TRUE=已订阅，FALSE=未订阅
static BOOL isResBandSubscribed = FALSE;
static BOOL isTrainingDataSubscribed = FALSE;

// 订阅超时时间：2分钟 = 2*60*1000ms = 120000ms（TMOS任务定时器单位为ms）
#define RESBAND_SUB_TIMEOUT_MS 120000

static uint8_t resBand_TaskID; // Task ID for internal task/event processing

static gapRole_States_t gapProfileState = GAPROLE_INIT;

// GAP Profile - Name attribute for SCAN RSP data
static uint8_t scanRspData[] = {
    0x0F, // length of this data:15
    GAP_ADTYPE_LOCAL_NAME_COMPLETE,
    'R',
    'e',
    's',
    'B',
    'a',
    'n',
    'd',
    ' ',
    'S',
    'e',
    'n',
    's',
    'o',
    'r'};

static uint8_t advertData[] = {
    // flags
    0x02,
    GAP_ADTYPE_FLAGS,
    GAP_ADTYPE_FLAGS_GENERAL | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
    // service UUIDs
    0x05,
    GAP_ADTYPE_16BIT_MORE,
    LO_UINT16(RESBAND_SERV_UUID),
    HI_UINT16(RESBAND_SERV_UUID),
    LO_UINT16(BATT_SERV_UUID),
    HI_UINT16(BATT_SERV_UUID)};

// Device name attribute value
static uint8_t attDeviceName[GAP_DEVICE_NAME_LEN] = "ResBand Sensor";

// GAP connection handle
static uint16_t gapConnHandle;

// Heart rate measurement value stored in this structure
static attHandleValueNoti_t resBandMeas;
static attHandleValueNoti_t resBandTrainingNoti;
static uint32_t lastPullCount = 0;

// 自定义角度数据（2字节，示例值）
static uint16_t resBandAngle = 0x1234; // 示例角度值（0~360°可映射到0x0000~0xFFFF）
// 删除原有的 resBandFlags 数组，改为单字节标志（可选）
static const uint8_t resBandFlags = 0x00; // 无特殊标志

// // Components of heart rate measurement structure
// static uint8_t  resBandBpm = BPM_DEFAULT;
// static uint16_t resBandEnergy = 0;
// static uint16_t resBandRrInterval1 = RESBAND_BPM_TO_RR(BPM_DEFAULT);
// static uint16_t resBandRrInterval2 = RESBAND_BPM_TO_RR(BPM_DEFAULT);

// // flags for simulated measurements
// static const uint8_t resBandFlags[FLAGS_IDX_MAX] = {
//     RESBAND_FLAGS_CONTACT_NOT_SUP,
//     RESBAND_FLAGS_CONTACT_NOT_DET,
//     RESBAND_FLAGS_CONTACT_DET | RESBAND_FLAGS_ENERGY_EXP,
//     RESBAND_FLAGS_CONTACT_DET | RESBAND_FLAGS_RR,
//     RESBAND_FLAGS_CONTACT_DET | RESBAND_FLAGS_ENERGY_EXP | RESBAND_FLAGS_RR,
//     RESBAND_FLAGS_FORMAT_UINT16 | RESBAND_FLAGS_CONTACT_DET | RESBAND_FLAGS_ENERGY_EXP | RESBAND_FLAGS_RR,
//     0x00};

// static uint8_t resBandFlagsIdx = 0;

// Advertising user-cancelled state
static BOOL resBandAdvCancelled = FALSE;


static uint16_t zero_angle = 0;  // 零位基准角度
static uint8_t zero_calibrated = 0;

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void resBand_ProcessTMOSMsg(tmos_event_hdr_t *pMsg);
static void ResBandGapStateCB(gapRole_States_t newState, gapRoleEvent_t *pEvent);
static void resBandPeriodicTask(void);
static void resBandBattPeriodicTask(void);
static void resBandMeasNotify(void);
static void resBandCB(uint8_t event);
static void resBandBattCB(uint8_t event);
static void SendTrainingDataNotification(void);

/*********************************************************************
 * PROFILE CALLBACKS
 */

// GAP Role Callbacks
static gapRolesCBs_t resBandPeripheralCB = {
    ResBandGapStateCB, // Profile State Change Callbacks
    NULL,                // When a valid RSSI is read from controller
    NULL};

// Bond Manager Callbacks
static gapBondCBs_t resBandBondCB = {
    NULL, // Passcode callback
    NULL  // Pairing state callback
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      ResBand_Init
 *
 * @brief   Initialization function for the Heart Rate App Task.
 *          This is called during initialization and should contain
 *          any application specific initialization (ie. hardware
 *          initialization/setup, table initialization, power up
 *          notificaiton ... ).
 *
 * @param   task_id - the ID assigned by TMOS.  This ID should be
 *                    used to send messages and set timers.
 *
 * @return  none
 */
void ResBand_Init()
{
    resBand_TaskID = TMOS_ProcessEventRegister(ResBand_ProcessEvent);

    // Setup the GAP Peripheral Role Profile
    {
        uint8_t initial_advertising_enable = TRUE;

        // Set the GAP Role Parameters
        GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8_t), &initial_advertising_enable);
        GAPRole_SetParameter(GAPROLE_SCAN_RSP_DATA, sizeof(scanRspData), scanRspData);
        GAPRole_SetParameter(GAPROLE_ADVERT_DATA, sizeof(advertData), advertData);
    }

    // Setup the GAP Bond Manager
    {
        uint32_t passkey = 0; // passkey "000000"
        uint8_t  pairMode = GAPBOND_PAIRING_MODE_WAIT_FOR_REQ;
        uint8_t  mitm = FALSE;
        uint8_t  ioCap = GAPBOND_IO_CAP_DISPLAY_ONLY;
        uint8_t  bonding = TRUE;
        GAPBondMgr_SetParameter(GAPBOND_PERI_DEFAULT_PASSCODE, sizeof(uint32_t), &passkey);
        GAPBondMgr_SetParameter(GAPBOND_PERI_PAIRING_MODE, sizeof(uint8_t), &pairMode);
        GAPBondMgr_SetParameter(GAPBOND_PERI_MITM_PROTECTION, sizeof(uint8_t), &mitm);
        GAPBondMgr_SetParameter(GAPBOND_PERI_IO_CAPABILITIES, sizeof(uint8_t), &ioCap);
        GAPBondMgr_SetParameter(GAPBOND_PERI_BONDING_ENABLED, sizeof(uint8_t), &bonding);
    }

    // Setup the Heart Rate Characteristic Values
    {
        uint8_t sensLoc = RESBAND_SENS_LOC_WRIST;
        ResBand_SetParameter(RESBAND_SENS_LOC, sizeof(uint8_t), &sensLoc);
    }

    // Setup Battery Characteristic Values
    {
        uint8_t critical = DEFAULT_BATT_CRITICAL_LEVEL;
        Batt_SetParameter(BATT_PARAM_CRITICAL_LEVEL, sizeof(uint8_t), &critical);
    }

    // Initialize GATT attributes
    GGS_AddService(GATT_ALL_SERVICES);         // GAP
    GATTServApp_AddService(GATT_ALL_SERVICES); // GATT attributes
    ResBand_AddService(GATT_ALL_SERVICES);
    DevInfo_AddService();
    Batt_AddService();

    // Set the GAP Characteristics
    GGS_SetParameter(GGS_DEVICE_NAME_ATT, GAP_DEVICE_NAME_LEN, attDeviceName);

    // Register for Heart Rate service callback
    ResBand_Register(resBandCB);

    // Register for Battery service callback;
    Batt_Register(resBandBattCB);

    // Setup a delayed profile startup
    tmos_set_event(resBand_TaskID, START_DEVICE_EVT);

    // 初始化时启动倒计时，倒计时内没有订阅会进入shutdown模式，按下wake botton重新启动
    tmos_start_task(resBand_TaskID, RESBAND_SHUTDOWN_EVT, RESBAND_SUB_TIMEOUT_MS);
}

/*********************************************************************
 * @fn      ResBand_ProcessEvent
 *
 * @brief   Heart Rate Application Task event processor.  This function
 *          is called to process all events for the task.  Events
 *          include timers, messages and any other user defined events.
 *
 * @param   task_id  - The TMOS assigned task ID.
 * @param   events - events to process.  This is a bit map and can
 *                   contain more than one event.
 *
 * @return  events not processed
 */
uint16_t ResBand_ProcessEvent(uint8_t task_id, uint16_t events)
{
    if(events & SYS_EVENT_MSG)
    {
        uint8_t *pMsg;

        if((pMsg = tmos_msg_receive(resBand_TaskID)) != NULL)
        {
            resBand_ProcessTMOSMsg((tmos_event_hdr_t *)pMsg);

            // Release the TMOS message
            tmos_msg_deallocate(pMsg);
        }

        // return unprocessed events
        return (events ^ SYS_EVENT_MSG);
    }

    if(events & START_DEVICE_EVT)
    {
        // Start the Device
        GAPRole_PeripheralStartDevice(resBand_TaskID, &resBandBondCB, &resBandPeripheralCB);

        return (events ^ START_DEVICE_EVT);
    }

    if(events & RESBAND_PERIODIC_EVT)
    {
        // Perform periodic heart rate task
        resBandPeriodicTask();

        return (events ^ RESBAND_PERIODIC_EVT);
    }

    if(events & BATT_PERIODIC_EVT)
    {
        // Perform periodic battery task
        resBandBattPeriodicTask();

        return (events ^ BATT_PERIODIC_EVT);
    }

    if(events & RESBAND_CONN_PARAM_UPDATE_EVT)
    {
        // Send param update.
        GAPRole_PeripheralConnParamUpdateReq(gapConnHandle,
                                             DEFAULT_DESIRED_MIN_CONN_INTERVAL,
                                             DEFAULT_DESIRED_MAX_CONN_INTERVAL,
                                             DEFAULT_DESIRED_SLAVE_LATENCY,
                                             DEFAULT_DESIRED_CONN_TIMEOUT,
                                             resBand_TaskID);

        return (events ^ RESBAND_CONN_PARAM_UPDATE_EVT);
    }

    if(events & RESBAND_SHUTDOWN_EVT)
    {
        // 检查是否仍未订阅
        if (!isResBandSubscribed)
        {
            // 停止所有周期性任务
            tmos_stop_task(resBand_TaskID, RESBAND_PERIODIC_EVT);
            tmos_stop_task(resBand_TaskID, BATT_PERIODIC_EVT);
            
            // 停止广告
            uint8_t advState = FALSE;
            GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8_t), &advState);
            // 关闭电源
            GPIOA_ResetBits(GPIO_Pin_9);
        }
        return (events ^ RESBAND_SHUTDOWN_EVT);
    }

    // Discard unknown events
    return 0;
}

/*********************************************************************
 * @fn      resBand_ProcessTMOSMsg
 *
 * @brief   Process an incoming task message.
 *
 * @param   pMsg - message to process
 *
 * @return  none
 */
static void resBand_ProcessTMOSMsg(tmos_event_hdr_t *pMsg)
{
    switch(pMsg->event)
    {
        default:

            break;
    }
}

/*********************************************************************
 * @fn      resBandMeasNotify
 *
 * @brief   Prepare and send a heart rate measurement notification
 *
 * @return  none
 */
static void resBandMeasNotify(void)
{
    resBandMeas.pValue = GATT_bm_alloc(gapConnHandle, ATT_HANDLE_VALUE_NOTI, RESBAND_MEAS_LEN, NULL, 0);

    if(resBandMeas.pValue != NULL)
    {
        uint8_t *p = resBandMeas.pValue;
        // uint8_t  flags = resBandFlags[resBandFlagsIdx];

        // build heart rate measurement structure from simulated values
        // *p++ = flags;

        //1.读取原始角度数值
        resBandAngle = AS5600_ReadTwoByte(_raw_ang_hi, _raw_ang_lo);

        TensionCalculator_UpdateTrainingStats(resBandAngle);

        // 2. 计算拉力值
        uint16_t tension_value = TensionCalculator_GetTensionValue(resBandAngle);


        // 3. 构建数据包：2字节拉力
        *p++ = LO_UINT16(tension_value);    // 拉力低字节
        *p++ = HI_UINT16(tension_value);    // 拉力高字节

        resBandMeas.len = (uint8_t)(p - resBandMeas.pValue);

        if(ResBand_MeasNotify(gapConnHandle, &resBandMeas) != SUCCESS)
        {
            GATT_bm_free((gattMsg_t *)&resBandMeas, ATT_HANDLE_VALUE_NOTI);
        }

//        if(stats.total_pulls > lastPullCount && stats.current_pull_duration > 0)
//        {
//            if(isTrainingDataSubscribed)  // 检查训练数据是否已订阅
//            {
//                SendTrainingDataNotification();  // 独立发送训练数据
//                lastPullCount = stats.total_pulls;
//            }
//        }

        SendTrainingDataNotification();  // 直接发送当前记录

        // SDA_IN();
        // resBandAngle = GPIOA_ReadPortPin(GPIO_Pin_14);

        //        *p++ = LO_UINT16(resBandAngle);
        //        *p++ = HI_UINT16(resBandAngle);
        //
        //        resBandMeas.len = (uint8_t)(p - resBandMeas.pValue);

        // if(++resBandAngle == ANGLE_MAX)
        // {
        //     resBandAngle = ANGLE_DEFAULT;
        // }
    }
}

/*********************************************************************
 * @fn      SendTrainingDataNotification
 *
 * @brief   发送训练数据通知
 */
static void SendTrainingDataNotification(void)
{
    if(!isTrainingDataSubscribed) return;

    TrainingStats_t stats;
    TensionCalculator_GetTrainingStats(&stats);

    resBandTrainingNoti.pValue = GATT_bm_alloc(gapConnHandle, ATT_HANDLE_VALUE_NOTI,
                                              RESBAND_TRAINING_DATA_LEN, NULL, 0);

    if(resBandTrainingNoti.pValue != NULL)
    {
        uint8_t *p = resBandTrainingNoti.pValue;
        uint16_t current_tension = TensionCalculator_GetTensionValue(resBandAngle);
        uint16_t max_tension_value = (uint16_t)(stats.max_tension * 100.0f);

        // 构建训练数据包 (8字节)
        *p++ = LO_UINT16(stats.total_pulls);        // 拉动计数低字节
        *p++ = HI_UINT16(stats.total_pulls);        // 拉动计数高字节

        *p++ = LO_UINT16(stats.current_pull_duration); // 持续时间低字节
        *p++ = HI_UINT16(stats.current_pull_duration); // 持续时间高字节

        *p++ = LO_UINT16(max_tension_value);        // 最大拉力低字节
        *p++ = HI_UINT16(max_tension_value);        // 最大拉力高字节

        *p++ = LO_UINT16(current_tension);          // 当前拉力低字节
        *p++ = HI_UINT16(current_tension);          // 当前拉力高字节

        resBandTrainingNoti.len = RESBAND_TRAINING_DATA_LEN;

        if(ResBand_TrainingDataNotify(gapConnHandle, &resBandTrainingNoti) != SUCCESS)
        {
            GATT_bm_free((gattMsg_t *)&resBandTrainingNoti, ATT_HANDLE_VALUE_NOTI);
        }
        else
        {
            PRINT("发送训练数据: 计数=%lu, 时长=%lums, 最大拉力=%.1fkgf\n",
                  stats.total_pulls, stats.current_pull_duration, stats.max_tension);
        }
    }
}


/*********************************************************************
 * @fn      ResBandGapStateCB
 *
 * @brief   Notification from the profile of a state change.
 *
 * @param   newState - new state
 *
 * @return  none
 */
static void ResBandGapStateCB(gapRole_States_t newState, gapRoleEvent_t *pEvent)
{
    // if connected
    if(newState == GAPROLE_CONNECTED)
    {
        if(pEvent->gap.opcode == GAP_LINK_ESTABLISHED_EVENT)
        {
            // Get connection handle
            gapConnHandle = pEvent->linkCmpl.connectionHandle;

            // Set timer to update connection parameters
            tmos_start_task(resBand_TaskID, RESBAND_CONN_PARAM_UPDATE_EVT, DEFAULT_CONN_PARAM_UPDATE_DELAY);
        }
    }
    // if disconnected
    else if(gapProfileState == GAPROLE_CONNECTED &&
            newState != GAPROLE_CONNECTED)
    {
        uint8_t advState = TRUE;
        // 标记为未订阅（设备断开后，订阅关系自动失效）
        isResBandSubscribed = FALSE;
        // 开启shutdown倒计时
        tmos_start_task(resBand_TaskID, RESBAND_SHUTDOWN_EVT, RESBAND_SUB_TIMEOUT_MS);

        // stop periodic measurement
        tmos_stop_task(resBand_TaskID, RESBAND_PERIODIC_EVT);

        // reset client characteristic configuration descriptors
        ResBand_HandleConnStatusCB(gapConnHandle, LINKDB_STATUS_UPDATE_REMOVED);
        Batt_HandleConnStatusCB(gapConnHandle, LINKDB_STATUS_UPDATE_REMOVED);

        // link loss -- use fast advertising
        GAP_SetParamValue(TGAP_DISC_ADV_INT_MIN, DEFAULT_FAST_ADV_INTERVAL);
        GAP_SetParamValue(TGAP_DISC_ADV_INT_MAX, DEFAULT_FAST_ADV_INTERVAL);
        GAP_SetParamValue(TGAP_GEN_DISC_ADV_MIN, DEFAULT_FAST_ADV_DURATION);

        // Enable advertising
        GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8_t), &advState);
    }
    // if advertising stopped
    else if(gapProfileState == GAPROLE_ADVERTISING &&
            newState == GAPROLE_WAITING)
    {
        // if advertising stopped by user
        if(resBandAdvCancelled)
        {
            resBandAdvCancelled = FALSE;
        }
        // if fast advertising switch to slow
        else if(GAP_GetParamValue(TGAP_DISC_ADV_INT_MIN) == DEFAULT_FAST_ADV_INTERVAL)
        {
            uint8_t advState = TRUE;

            GAP_SetParamValue(TGAP_DISC_ADV_INT_MIN, DEFAULT_SLOW_ADV_INTERVAL);
            GAP_SetParamValue(TGAP_DISC_ADV_INT_MAX, DEFAULT_SLOW_ADV_INTERVAL);
            GAP_SetParamValue(TGAP_GEN_DISC_ADV_MIN, DEFAULT_SLOW_ADV_DURATION);
            GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8_t), &advState);
        }
    }
    // if started
    else if(newState == GAPROLE_STARTED)
    {
        // Set the system ID from the bd addr
        uint8_t systemId[DEVINFO_SYSTEM_ID_LEN];
        GAPRole_GetParameter(GAPROLE_BD_ADDR, systemId);

        // shift three bytes up
        systemId[7] = systemId[5];
        systemId[6] = systemId[4];
        systemId[5] = systemId[3];

        // set middle bytes to zero
        systemId[4] = 0;
        systemId[3] = 0;

        DevInfo_SetParameter(DEVINFO_SYSTEM_ID, DEVINFO_SYSTEM_ID_LEN, systemId);
    }

    gapProfileState = newState;
}

/*********************************************************************
 * @fn      resBandCB
 *
 * @brief   Callback function for heart rate service.
 *
 * @param   event - service event
 *
 * @return  none
 */
static void resBandCB(uint8_t event)
{
    switch(event)
    {
        case RESBAND_MEAS_NOTI_ENABLED:
            isResBandSubscribed = TRUE;
            tmos_stop_task(resBand_TaskID, RESBAND_SHUTDOWN_EVT);

            // 初始化拉力计算模块
            TensionCalculator_Init();

            if(gapProfileState == GAPROLE_CONNECTED)
            {
                tmos_start_task(resBand_TaskID, RESBAND_PERIODIC_EVT, DEFAULT_RESBAND_PERIOD);
            }
            PRINT("拉力测量通知已启用\n");
            break;

        case RESBAND_MEAS_NOTI_DISABLED:
            isResBandSubscribed = FALSE;
            tmos_start_task(resBand_TaskID, RESBAND_SHUTDOWN_EVT, RESBAND_SUB_TIMEOUT_MS);
            tmos_stop_task(resBand_TaskID, RESBAND_PERIODIC_EVT);
            PRINT("拉力测量通知已禁用\n");
            break;

        case RESBAND_TRAINING_NOTI_ENABLED:
            isTrainingDataSubscribed = TRUE;
            tmos_stop_task(resBand_TaskID, RESBAND_SHUTDOWN_EVT);
            PRINT("训练数据通知已启用\n");
            break;

        case RESBAND_TRAINING_NOTI_DISABLED:
            isTrainingDataSubscribed = FALSE;
            if(!isResBandSubscribed)
            {
                tmos_start_task(resBand_TaskID, RESBAND_SHUTDOWN_EVT, RESBAND_SUB_TIMEOUT_MS);
            }
            PRINT("训练数据通知已禁用\n");
            break;

        case RESBAND_COMMAND_SET:
            {
                uint8_t command = 0;
                ResBand_GetParameter(RESBAND_COMMAND, &command);

                if(command == RESBAND_COMMAND_CALIBRATE_ZERO)
                {
                    // 校准零位
                    uint16_t current_angle = AS5600_ReadTwoByte(_raw_ang_hi, _raw_ang_lo);
                    TensionCalculator_CalibrateZero(current_angle);
                    PRINT("零位校准完成: 0x%04X\n", current_angle);
                }else if(command == RESBAND_COMMAND_RESET_STATS)
                {
                    TensionCalculator_ResetTrainingStats();
                    lastPullCount = 0;
                    PRINT("训练统计数据已重置\n");
                }
                else if(command == RESBAND_COMMAND_ENERGY_EXP)
                {
                    PRINT("收到能量重置命令\n");
                    // 可以在这里重置计数等
                }
            }
            break;

        case RESBAND_PARAMS_UPDATED:
            {
                uint16_t pound, length;
                ResBand_GetBandParameters(&pound, &length);
                TensionCalculator_SetParameters(pound, length);
                PRINT("拉力计算参数更新 - 磅数: %d, 长度: %dcm\n", pound, length);
            }
            break;

        default:
            break;
    }
}

/*********************************************************************
 * @fn      resBandBattCB
 *
 * @brief   Callback function for battery service.
 *
 * @param   event - service event
 *
 * @return  none
 */
static void resBandBattCB(uint8_t event)
{
    if(event == BATT_LEVEL_NOTI_ENABLED)
    {
        // if connected start periodic measurement
        if(gapProfileState == GAPROLE_CONNECTED)
        {
            tmos_start_task(resBand_TaskID, BATT_PERIODIC_EVT, DEFAULT_BATT_PERIOD);
        }
    }
    else if(event == BATT_LEVEL_NOTI_DISABLED)
    {
        // stop periodic measurement
        tmos_stop_task(resBand_TaskID, BATT_PERIODIC_EVT);
    }
}

/*********************************************************************
 * @fn      resBandPeriodicTask
 *
 * @brief   Perform a periodic heart rate application task.
 *
 * @param   none
 *
 * @return  none
 */
static void resBandPeriodicTask(void)
{
    if(gapProfileState == GAPROLE_CONNECTED)
    {
        // send heart rate measurement notification
        resBandMeasNotify();

        // Restart timer
        tmos_start_task(resBand_TaskID, RESBAND_PERIODIC_EVT, DEFAULT_RESBAND_PERIOD);
    }
}

/*********************************************************************
 * @fn      resBandBattPeriodicTask
 *
 * @brief   Perform a periodic task for battery measurement.
 *
 * @param   none
 *
 * @return  none
 */
static void resBandBattPeriodicTask(void)
{
    if(gapProfileState == GAPROLE_CONNECTED)
    {
        // perform battery level check
        Batt_MeasLevel();

        // Restart timer
        tmos_start_task(resBand_TaskID, BATT_PERIODIC_EVT, DEFAULT_BATT_PERIOD);
    }
}
/*********************************************************************
*********************************************************************/
