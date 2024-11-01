#define Motor1 3
#define Motor2 5
#define Motor3 6
#define Motor4 9
#define Motor5 10
// #define Motor6 11
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

  Wire.beginTransmission(0x68); 
  Wire.write(0x1C);     //Acc calibration 28
  Wire.write(0x08);     // value range for +-8g
  Wire.endTransmission();

  Wire.beginTransmission(0x68);//hex for stating communication
  Wire.write(0x3B);//import Acc output
  Wire.endTransmission(false);

  Wire.requestFrom(0x68,6,true);



  int16_t accX= Wire.read()<<8 | Wire.read(); 
  int16_t accY= Wire.read()<<8 | Wire.read(); 
  int16_t accZ= Wire.read()<<8 | Wire.read();


  accValX=(float)accX/4096 ;
  accValY=(float)accY/4096 ;
  accValZ=(float)accZ/4096 ;     


}



void setup() {
  Serial.begin(9600);
  Wire.setClock(400000);
  Wire.begin();
  delay(250);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();


}

void loop() {

  gyro_signals();
  // rateRoll-=rateCallibrationRoll;
  // ratePitch-=rateCallibrationPitch;
  // rateYaw-=rateCallibrationYaw;
  // accValX -= rateCallibrationAccX;
  // accValY -= rateCallibrationAccY;
  // accValZ -= rateCallibrationAccZ;
  // Serial.print("Roll Rate   =");
  // Serial.print(rateRoll);
  // Serial.print("\nPitch Rate  =");
  // Serial.print(ratePitch);
  // Serial.print("\nYaw Rate    =");
  // Serial.println(rateYaw);
  Serial.print("AX: "); Serial.print(accValX* 9.81/2);
  Serial.print("\tAY:= "); Serial.print(accValY* 9.81/2);
  Serial.print("\tAZ:= "); Serial.println(accValZ* 9.81/2);

  delay(1000);


}
