
#include "Setup_SSD1306.hpp"

LGFX display;

void setup(void)
{
  Serial.begin(115200);
  display.init();
  display.setBrightness(255);
  display.setTextSize((std::max(display.width(), display.height()) + 255) >> 8);
  display.setRotation(0);
  display.setColorDepth(1);
  display.fillScreen(TFT_WHITE);
  Serial.printf("width: %d, height: %d\n", display.width(), display.height());
  delay(1000);
}

uint32_t count = ~0;
void loop(void)
{
  // for (uint8_t rotation = 0; rotation < 8; ++rotation)
  // {
  //   display.fillScreen(TFT_BLACK);
  //   display.startWrite();
  //   display.setRotation(rotation);
  //   display.setColorDepth(1);

  //   display.setTextColor(TFT_WHITE);
  //   display.drawString("Hello", 30, 16);
  //   display.drawNumber(display.getRotation(), 16, 16);

  //   display.endWrite();
  //   delay(500);
  // }
  display.fillScreen(TFT_BLACK);
  display.drawPixel(0, 0, TFT_WHITE);
  delay(500);
  display.drawPixel(display.width()-1, 0, TFT_WHITE);
  display.drawPixel(display.width()-2, 1, TFT_WHITE);
  display.drawPixel(display.width()-3, 2, TFT_WHITE);
  delay(500);
  display.drawPixel(0, display.height()-1, TFT_WHITE);
  delay(500);
  display.drawPixel(display.width()-1, display.height()-1, TFT_WHITE);
  delay(500);
  display.drawPixel(display.width()/2, display.height()/2, TFT_WHITE);
  delay(500);
  display.drawFastVLine(10, 0, 63, TFT_WHITE); 
  delay(500);
  display.drawFastHLine(0, 10, 127, TFT_WHITE); 
  delay(500);
  display.fillRect(display.width()/2-20, display.height()/2-20, 40, 40, TFT_WHITE);
  delay(500);
  display.fillRect(display.width()/2-20, display.height()/2-20, 40, 40, TFT_BLACK);
  display.fillRoundRect(display.width()/2-20, display.height()/2-20, 40, 40, 5, TFT_WHITE); 
  // for (uint16_t b = 0; b < display.height(); ++b)
  // {
  //   display.drawFastHLine(0, b, display.width()-1, b+1); 
  // }
  // delay(2000);
  // for (uint16_t a = 0; a < display.width()/2; ++a)
  // {
  //   display.fillRect(a, 0, display.width()-(2*a), display.height()-1, 255);
  //   delay(300);
  //   display.fillScreen(TFT_BLACK);
  // }
  delay(2000);
}
