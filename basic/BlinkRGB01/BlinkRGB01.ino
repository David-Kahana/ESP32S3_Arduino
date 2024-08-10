const int d = 250;
const int b = RGB_BRIGHTNESS - 32;

void setup() 
{
  
}

void loop() 
{
  neopixelWrite(RGB_BUILTIN,b,0,0); // Red
  delay(d);
  neopixelWrite(RGB_BUILTIN,0,b,0); // Green
  delay(d);
  neopixelWrite(RGB_BUILTIN,0,0,b); // Blue
  delay(d);
  neopixelWrite(RGB_BUILTIN,0,0,0); // Off / black
  delay(d);
}
