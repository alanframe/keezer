#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_MOSI   D7
#define OLED_CLK   D5
#define OLED_DC    D1
#define OLED_CS    D8
#define OLED_RESET D3
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void MDisplayInit(){
display.begin(SSD1306_SWITCHCAPVCC);
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println("Kegerator");
display.display();
delay(2000);
}
void MDisplayNorm( float FreezerTemp , float Beer1Temp , float Beer2Temp , float SetTemp, bool Cooling) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Ft=");
  display.print(FreezerTemp);
  display.print(" B1t=");
  display.print(Beer1Temp);
  display.print(" B2t=");
  display.print(Beer2Temp);
  display.display();
  delay(2000);
}
