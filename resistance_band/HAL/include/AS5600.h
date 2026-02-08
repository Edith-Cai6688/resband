#ifndef __AS5600_H
#define __AS5600_H
#include "HAL.h"


   	   		   
//IO方向设置
#define SDA_IN()  GPIOA_ModeCfg(GPIO_Pin_13,GPIO_ModeIN_PU)
#define SDA_OUT() GPIOA_ModeCfg(GPIO_Pin_13,GPIO_ModeOut_PP_5mA)

//IO操作函数	 
#define RESET_SCL           GPIOA_ResetBits(GPIO_Pin_14)
#define SET_SCL             GPIOA_SetBits(GPIO_Pin_14)
#define RESET_SDA           GPIOA_ResetBits(GPIO_Pin_13)
#define SET_SDA             GPIOA_SetBits(GPIO_Pin_13)
#define READ_SDA            GPIOA_ReadPortPin(GPIO_Pin_13)  //输入SDA

#define	_raw_ang_hi 0x0c
#define	_raw_ang_lo 0x0d

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  

u16 AS5600_ReadTwoByte(u16 ReadAddr_hi,u16 ReadAddr_lo);
#endif
