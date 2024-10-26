#define motor1 11
#define motor2 11
#define motor3 11
#define motor4 11
#define motor5 11
#define motor6 11
#include <Wire.h>

float RatePitch, RateRoll, RateYaw; 
float accX, accY, accX; 
float RateCalibrationPitch, RateCalibrationRoll, RateCalibrationYaw;
int RateCalibrationNumber;


void gyro_signals(void){
      Wire.beginTransmission(0x68);//hex for starting communication
      Wire.write(0x1A);//low pass filter selection hex
      Wire.write(0x00);//change this to select different low pass filters.(values allowed: 0-256hz, 1-188hz, 2-98hz, 3-42hz, 4-20hz, 5-10hz, 6-5hz)
      Wire.endTransmission();

      Wire.beginTransmission(0x68);//hex for starting communication
      Wire.write(0x1B);//gyro callibration
      Wire.write(0x8);//change this to select different gyro callibrations.
      Wire.endTransmission();

      Wire.beginTransmission(0x68);//hex for stating communication
      Wire.write(0x43);//import gyro output
      Wire.endTransmission();

      Wire.requestFrom(0x68,6);

      int16_t gyroX= Wire.read()<<8 | Wire.read(); //read the gyro measurements around the x axis
      int16_t gyroY= Wire.read()<<8 | Wire.read(); //read the gyro measurements around the y axis
      int16_t gyroZ= Wire.read()<<8 | Wire.read(); //read the gyro measurements around the z axis

      Wire.beginTransmission(MPU6050_ADDR);
      Wire.write(0x3B);     
      Wire.endTransmission();

      int16_t accX= Wire.read()<<8 | Wire.read(); //read the gyro measurements around the x axis
      int16_t accY= Wire.read()<<8 | Wire.read(); //read the gyro measurements around the y axis
      int16_t accZ= Wire.read()<<8 | Wire.read();

      rateRoll=(float)gyroX/256;
      ratePitch=(float)gyroY/256;
      rateYaw=(float)gyroZ/256;
      int16_t accelX, accelY, accelZ;

      


}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor1,OUT);
  pinMode(motor2,OUT);
  pinMode(motor3,OUT);
  pinMode(motor4,OUT);
  pinMode(motor5,OUT);
  pinMode(motor6,OUT);

    Wire.setClock(400000);
  Wire.begin();
  delay(250);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  for(rateCallibrationNumber=0; rateCallibrationNumber<5000; rateCallibrationNumber++)
  {
    gyro_signals();
    rateCallibrationRoll+=rateRoll;
    rateCallibrationPitch+=ratePitch;
    rateCallibrationYaw+=rateYaw;
    delay(1);
  }

  rateCallibrationRoll/=5000;
  rateCallibrationPitch/=5000;
  rateCallibrationYaw/=5000;


}

void loop() {
  analogWrite(motor1,120);
  analogWrite(motor2,120);
  analogWrite(motor3,120);
  analogWrite(motor4,120);
  analogWrite(motor5,120);
  analogWrite(motor6,120);
  

}
