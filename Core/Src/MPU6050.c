#include "SWI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_Addr 0b11010000

/*·	@brief	将数据写入MPU6050指定寄存器
*	@param	RegAddr: 寄存器地址
*	@param	Dbyte: 待写入的数据
*/
void MPU6050_WriteReg(uint8_t RegAddr, uint8_t Byte)
{
	SWI2C_Start();
	SWI2C_SendByte(MPU6050_Addr + 0);
	SWI2C_ReceiveACK();
	SWI2C_SendByte(RegAddr);
	SWI2C_ReceiveACK();
	SWI2C_SendByte(Byte);
	SWI2C_ReceiveACK();
	SWI2C_Stop();
}

/*·	@brief	读取MPU6050指定寄存器的数据
*	@param	RegAddr: 寄存器地址
*	@value	该寄存器的值
*/
uint8_t MPU6050_ReadReg(uint8_t RegAddr)
{
	uint8_t Byte;
	
	SWI2C_Start();
	SWI2C_SendByte(MPU6050_Addr + 0);
	SWI2C_ReceiveACK();
	SWI2C_SendByte(RegAddr);
	SWI2C_ReceiveACK();
	
	SWI2C_Start();
	SWI2C_SendByte(MPU6050_Addr + 1);
	SWI2C_ReceiveACK();
	Byte = SWI2C_ReceiveByte();
	SWI2C_SendingACK(1);
	SWI2C_Stop();
	
	return Byte;
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(WHO_AM_I);
}

void MPU6050_Init(void)
{
	SWI2C_Init();
	
	MPU6050_WriteReg(PWR_MGMT_1, 	0x01);
	MPU6050_WriteReg(PWR_MGMT_2, 	0x00);
	MPU6050_WriteReg(SMPLRT_DIV, 	0x09);
	MPU6050_WriteReg(CONFIG, 		0x06);
	MPU6050_WriteReg(GYRO_CONFIG, 	0x00);
	MPU6050_WriteReg(ACCEL_CONFIG, 	0x00);
}

void MPU6050_GetData(int16_t *AccX,	int16_t *AccY,	int16_t *AccZ,
					int16_t *GyroX,	int16_t *GyroY,	int16_t *GyroZ, int16_t *Temp)
{
	uint8_t DataH, DataL;
	
	DataH = MPU6050_ReadReg(ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(ACCEL_XOUT_L);
	*AccX = (DataH<<8)|DataL;
	
	DataH = MPU6050_ReadReg(ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(ACCEL_YOUT_L);
	*AccY = (DataH<<8)|DataL;
	
	DataH = MPU6050_ReadReg(ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(ACCEL_ZOUT_L);
	*AccZ = (DataH<<8)|DataL;

	DataH = MPU6050_ReadReg(TEMP_OUT_H);
	DataL = MPU6050_ReadReg(TEMP_OUT_L);
	*Temp = (DataH<<8)|DataL;
	
	DataH = MPU6050_ReadReg(GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(GYRO_XOUT_L);
	*GyroX = (DataH<<8)|DataL;

	DataH = MPU6050_ReadReg(GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(GYRO_YOUT_L);
	*GyroY = (DataH<<8)|DataL;
	
	DataH = MPU6050_ReadReg(GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(GYRO_ZOUT_L);
	*GyroZ = (DataH<<8)|DataL;
}



