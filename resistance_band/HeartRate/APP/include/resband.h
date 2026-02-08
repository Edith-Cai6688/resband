/********************************** (C) COPYRIGHT *******************************
 * File Name          : resBand.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/11
 * Description        :
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef resBand_H
#define resBand_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */

// Heart Rate Task Events
#define START_DEVICE_EVT                 0x0001
#define RESBAND_PERIODIC_EVT             0x0002
#define BATT_PERIODIC_EVT                0x0004
#define RESBAND_CONN_PARAM_UPDATE_EVT    0x0008
#define RESBAND_SHUTDOWN_EVT             0x0010

#define RESBAND_MEAS_LEN             2
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task Initialization for the BLE Application
 */
extern void ResBand_Init(void);

/*
 * Task Event Processor for the BLE Application
 */
extern uint16_t ResBand_ProcessEvent(uint8_t task_id, uint16_t events);
extern uint16_t CalculateTension(uint16_t rawAngle);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
