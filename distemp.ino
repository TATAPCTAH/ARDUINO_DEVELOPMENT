#include <BME280I2C.h>
#include <Wire.h>
#include <TFT_ILI9341.h>
#include <SPI.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#define TFT_BROWN 0x38E0
#define TFT_GREY 0x7BEF
BME280I2C bme;
TFT_ILI9341 tft = TFT_ILI9341();
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
bool metric = true;
int i = 0;
byte massiv_t[320];
byte massiv_h[320];
byte massiv_p[320];
void printBME280Data() {
  float temp(NAN), hum(NAN), pres(NAN);
  uint8_t pressureUnit(3);                                           // unit: B000 = Pa, B001 = hPa, B010 = Hg, B011 = atm, B100 = bar, B101 = torr, B110 = N/m^2, B111 = psi
  bme.read(pres, temp, hum, metric, pressureUnit);// Parameters: (float& pressure, float& temp, float& humidity, bool celsius = false, uint8_t pressureUnit = 0x0)
  massiv_t[i] = 75 - int(temp)/2;
  massiv_h[i] = 160 - int(hum)/2;
  massiv_p[i] = 210 + pres*250;
  for(int j = 0;j < 320;++j){
    if(massiv_t[j] != -1){
  tft.drawPixel(j, massiv_t[j], TFT_BLUE);
  tft.drawPixel(j, massiv_h[j], TFT_GREEN);
  tft.drawPixel(j, massiv_p[j], TFT_YELLOW);
    }
  }
    tft.setCursor(0, 0, 2);
    tft.print("Temp: ");
    tft.print(temp);
    tft.print(String('C'));
//    tft.print("°"+ String(metric ? 'C' :'F'));
    tft.setCursor(0, 85, 2);
    tft.print("Humidity: ");
    tft.print(hum);
    tft.print("% RH");
    tft.setCursor(0, 160, 2);
    tft.print("Pressure: ");
    tft.print(pres);
    tft.println(" atm");
}
void printBME280CalculatedData() {
  float altitude = bme.alt(metric);
  float dewPoint = bme.dew(metric);
  tft.setCursor(0, 0, 2);
  tft.print("Altitude: ");
  tft.print(altitude);
  tft.println((metric ? "m" : "ft"));
  tft.print("Dew point: ");
  tft.print(dewPoint);
  tft.println("°" + String(metric ? 'C' : 'F'));
}
void setup() {
  // put your setup code here, to run once:
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  tft.init();
  tft.setRotation(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  for(int x = 0;x < 320;x++){
    massiv_t[x] = -1;
    massiv_h[x] = -1;
    massiv_p[x] = -1;
    }
  while (!bme.begin()) {
    delay(1000);
  }
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  myDFPlayer.volume(10);
  myDFPlayer.play(1);//Set volume value. From 0 to 30
  for(int j = 0;j < 319;j++){
//    tft.drawPixel(j, 65, TFT_WHITE);
//    tft.drawPixel(j, 135, TFT_WHITE);
//    tft.drawPixel(j, 210, TFT_WHITE);
    //16
    tft.drawPixel(j, 25, TFT_GREY);
    tft.drawPixel(j, 84, TFT_GREY);
    tft.drawPixel(j, 109, TFT_GREY);
    tft.drawPixel(j, 159, TFT_GREY);
    tft.drawPixel(j, 184, TFT_GREY);
    tft.drawPixel(j, 234, TFT_GREY);
    delay(5);
    }
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
//  tft.setTextColor(TFT_WHITE, TFT_BLACK);
if(i == 320){
  i = 0;
       for(int j = 0;j < 320;++j){
    if(massiv_t[j] != -1){
  tft.drawPixel(j, massiv_t[j], TFT_BLACK);
  tft.drawPixel(j, massiv_h[j], TFT_BLACK);
  tft.drawPixel(j, massiv_p[j], TFT_BLACK);
    }
    }
    for(int x = 0;x < 320;x++){
    massiv_t[x] = -1;
    massiv_h[x] = -1;
    massiv_p[x] = -1;
    }
//  i--;
//  while(true){
//    for(int j = 0;j < 320;++j){
//    if(massiv_t[j] != -1){
//  tft.drawPixel(j, massiv_t[j], TFT_BLACK);
//  tft.drawPixel(j, massiv_h[j], TFT_BLACK);
//  tft.drawPixel(j, massiv_p[j], TFT_BLACK);
//    }
//    }
//    for(int g = 0;g < 319;g++){
//      massiv_t[g] = massiv_t[g+1];
//      massiv_h[g] = massiv_h[g+1];
//      massiv_p[g] = massiv_p[g+1];
//      }
//    printBME280Data();
//    delay(100);
//    }
  }
else{
  printBME280Data();
  i++;
  delay(100);
}
}
