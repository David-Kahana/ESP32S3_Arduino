
#include "Setup_SSD1306.hpp"

LGFX display;

void setup(void)
{
  display.init();
  display.setBrightness(255);
  display.setTextSize((std::max(display.width(), display.height()) + 255) >> 8);
  display.fillScreen(TFT_BLACK);
}

uint32_t count = ~0;
void loop(void)
{
  display.fillScreen(TFT_BLACK);
  display.startWrite();
  display.setRotation(++count & 7);
  display.setColorDepth(1);

  display.setTextColor(TFT_WHITE);
  display.drawString("Hello", 30, 16);
  display.drawNumber(display.getRotation(), 16, 16);

  display.endWrite();
  delay(1000);
}
