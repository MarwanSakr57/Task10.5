#include <Wire.h> 

const int MPU6050_ADDR = 0x68; // The I2C address of the MPU6050
const float GYRO_SENSITIVITY = 131.0;

void setup() {
  Wire.begin();  
  Serial.begin(9600); 

  // Wake up the MPU6050
  Wire.beginTransmission(MPU6050_ADDR); 
  Wire.write(0x6B);  //  power management register
  Wire.write(0);  // Write 0 to wake it up
  Wire.endTransmission(true);  
}

void loop() {
  int16_t rawGyroZ = readGyroZ();  // Read the Z axis gyroscope data

    // Convert raw data to degrees per second
  float gyroZ_dps = rawGyroZ / GYRO_SENSITIVITY;
  Serial.print("Gyro Z (Yaw Rate): ");
  Serial.print(gyroZ_dps);  // Print the raw gyro Z data
  Serial.println(" °/Sec");
  delay(500);  
}

int16_t readGyroZ() {
  Wire.beginTransmission(MPU6050_ADDR);  
  Wire.write(0x47);  // Point to the high byte of gyro Z data register
  Wire.endTransmission(false);  
  Wire.requestFrom(MPU6050_ADDR, 2, true);  // Request 2 bytes of data from MPU6050
  //since we request 2 bytes after sending highbyte the lowbyte data register is sequentially after the highbyte(0x48)

  int highByte = Wire.read();  
  int lowByte = Wire.read();  

  // Combine high and low bytes to get the full gyro Z value
  int16_t gyroZ = (highByte << 8) | lowByte;

  return gyroZ;  
}
