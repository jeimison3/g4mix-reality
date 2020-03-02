//Originalmente de https://github.com/randrews7/rpi-mpu6050/

#include <iostream>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#define MPU_ACCEL_XOUT1 0x3b
#define MPU_ACCEL_XOUT2 0x3c
#define MPU_ACCEL_YOUT1 0x3d
#define MPU_ACCEL_YOUT2 0x3e
#define MPU_ACCEL_ZOUT1 0x3f
#define MPU_ACCEL_ZOUT2 0x40

#define MPU_GYRO_XOUT1 0x43
#define MPU_GYRO_XOUT2 0x44
#define MPU_GYRO_YOUT1 0x45
#define MPU_GYRO_YOUT2 0x46
#define MPU_GYRO_ZOUT1 0x47
#define MPU_GYRO_ZOUT2 0x48

#define MPU_TEMP1 0x41
#define MPU_TEMP2 0x42

#define MPU_POWER1 0x6b
#define MPU_POWER2 0x6c

int main(int argc, char **argv)
{

    int8_t power = i2c_smbus_read_byte_data(fd, MPU_POWER1);
    i2c_smbus_write_byte_data(fd, MPU_POWER1, ~(1 << 6) & power);

    while (1) {
        int16_t temp = i2c_smbus_read_byte_data(fd, MPU_TEMP1) << 8 |
                       i2c_smbus_read_byte_data(fd, MPU_TEMP2);

        int16_t xaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_XOUT1) << 8 |
                         i2c_smbus_read_byte_data(fd, MPU_ACCEL_XOUT2);
        int16_t yaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_YOUT1) << 8 |
                         i2c_smbus_read_byte_data(fd, MPU_ACCEL_YOUT2);
        int16_t zaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_ZOUT1) << 8 |
                         i2c_smbus_read_byte_data(fd, MPU_ACCEL_ZOUT2);

        int16_t xgyro = i2c_smbus_read_byte_data(fd, MPU_GYRO_XOUT1) << 8 |
                        i2c_smbus_read_byte_data(fd, MPU_GYRO_XOUT2);
        int16_t ygyro = i2c_smbus_read_byte_data(fd, MPU_GYRO_YOUT1) << 8 |
                        i2c_smbus_read_byte_data(fd, MPU_GYRO_YOUT2);
        int16_t zgyro = i2c_smbus_read_byte_data(fd, MPU_GYRO_ZOUT1) << 8 |
                        i2c_smbus_read_byte_data(fd, MPU_GYRO_ZOUT2);

        cout << "temp: " << ((float)temp / 340.0f + 36.53) << endl;
        cout << "accel X,Y,Z: " << ((int)xaccel) << " " << ((int)yaccel) << " " << ((int)zaccel) << endl;
        cout << "gyro X,Y,Z: " << ((int)xgyro) << " " << ((int)ygyro) << " " << ((int)zgyro) << endl;
        sleep(1);
    }

    return 0;
}
