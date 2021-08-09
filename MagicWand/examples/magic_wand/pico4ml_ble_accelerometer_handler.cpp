/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "accelerometer_handler.h"
#include "ICM42622.h"
#include <pico/stdio.h>
#include <stdio.h>
#include <hardware/gpio.h>

// Buffer, save the last 200 groups of 3 channel values
float save_data[600] = { 0.0 };

// the latest position in the save_data buffer
int begin_index = 0;
// If there is not enough data to make inferences, then True
auto pending_initial_data = true;
uint8_t DeviceWho=0;
uint8_t count_h=0,count_l=0;
uint16_t AccelLenght=0;
uint8_t AccelBuffer[2048]={0};
int16_t Accel_X=0,Accel_Y=0,Accel_Z=0;
int sample_skip_counter = 1;

TfLiteStatus SetupAccelerometer(tflite::ErrorReporter *error_reporter) {
  uint8_t flag=0;
  stdio_init_all();
  i2c_init(I2C_PORT, 400 * 1000);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(IC2_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(IC2_SCL);
  sleep_ms(1000);
  uint8_t DeviceID=ICM42622::Icm42622CheckID();
  if(DeviceID==ICM42622_DEVICE_ID)
  {
    DeviceWho=ICM42622_DEVICE;
    flag=ICM42622::Icm42622Init();
    if (flag==0) 
    {
      TF_LITE_REPORT_ERROR(error_reporter, "Failed to initialize IMU");
      return kTfLiteError;
    }
  }

  TF_LITE_REPORT_ERROR(error_reporter, "Magic starts!");
  return kTfLiteOk;
}

static bool UpdateData() {

  float x = 0.0f, y = 0.0f, z = 0.0f;
  if (!ICM42622::Icm42622ReadAccel(&x, &y, &z)) {
    return false;
  }


  // raw data processing
  const float tmp_x = -y;
  const float tmp_y = -x;
  const float tmp_z = z;
  // Axis adjustment
  const float norm_x       = -tmp_x;
  const float norm_y       = tmp_y;
  const float norm_z       = tmp_z;
  save_data[begin_index++] = norm_x * 1000;
  save_data[begin_index++] = norm_y * 1000;
  save_data[begin_index++] = norm_z * 1000;


  if (begin_index >= 600) {
    begin_index = 0;
  }



  return true;
}

bool ReadAccelerometer(tflite::ErrorReporter *error_reporter, float *input,
                       int length) {
  bool new_data = false;

  float x = 0.0f, y = 0.0f, z = 0.0f;
  count_h=ICM42622::I2cReadOneByte(ICM42622_FIFO_COUNTH);
  count_l=ICM42622::I2cReadOneByte(ICM42622_FIFO_COUNTL);
  AccelLenght=count_h<<8|count_l;
  if(AccelLenght>0)
  {
    ICM42622::Icm42622DataReady();
    ICM42622::Icm42622ReadFifo(AccelBuffer,AccelLenght);
    for (uint16_t value = 0; value < AccelLenght/8; value++)
    {
      Accel_X=(AccelBuffer[value*8+1]<<8)|AccelBuffer[value*8+2];
      Accel_Y=(AccelBuffer[value*8+3]<<8)|AccelBuffer[value*8+4];
      Accel_Z=(AccelBuffer[value*8+5]<<8)|AccelBuffer[value*8+6];
      if (sample_skip_counter != 4) {
      sample_skip_counter += 1;
      continue;
      }
      // printf("%d %d %d\r\n",Accel_X,Accel_Y,Accel_Z);
      const float tmp_x = -Accel_Y;
      const float tmp_y = -Accel_X;
      const float tmp_z = Accel_Z;
      // Axis adjustment
      const float norm_x       = -tmp_x;
      const float norm_y       = tmp_y;
      const float norm_z       = tmp_z;
      save_data[begin_index++] = norm_x * 1000;
      save_data[begin_index++] = norm_y * 1000;
      save_data[begin_index++] = norm_z * 1000;
      sample_skip_counter = 1;
      if (begin_index >= 600) {
        begin_index = 0;
      }
      new_data=true;     
    }
  }
  
  

  if (!new_data) {
    return false;
  }
  // Check if we are ready to make predictions or are still waiting for more initial
  // data
  if (pending_initial_data && begin_index >= 200) {
    pending_initial_data = false;
  }

  // If we don't have enough data, return false
  if (pending_initial_data) {
    return false;
  }

  for (int i = 0; i < length; ++i) {
    int ring_array_index = begin_index + i - length;
    if (ring_array_index < 0) {
      ring_array_index += 600;
    }
    input[i] = save_data[ring_array_index];
  }
  return true;
}
