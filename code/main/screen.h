#pragma once
#include <Arduino.h>
#include <U8g2lib.h>

#define USE_U8G2

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void tickU8G2(uint8_t rotation){
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  String display_string = "Hello World! " + String(rotation);
  Serial.println(display_string);
  u8g2.drawStr(0,10, display_string.c_str());	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
}