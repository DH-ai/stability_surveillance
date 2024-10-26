#define Motor1 3
#define Motor2 5
#define Motor3 6
#define Motor4 9
#define Motor5 10
#define Motor6 11
#include <Wire.h>
#include <Servo.h>
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
Servo motor5;
Servo motor6;

float ratePitch, rateRoll, rateYaw; 
float accValX, accValY, accValZ; 

float rateCallibrationPitch, rateCallibrationRoll, rateCallibrationYaw;
float rateCallibrationAccX, rateCallibrationAccY, rateCallibrationAccZ;

int rateCallibrationNumber;


void gyro_signals(void){
      Wire.beginTransmission(0x68);//hex for starting communication
      Wire.write(0x1A);//low pass filter selection hex
      Wire.write(0x00);//change this to select different low pass filters.(values allowed: 0-256hz, 1-188hz, 2-98hz, 3-42hz, 4-20hz, 5-10hz, 6-5hz)
      Wire.endTransmission();

      Wire.beginTransmission(0x68);//hex for starting communication
      Wire.write(0x1B);//gyro callibration
      Wire.write(0x08);//change this to select different gyro callibrations.
      Wire.endTransmission();

      Wire.beginTransmission(0x68);//hex for stating communication
      Wire.write(0x43);//import gyro output

      Wire.endTransmission();

      Wire.requestFrom(0x68,6);

      int16_t gyroX= Wire.read()<<8 | Wire.read(); 
      int16_t gyroY= Wire.read()<<8 | Wire.read(); 
      int16_t gyroZ= Wire.read()<<8 | Wire.read(); 

      Wire.beginTransmission(0x68);
      Wire.write(0x1C);     //Acc calibration
      Wire.write(0x08);     // value range for +-8g
      Wire.endTransmission();
      Wire.requestFrom(0x68,6);

      int16_t accX= Wire.read()<<8 | Wire.read(); 
      int16_t accY= Wire.read()<<8 | Wire.read(); 
      int16_t accZ= Wire.read()<<8 | Wire.read();

      rateRoll=(float)gyroX/256;
      ratePitch=(float)gyroY/256;
      rateYaw=(float)gyroZ/256;

      accValX=(float)accX/256;
      accValY=(float)accY/256;
      accValZ=(float)accZ/256;     


}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor1.attach(Motor1);
  motor2.attach(Motor2);
  motor3.attach(Motor3);
  motor4.attach(Motor4);
  motor5.attach(Motor5);
  motor6.attach(Motor6);

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

    rateCallibrationAccX+=accValX;
    rateCallibrationAccY+=accValY;
    rateCallibrationAccZ+=accValZ;


    delay(1);
  }

  rateCallibrationRoll/=5000;
  rateCallibrationPitch/=5000;
  rateCallibrationYaw/=5000;
  rateCallibrationAccX/=5000;
  rateCallibrationAccY/=5000;
  rateCallibrationAccZ/=5000;


}

void loop() {
  motor1.writeMicroseconds(1500);  
  motor2.writeMicroseconds(1500);  
  motor3.writeMicroseconds(1500);  
  motor4.writeMicroseconds(1500);  
  motor5.writeMicroseconds(1500);  
  motor6.writeMicroseconds(1500);  
  gyro_signals();
  rateRoll-=rateCallibrationRoll;
  ratePitch-=rateCallibrationPitch;
  rateYaw-=rateCallibrationYaw;
  accValX -= rateCallibrationAccX;
  accValY -= rateCallibrationAccY;
  accValZ -= rateCallibrationAccZ;
  Serial.print("Roll Rate   =");
  Serial.print(rateRoll);
  Serial.print("\nPitch Rate  =");
  Serial.print(ratePitch);
  Serial.print("\nYaw Rate    =");
  Serial.println(rateYaw);
  Serial.print("AcclerationX   =");
  Serial.print(accValX);
  Serial.print("\nAcclerationY  =");
  Serial.print(accValY);
  Serial.print("\nAcclerationZ    =");
  Serial.println(accValZ);
  
  delay(50);
  

}
