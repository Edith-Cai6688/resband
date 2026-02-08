#include "AS5600.h"


//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	SET_SDA;	  	  
	SET_SCL;
	mDelayuS(4);
 	RESET_SDA;//START:when CLK is high,DATA change form high to low 
	mDelayuS(4);
	RESET_SCL;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	RESET_SCL;
	RESET_SDA;//STOP:when CLK is high DATA change form low to high
 	mDelayuS(4);
	SET_SCL; 
	SET_SDA;//发送I2C总线结束信号
	mDelayuS(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	mDelayuS(1);
	SET_SCL;mDelayuS(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	RESET_SCL;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	RESET_SCL;
	SDA_OUT();
	RESET_SDA;
	mDelayuS(2);
	SET_SCL;
	mDelayuS(2);
	RESET_SCL;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	RESET_SCL;
	SDA_OUT();
	SET_SDA;
	mDelayuS(2);
	SET_SCL;
	mDelayuS(2);
	RESET_SCL;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    RESET_SCL;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        if((txd&0x80)>>7) SET_SDA; else RESET_SDA;
        txd<<=1;
		mDelayuS(2);   //对TEA5767这三个延时都是必须的
		SET_SCL;
		mDelayuS(2); 
		RESET_SCL;	
		mDelayuS(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        RESET_SCL; 
        mDelayuS(2);
		SET_SCL;
        receive<<=1;
        if(READ_SDA)receive++;   
		mDelayuS(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}


//函数：u8 AS5600_ReadOneByte(u16 ReadAddr)
//功能：从AS5600模块读取一个字节的数据
//参数：ReadAddr    要读取的地址
//返回：读取到的数据
u8 AS5600_ReadOneByte(u16 ReadAddr)
{                  
    u8 temp=0;                                                                                   
  IIC_Start();  
    IIC_Send_Byte((0x36<<1)|0x00);       //
    IIC_Wait_Ack(); 
  IIC_Send_Byte(ReadAddr);   //
    IIC_Wait_Ack();        
    IIC_Start();              
    IIC_Send_Byte((0x36<<1)|0x01);           //           
    IIC_Wait_Ack();     
  temp=IIC_Read_Byte(0);           
  IIC_Stop();//       
    return temp;
}


//函数功能：向AS5600写入一个字节
void AS5600_WriteOneByte(u16 WriteAddr,u8 WriteData)
{				  	  	    																 
  //开始发送
  IIC_Start();  
	//发送地址位0x36，写操作
	IIC_Send_Byte((0X36<<1)|0x00);	  
	IIC_Wait_Ack(); //等待响应
  //发送写入地址
  IIC_Send_Byte(WriteAddr);   
	IIC_Wait_Ack();	    //等待响应
  //发送写入数据
	IIC_Start();  	 	   
	IIC_Send_Byte(WriteData);        
	IIC_Wait_Ack();	 	   
  //结束发送
  IIC_Stop();
	mDelaymS(10);
}

//读2个字节数据，获取原始角度
u16 AS5600_ReadTwoByte(u16 ReadAddr_hi,u16 ReadAddr_lo)
{
	u16 TwoByte_Data = 0;
	u8 hi_Data = 0,lo_Data = 0;
	//Read the first byte (higher address)
	hi_Data = AS5600_ReadOneByte(ReadAddr_hi);
	//Read the second byte (lower address)
	lo_Data = AS5600_ReadOneByte(ReadAddr_lo);
	//Combine the two bytes into a single 16-bit value
	TwoByte_Data = (hi_Data<<8)|lo_Data;
	//Return the 16-bit value
	return TwoByte_Data;
}























