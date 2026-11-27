// #include "screen.h"
#include <ESP32Servo.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#include <Wire.h>

//Brown: Ground, Red: Vcc, Yellow: pin 4
Servo myservo;
constexpr uint8_t SERVO_PIN = 4;

constexpr uint8_t I2C_SDA = 1;
constexpr uint8_t I2C_SCL = 2;

void setup(void) {
  Wire.begin(I2C_SDA, I2C_SCL);

  //Servo initialization
  ESP32PWM::allocateTimer(0);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(SERVO_PIN);

  //outpu initial
  Serial.begin(9800);

  //turn on u8g2 if used
#ifdef USE_U8G2
  u8g2.begin();
#endif
}

uint8_t rotation = 0;
bool isClockwise = true;

void loop(void) {
  //tick u8g2
#ifdef USE_U8G2
  tickU8G2(rotation);
#endif

  // rotation += isClockwise? 1:-1;
  // if(rotation >= 180 || rotation <= 0){
  //   isClockwise = !isClockwise;
  // }

  
  myservo.write(rotation);
  delay(10);  
}
