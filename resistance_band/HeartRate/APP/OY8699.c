# include "CH57x_common.h"

uint8_t Send_MotionStatus_Buff[] = {2, 0};
uint8_t Receive_MotionStatus_Buff[2];

uint8_t Send_X_Buff[] = {3, 0};
uint8_t Receive_X_Buff[2];

uint8_t Send_Y_Buff[] = {4, 0};
uint8_t Receive_Y_Buff[2];

// 引脚定义 
#define OY_SCLK_PIN  GPIO_Pin_15  // 接传感器的 SCLK
#define OY_SDIO_PIN  GPIO_Pin_14  // 接传感器的 SDIO

// 同步序列
void OY_Serial_Resync(void) {
    // 1. 确保 SCLK 是输出状态
    GPIOB_ModeCfg(OY_SCLK_PIN, GPIO_ModeOut_PP_5mA);
    // 2. 翻转 SCLK 为低电平
    GPIOB_ResetBits(OY_SCLK_PIN); 
    // 3. 维持至少 tRESYNC 时间
    DelayMs(1); 
    // 4. 翻转为高电平
    GPIOB_SetBits(OY_SCLK_PIN);
    // 5. 维持至少 tSIWIT 时间 
    DelayMs(2); 
    // 此时串口逻辑复位完成，可以立即开始读 0x00 了
}

// 主机模式
void OY_SPI_Init(){
    R8_SPI0_CTRL_MOD = 0;
    GPIOB_ModeCfg(OY_SCLK_PIN, GPIO_ModeOut_PP_5mA); // SCLK 设为推挽输出
    GPIOB_ModeCfg(OY_SDIO_PIN, GPIO_ModeOut_PP_5mA); // SDIO 初始设为输出
    GPIOB_SetBits(OY_SCLK_PIN); // SCLK 初始高电平 (Mode 3)
    OY_Serial_Resync();
}

// 读寄存器函数
// 返回值：读取到的 8 位数据
uint8_t OY_Read_Reg(uint8_t reg_addr) {
    uint8_t data = 0;
    uint8_t addr = reg_addr & 0x7F; // 读操作：最高位 MSB = 0

    // 1. 发送 8 位地址
    GPIOB_ModeCfg(OY_SDIO_PIN, GPIO_ModeOut_PP_5mA); // 确保是输出
    for(int i = 7; i >= 0; i--) {
        GPIOB_ResetBits(OY_SCLK_PIN); // SCLK 下降沿：传输数据
        if(addr & (1 << i)) 
            GPIOB_SetBits(OY_SDIO_PIN);
        else 
            GPIOB_ResetBits(OY_SDIO_PIN);
        
        DelayUs(10); // 保持时间
        GPIOB_SetBits(OY_SCLK_PIN);   // SCLK 上升沿：复位
        DelayUs(10);
    }

    // 2. 切换阶段 (tHOLD)
    // 必须在第 8 个时钟结束后，立刻释放数据线
    GPIOB_ModeCfg(OY_SDIO_PIN, GPIO_ModeIN_Floating); // 切换为高阻态
    DelayUs(200); // 200us确保传感器准备好数据

    // 3. 读取 8 位数据
    for(int i = 7; i >= 0; i--) {
        GPIOB_ResetBits(OY_SCLK_PIN); // SCLK 下降沿：传感器开始输出数据
        DelayUs(10);                   // 等待传感器电平稳定

        GPIOB_SetBits(OY_SCLK_PIN);   // SCLK 上升沿：MCU 完成采样
        DelayUs(5);

        if(GPIOB_ReadPortPin(OY_SDIO_PIN)) // 读取 SDIO 电平
            data |= (1 << i);
        
        DelayUs(10);
    }

    return data;
}



