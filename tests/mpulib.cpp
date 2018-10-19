
#include <stdint>
#include "mpulib.h"


void MPU6050::write16(int Addr, int16_t data){
  write8(Addr,(int8_t) (data>>8));
  write8(Addr+1,(int8_t) data);
}

bool MPU6050::readRbit(int reg, int pos) {
    uint8_t value;
    value = read8(reg);
    return ((value >> pos) & 1); //Isola bit
}

void MPU6050::writeRbit(int reg, int pos, bool state) {
    uint8_t value;
    value = read8(reg);
    if (state) {
        value |= (1 << pos);
    } else {
        value &= ~(1 << pos);
    }
    write8(reg, value);
}

void MPU6050::readRawGyro(){
  rg.XAxis = read16(MPU6050_REG_GYRO_XOUT_H);
  rg.YAxis = read16(MPU6050_REG_GYRO_YOUT_H);
  rg.ZAxis = read16(MPU6050_REG_GYRO_ZOUT_H);
}

void MPU6050::readRawAccel(){
  ra.XAxis = read16(MPU6050_REG_ACCEL_XOUT_H);
  ra.YAxis = read16(MPU6050_REG_ACCEL_YOUT_H);
  ra.ZAxis = read16(MPU6050_REG_ACCEL_ZOUT_H);
}

void MPU6050::calibrateGyro(int amostras) {
    // Define calibragem
    useCalibrate = true;

    // Reseta valores
    float sumX = 0;
    float sumY = 0;
    float sumZ = 0;
    float sigmaX = 0;
    float sigmaY = 0;
    float sigmaZ = 0;

    // Lê n-amostras
    for (int i = 0; i < amostras; ++i) {
	     readRawGyro();
	      sumX += rg.XAxis;
	      sumY += rg.YAxis;
	      sumZ += rg.ZAxis;

	      sigmaX += rg.XAxis * rg.XAxis;
	      sigmaY += rg.YAxis * rg.YAxis;
	      sigmaZ += rg.ZAxis * rg.ZAxis;
	      sleep(5 * 1000);
    }

    // Calcula vetores delta
    dg.XAxis = sumX / amostras;
    dg.YAxis = sumY / amostras;
    dg.ZAxis = sumZ / amostras;

    // Calcula vetores de limite
    th.XAxis = sqrt((sigmaX / 50) - (dg.XAxis * dg.XAxis));
    th.YAxis = sqrt((sigmaY / 50) - (dg.YAxis * dg.YAxis));
    th.ZAxis = sqrt((sigmaZ / 50) - (dg.ZAxis * dg.ZAxis));

    // Se atingiu o limite, recalcula vetores de limite
    if (actualThreshold > 0) {
	     setThreshold(actualThreshold);
    }
}

void MPU6050::setThreshold(int multiple) {
  if (multiple > 0) {
	   if (!useCalibrate) calibrateGyro();

	   // Calcula vetor de limiares
	   tg.XAxis = th.XAxis * multiple;
	   tg.YAxis = th.YAxis * multiple;
	   tg.ZAxis = th.ZAxis * multiple;
  } else { // Se sem limiares
	   tg.XAxis = 0;
	   tg.YAxis = 0;
	   tg.ZAxis = 0;
  }
  // Remember old threshold value
  actualThreshold = multiple;
}

float MPU6050::getTemp(){
  int16_t T;
  T = read16(MPU6050_REG_TEMP_OUT_H);
  return (float)T/340 + 36.53;
}

mpu6050_clockSource_t MPU6050::getClockSource() {
    uint8_t value;
    value = read8(MPU6050_REG_PWR_MGMT_1); // Lê
    value &= 0b00000111; // Mascara
    return (mpu6050_clockSource_t)value; // Cast
}

void MPU6050::setClockSource(mpu6050_clockSource_t fonte) {
    uint8_t value;
    value = read8(MPU6050_REG_PWR_MGMT_1); // Lê
    value &= 0b11111000;
    value |= fonte; // Mascara
    write8(MPU6050_REG_PWR_MGMT_1, value); // Cast
}


void MPU6050::setScale(mpu6050_dps_t escala) {
    uint8_t value;
    switch (escala) {
      case MPU6050_SCALE_250DPS:
	      dpsPerDigit = .007633f;
	      break;
	    case MPU6050_SCALE_500DPS:
	      dpsPerDigit = .015267f;
	      break;
	    case MPU6050_SCALE_1000DPS:
	      dpsPerDigit = .030487f;
	      break;
	    case MPU6050_SCALE_2000DPS:
	      dpsPerDigit = .060975f;
	      break;
	    default:
	      break;
    }

    value = read8(MPU6050_REG_GYRO_CONFIG);
    value &= 0b11100111;
    value |= (escala << 3);
    write8(MPU6050_REG_GYRO_CONFIG, value);
}

mpu6050_dps_t MPU6050::getScale() {
    uint8_t value;
    value = read8(MPU6050_REG_GYRO_CONFIG);
    value &= 0b00011000; // Mascara
    value >>= 3;
    return (mpu6050_dps_t)value; // Cast
}

void MPU6050::setRange(mpu6050_range_t range) {
    uint8_t value;
    switch (range) {
	     case MPU6050_RANGE_2G:
	       rangePerDigit = .000061f;
	       break;
	     case MPU6050_RANGE_4G:
	       rangePerDigit = .000122f;
	       break;
	     case MPU6050_RANGE_8G:
	       rangePerDigit = .000244f;
	       break;
	     case MPU6050_RANGE_16G:
	       rangePerDigit = .0004882f;
	       break;
	     default:
	       break;
    }

    value = read8(MPU6050_REG_ACCEL_CONFIG);
    value &= 0b11100111;
    value |= (range << 3);
    write8(MPU6050_REG_ACCEL_CONFIG, value);
}

mpu6050_range_t MPU6050::getRange(void) {
    uint8_t value;
    value = read8(MPU6050_REG_ACCEL_CONFIG);
    value &= 0b00011000; // Mascara
    value >>= 3;
    return (mpu6050_range_t)value; // Cast
}
