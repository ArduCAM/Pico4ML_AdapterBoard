#include "ICM42622.h"

#include <stdio.h>


uint8_t ICM42622::Icm42622Init(void)
{
  uint8_t Ascale = AFS_4G, Gscale = GFS_2000DPS, AODR = AODR_100Hz, GODR = GODR_100Hz;
  uint8_t DeviceID=0;

  DeviceID=Icm42622CheckID();
  if (DeviceID!=ICM42622_DEVICE_ID)
  {
    return 0;
  }
  
  uint8_t temp =I2cReadOneByte(ICM42622_DEVICE_CONFIG);
  I2cWriteOneByte(ICM42622_DEVICE_CONFIG,temp|0x01);
  sleep_ms(1000);

  temp = I2cReadOneByte( ICM42622_PWR_MGMT0); // make sure not to disturb reserved bit values
  
  I2cWriteOneByte( ICM42622_PWR_MGMT0,0x0F);  // enable gyro and accel in low noise mode

  sleep_ms(100);

  I2cWriteOneByte( ICM42622_GYRO_CONFIG0, GODR | Gscale << 5); // gyro full scale and data rate

  I2cWriteOneByte( ICM42622_ACCEL_CONFIG0, AODR | Ascale << 5); // set accel full scale and data rate

  I2cWriteOneByte( ICM42622_GYRO_CONFIG1,0x0a); // set temperature sensor low pass filter to 5Hz, use first order gyro filter

  I2cWriteOneByte(ICM42622_ACCEL_CONFIG1, 0x14); 

  I2cWriteOneByte( ICM42622_INT_CONFIG, 0x03 ); // set both interrupts active high, push-pull, pulsed

  I2cWriteOneByte( ICM42622_FIFO_CONFIG, 0x40);

  I2cWriteOneByte( ICM42622_FIFO_CONFIG1, 0x61); // Enable the accel  to the FIFO
  
  I2cWriteOneByte( ICM42622_FIFO_CONFIG2, 0x00);

  I2cWriteOneByte( ICM42622_FIFO_CONFIG3, 0xff);  
  return 1;
}


bool ICM42622::Icm42622ReadGyro(float *ps16X, float *ps16Y, float *ps16Z) 
{
  uint8_t u8Buf[6]={0};
  int16_t s16Buf[3] = { 0 };

  u8Buf[0]  = I2cReadOneByte(ICM42622_GYRO_DATA_X0);
  u8Buf[1]  = I2cReadOneByte(ICM42622_GYRO_DATA_X1);
  s16Buf[0] = (u8Buf[1] << 8) | u8Buf[0];
  u8Buf[0]  = I2cReadOneByte(ICM42622_GYRO_DATA_Y0);
  u8Buf[1]  = I2cReadOneByte(ICM42622_GYRO_DATA_Y1);
  s16Buf[1] = (u8Buf[1] << 8) | u8Buf[0];
  u8Buf[0]  = I2cReadOneByte(ICM42622_GYRO_DATA_Z0);
  u8Buf[1]  = I2cReadOneByte(ICM42622_GYRO_DATA_Z1);
  s16Buf[2] = (u8Buf[1] << 8) | u8Buf[0];

  *ps16X = s16Buf[0] * 2000.0 / 32768.0;
  *ps16Y = s16Buf[1] * 2000.0 / 32768.0;
  *ps16Z = s16Buf[2] * 2000.0 / 32768.0;

  if (*ps16X == 0 && *ps16Y == 0 && *ps16Z == 0) 
  {
    return false;
  }

  return true;
}


bool ICM42622::Icm42622ReadAccel(float *ps16X, float *ps16Y, float *ps16Z) 
{
  uint8_t                     u8Buf[2];
  int16_t                     s16Buf[3] = { 0 };
  
  u8Buf[0]  = I2cReadOneByte(ICM42622_ACCEL_DATA_X0);
  u8Buf[1]  = I2cReadOneByte(ICM42622_ACCEL_DATA_X1);
  s16Buf[0] = (u8Buf[1] << 8) | u8Buf[0];

  u8Buf[0]  = I2cReadOneByte(ICM42622_ACCEL_DATA_Y0);
  u8Buf[1]  = I2cReadOneByte(ICM42622_ACCEL_DATA_Y1);
  s16Buf[1] = (u8Buf[1] << 8) | u8Buf[0];

  u8Buf[0]  = I2cReadOneByte(ICM42622_ACCEL_DATA_Z0);
  u8Buf[1]  = I2cReadOneByte(ICM42622_ACCEL_DATA_Z1);
  s16Buf[2] = (u8Buf[1] << 8) | u8Buf[0];


  *ps16X = s16Buf[0] * 4.0 / 32768.0;
  *ps16Y = s16Buf[1] * 4.0 / 32768.0;
  *ps16Z = s16Buf[2] * 4.0 / 32768.0;


  if (*ps16X == 0 && *ps16Y == 0 && *ps16Z == 0) 
  {
    return false;
  }
  
  return true;
}

uint8_t ICM42622::Icm42622CheckID(void)
{
  return I2cReadOneByte(ICM42622_WHO_AM_I);
}

uint8_t ICM42622::Icm42622DataReady(void)
{
  return I2cReadOneByte(ICM42622_INT_STATUS)&0x08;
}

void ICM42622::I2cWriteOneByte(uint8_t reg, uint8_t value) {
  uint8_t buf[] = { reg, value };
  i2c_write_blocking(I2C_PORT, ICM42622_I2C_ADDRESS, buf, 2, false);
}

uint8_t ICM42622::I2cReadOneByte(uint8_t reg) {
  uint8_t buf;
  i2c_write_blocking(I2C_PORT, ICM42622_I2C_ADDRESS, &reg, 1, true);
  i2c_read_blocking(I2C_PORT, ICM42622_I2C_ADDRESS, &buf, 1, false);
  return buf;
}

void ICM42622::Icm42622ReadFifo(uint8_t* buffer,uint16_t lenght)
{
  I2cReadBlock(ICM42622_FIFO_DATA,buffer,lenght);
}

void ICM42622::I2cReadBlock(uint8_t add,uint8_t* buffer,uint16_t lenght)
{
  i2c_write_blocking(I2C_PORT,ICM42622_I2C_ADDRESS,&add,1,false);
  i2c_read_blocking(I2C_PORT,ICM42622_I2C_ADDRESS,buffer,lenght,false);
}