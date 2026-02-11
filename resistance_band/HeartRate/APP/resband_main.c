/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.1
 * Date               : 2020/08/06
 * Description        : 心率计主函数及任务系统初始化
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */
#include "config.h"
#include "HAL.h"
#include "resband.h"
#include "CH57x_common.h"
#include "OY8699.h"

/*********************************************************************
 * GLOBAL TYPEDEFS
 */
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

/*********************************************************************
 * @fn      Main_Circulation
 *
 * @brief   主循环
 *
 * @return  none
 */
__attribute__((section(".highcode")))
__attribute__((noinline))
void Main_Circulation()
{
    while(1)
    {
        TMOS_SystemProcess();
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   主函数
 *
 * @return  none
 */
int main(void)
{
#if(defined(DCDC_ENABLE)) && (DCDC_ENABLE == TRUE)
    PWR_DCDCCfg(ENABLE);
#endif
    SetSysClock(CLK_SOURCE_PLL_60MHz);
#if(defined(HAL_SLEEP)) && (HAL_SLEEP == TRUE)
    GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    R16_PB_INT_EN |= (1 << 8);  // 开启PB22 中断（外部唤醒）
    PWR_PeriphWakeUpCfg(ENABLE, RB_SLP_GPIO_WAKE, Level_ShortDelay);    // press button down for 520 cycles
#endif
#ifdef DEBUG
    GPIOA_SetBits(bTXD1);
    GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
#endif
    // USB使能
    GPIOB_ModeCfg(GPIO_Pin_12,GPIO_ModeOut_PP_5mA);
    GPIOB_SetBits(GPIO_Pin_12);
    
    CH57X_BLEInit(); //1.使能TMOS调度系统
    HAL_Init();//2.使能硬件
    GAPRole_PeripheralInit();//3.使能BLE的应用协议
    OY_SPI_Init();// 初始化位移读取传感器

    ResBand_Init();

    Main_Circulation();//启动TMOS调度系统
}

/******************************** endfile @ main ******************************/
