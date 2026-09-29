#include <ESP32Servo.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

Servo myservo;
constexpr uint8_t SERVO_PIN = 4;

constexpr uint8_t I2C_SDA = 1;
constexpr uint8_t I2C_SCL = 2;

void setup(void) {
  Wire.begin(I2C_SDA, I2C_SCL);

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(SERVO_PIN);

  u8g2.begin();
  Serial.begin(9800);
}

uint8_t rotation = 0;
bool isClockwise = true;

void loop(void) {
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(0,10,"Hello World!");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display

  if(rotation >= 180 || rotation <= 0){
    isClockwise = !isClockwise;
  }

  rotation += isClockwise? 1:-1;

  myservo.write(rotation);

  Serial.println(rotation);

  delay(10);  
}
