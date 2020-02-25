/*
P9_19       SCL
P9_20       SDA
P9_3        VCC
P9_1        GND
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

//MPU6050 register addresses
#define MPU6050_REG_POWER               0x6B
#define MPU6050_REG_GYRO_CONFIG         0x1B

#define MPU6050_REG_GYRO_X_HIGH          0x43
#define MPU6050_REG_GYRO_X_LOW           0x44
#define MPU6050_REG_GYRO_Y_HIGH          0x45
#define MPU6050_REG_GYRO_Y_LOW           0x46
#define MPU6050_REG_GYRO_Z_HIGH          0x47
#define MPU6050_REG_GYRO_Z_LOW           0x48


#define GYR_FS_SENS_0			131
#define GYR_FS_SENS_1			65.5
#define GYR_FS_SENS_2			32.8
#define GYR_FS_SENS_3			16.4


//I2C Slave ADDR
#define SLAVE_ADDR 0x68

#define MAX_VALUE 50

#define I2C_DEVICE_FILE   "/dev/i2c-2"

int fd; // global variable



int mpu6050_write(uint8_t addr, uint8_t data){
  int ret;
  char buf[2];
  buf[0]=addr;
  buf[1]=data;

  ret = write(fd,buf,2);
  if (ret <= 0)
  {
      perror("fail\n");
      return -1;
  }
  return 0;
}


int mpu6050_read(uint8_t base_addr, char *pBuffer,uint32_t len)     {
  int ret;
  char buf[2];
  buf[0]=base_addr;

  ret = write(fd,buf,1);
  if (ret <= 0)
  {
      perror("write fail\n");
      return -1;
  }

  // write + read

  ret = read(fd,pBuffer,len);
  if(ret <= 0)
  {
      perror("read fail\n");
      return -1;
  }
  return 0;
}


void mpu6050_init(){

    mpu6050_write(MPU6050_REG_POWER, 0x00);
    usleep(500);
    mpu6050_write(MPU6050_REG_GYRO_CONFIG, 0x18);
    usleep(500);
}



void mpu6050_read_gyro(uint32_t *pBuffer){

    char gyro_buffer[6]; // 3 Eksen 3x2

    mpu6050_read(MPU6050_REG_GYRO_X_HIGH,gyro_buffer,6);

    pBuffer[0] =  ( (gyro_buffer[0] << 8) +  gyro_buffer[1] );
    pBuffer[1] =  ( (gyro_buffer[2] << 8) +  gyro_buffer[3] );
    pBuffer[2] =  ( (gyro_buffer[4] << 8) +  gyro_buffer[5] );

}

int main(void){

     uint32_t gyro_value[3];
     double gyrox,gyroy,gyroz;

     //I2C device file
    if ((fd = open(I2C_DEVICE_FILE,O_RDWR)) < 0) {
        perror("ERROR I2C file\n");
        return -1;
    }


    if (ioctl(fd,I2C_SLAVE,SLAVE_ADDR) < 0) {

            perror("ERROR I2C slave address\n");
            close(fd);
            return -1;
    }


    mpu6050_init();

    while(1)
    {

        mpu6050_read_gyro(gyro_value);


        gyrox = (double) gyro_value[0]/GYR_FS_SENS_3;
        gyroy = (double) gyro_value[1]/GYR_FS_SENS_3;
        gyroz = (double) gyro_value[2]/GYR_FS_SENS_3;


        //raw values
       printf("gyro(raw): X:%d Y:%d Z:%d \n", gyro_value[0],gyro_value[1],gyro_value[2]);

       //g values
       printf("gyro(dps): X:%.3f Y:%.3f Z:%.3f \n" , gyrox,gyroy,gyroz);

       usleep(500 * 1000); // 500ms delay

    }
}
