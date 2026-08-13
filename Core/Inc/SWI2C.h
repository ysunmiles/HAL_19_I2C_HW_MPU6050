#ifndef __SWI2C_H
#define __SWI2C_H

#include <stdint.h>

void SWI2C_Init(void);
void SWI2C_Start(void);
void SWI2C_Stop(void);
void SWI2C_SendByte(uint8_t Byte);
uint8_t SWI2C_ReceiveByte(void);
void SWI2C_SendACK(uint8_t AckBit);
uint8_t SWI2C_ReceiveACK(void);

#endif