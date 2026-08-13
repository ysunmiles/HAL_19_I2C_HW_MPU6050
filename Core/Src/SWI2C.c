#include "gpio.h"                  // gpio header
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include <stdint.h>
#include "SWI2C.h"

void SWI2C_Init(void)
{
    /* GPIO is configured by MX_GPIO_Init(); nothing else required here. */
}

/*	@brief	写入SCL
*	@param	BitValue: 待写入的值，1或0
*	函数内的延迟用于降低I2C的速度，以便示波器观测，可以取消。保险起见可留10us。
*/
void SWI2C_WriteSCL(GPIO_PinState BitValue)
{
	HAL_GPIO_WritePin(MPU_SCL_GPIO_Port, MPU_SCL_Pin, BitValue);
	HAL_Delay(1);
}

/*	@brief	写入SDA
*	@param	BitValue: 待写入的值，1或0
*	函数内的延迟用于降低I2C的速度，以便示波器观测，可以取消。保险起见可留10us。
*/
void SWI2C_WriteSDA(GPIO_PinState BitValue)
{
	HAL_GPIO_WritePin(MPU_SDA_GPIO_Port, MPU_SDA_Pin, BitValue);
	HAL_Delay(1);
}

/*	@brief	读取SDA
*	@param	无
*/
uint8_t SWI2C_ReadSDA(void)
{
	return HAL_GPIO_ReadPin(MPU_SDA_GPIO_Port, MPU_SDA_Pin);
}

void SWI2C_Start(void)
{
	SWI2C_WriteSDA(1);
	SWI2C_WriteSCL(1);
	SWI2C_WriteSDA(0);
	SWI2C_WriteSCL(0);
}

void SWI2C_Stop(void)
{
	SWI2C_WriteSDA(0);
	SWI2C_WriteSCL(1);
	SWI2C_WriteSDA(1);
}

/*	@brief	发送8位数据Byte
*	@param	Byte:待发送的数据
*/
void SWI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i=0; i<8; i++)
	{
		SWI2C_WriteSDA(!!(Byte & (0b10000000 >> i)));
		SWI2C_WriteSCL(1);
		SWI2C_WriteSCL(0);
	}
}

uint8_t SWI2C_ReceiveByte(void)
{
	uint8_t Byte = 0x00;
	uint8_t i;
	for (i=0; i<8; i++)
	{
		SWI2C_WriteSCL(1);
		if (SWI2C_ReadSDA() == 1)
		{
			Byte |= (0b10000000 >> i);
		}
		SWI2C_WriteSCL(0);
	}
	return Byte;
}

/*	@brief	向从机发送应答
*	@param	AckBit: 应答位，1为非应答NACK，0为应答ACK
*/
void SWI2C_SendingACK(uint8_t AckBit)
{
	SWI2C_WriteSDA(AckBit);
	SWI2C_WriteSCL(1);
	SWI2C_WriteSCL(0);
}
/*	@brief	接收从机的接收应答
*	@value	AckBit: 应答位，1为非应答NACK，0为应答ACK
*/
uint8_t SWI2C_ReceiveACK(void)
{
	SWI2C_WriteSDA(1);
	SWI2C_WriteSCL(1);
	uint8_t AckBit = SWI2C_ReadSDA();
	SWI2C_WriteSCL(0);
	return AckBit;
}

