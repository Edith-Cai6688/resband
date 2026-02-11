#ifndef OY8699_H
#define OY8699_H


void OY_SPI_Init();
void OY_Read_Init();
void Set_Output();
void Set_Input();
uint8_t OY_Read_Reg(uint8_t reg_addr);
void OY_Serial_Resync(void);
void OY_Read_XY(uint8_t *buffer);









#endif