#include <iarduino_DHT.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_NeoPixel.h>
#include <MemoryFree.h>
#include <BME280I2C.h>
#include <Wire.h> 
#define PIN 6
#define NUMB_PIXELS 16
#define sound {tone(3,100);delay(500);noTone(3);delay(500);}
//File directory_in_cd_card;
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);
//iarduino_DHT sensor(2);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMB_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
BME280I2C bme;
bool metric = true;
int delay_value = 50;
int s1[7]{7,6,5,4,3,2,1};
int s2[7]{9,10,11,12,13,14,15};
int s3[7]{1,2,3,4,5,6,7};
int s4[7]{15,14,13,12,11,10,9};
int m[23]{0,0,0,0,0,0,0,255,255/2,255/4,255/8,255/16,255/32,255/64,255/128,0,0,0,0,0,0,0,0};
const int chipSelect = 53;
void smooth_green() {
  delay(500);
  for (int l = 0; l < 255; l += 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, l, 0));
    }
    pixels.show();
    delay(25);
  }
  delay(100);
  for (int l = 255; l >= 0; l -= 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, l, 0));
    }
    pixels.show();
    delay(25);
  }
}
void smooth_blue() {
  delay(500);
  for (int l = 0; l < 255; l += 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, l));
    }
    pixels.show();
    delay(25);
  }
  delay(100);
  for (int l = 255; l >= 0; l -= 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, l));
    }
    pixels.show();
    delay(25);
  }
}
void cheres(){
  for(int i = 0;i < 16;i++){
    if(i%2 == 0){}
    else{
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
      pixels.show();
      delay(20);
    }
    for(int i = 0;i < 16;i++){
    if(i%2 == 0){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
    else{
      }
      pixels.show();
      delay(20);
    }
    for(int i = 0;i < 16;i++){
    if(i%2 == 0){}
    else{
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      }
      pixels.show();
      delay(20);
    }
    for(int i = 0;i < 16;i++){
    if(i%2 == 0){}
    else{
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
      pixels.show();
      delay(20);
    }
    for(int i = 0;i < 16;i++){
    if(i%2 == 0){
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      }
    else{
      }
      pixels.show();
      delay(20);
    }
    for(int i = 0;i < 16;i++){
    if(i%2 == 0){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
    else{
      }
      pixels.show();
      delay(20);
    }
  }
void ring() {
    for (int i = 0; i < 16; ++i)
    {
      pixels.setPixelColor(i % 16, pixels.Color(31, 236, 240));
      pixels.setPixelColor((i + 1) % 16, pixels.Color(255/3, 0, 0));
      pixels.setPixelColor((i + 2) % 16, pixels.Color(255/2, 0, 0));
      pixels.setPixelColor((i + 3) % 16, pixels.Color(255, 0, 0));
      pixels.show();
      delay(delay_value);
    }
}
void blinking() {
  delay(500);
  for (int i = 0; i < 16; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
  }
  pixels.show();
  delay(500);
  for (int i = 0; i < 16; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
  delay(500);
  for (int i = 0; i < 16; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
  }
  pixels.show();
  delay(500);
  for (int i = 0; i < 16; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}
void smooth_red() {
  delay(500);
  for (int l = 0; l < 255; l += 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(l, 0, 0));
    }
    pixels.show();
    delay(25);
  }
  delay(100);
  for (int l = 255; l >= 0; l -= 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(l, 0, 0));
    }
    pixels.show();
    delay(25);
  }
}
void sending() {
  pixels.show();
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.setPixelColor(8, pixels.Color(0, 0, 255));
  for (int i = 0; i < 16; i++) {
    for(int j = 0;j < 7;j++){
    pixels.setPixelColor(s1[j], pixels.Color(m[i+j], 0, 0));
    pixels.setPixelColor(s2[j], pixels.Color(m[i+j], 0, 0));
    delay(5);
    pixels.show();
    }
  }
  for (int i = 0; i < 16; i++) {
    for(int j = 0;j < 7;j++){
    pixels.setPixelColor(s3[j], pixels.Color(m[i+j], 0, 0));
    pixels.setPixelColor(s4[j], pixels.Color(m[i+j], 0, 0));
    delay(5);
    pixels.show();
    }
  }
}
void searching_from_cd() {
  pixels.show();
  for (int i = 0; i < 4; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.setPixelColor(i + 4, pixels.Color(0, 255, 0));
    pixels.setPixelColor(i + 8, pixels.Color(0, 255, 0));
    pixels.setPixelColor(i + 12, pixels.Color(0, 255, 0));
    pixels.show();
    delay(50);
  }
  delay(200);
  for (int i = 0; i < 4; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.setPixelColor(i + 4, pixels.Color(0, 0, 0));
    pixels.setPixelColor(i + 8, pixels.Color(0, 0, 0));
    pixels.setPixelColor(i + 12, pixels.Color(0, 0, 0));
    pixels.show();
    delay(50);
  }
}
void full_ring() {
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 16; ++i)
    {
      pixels.setPixelColor(i % 16, pixels.Color(255 / 16, 0, 0));
      pixels.setPixelColor((i + 1) % 16, pixels.Color(255 / 15, 0, 0));
      pixels.setPixelColor((i + 2) % 16, pixels.Color(255 / 14, 0, 0));
      pixels.setPixelColor((i + 3) % 16, pixels.Color(255 / 13, 0, 0));
      pixels.setPixelColor((i + 4) % 16, pixels.Color(255 / 12, 0, 0));
      pixels.setPixelColor((i + 5) % 16, pixels.Color(255 / 11, 0, 0));
      pixels.setPixelColor((i + 6) % 16, pixels.Color(255 / 10, 0, 0));
      pixels.setPixelColor((i + 7) % 16, pixels.Color(255 / 9, 0, 0));
      pixels.setPixelColor((i + 8) % 16, pixels.Color(255 / 8, 0, 0));
      pixels.setPixelColor((i + 9) % 16, pixels.Color(255 / 7, 0, 0));
      pixels.setPixelColor((i + 10) % 16, pixels.Color(255 / 6, 0, 0));
      pixels.setPixelColor((i + 11) % 16, pixels.Color(255 / 5, 0, 0));
      pixels.setPixelColor((i + 12) % 16, pixels.Color(255 / 4, 0, 0));
      pixels.setPixelColor((i + 13) % 16, pixels.Color(255 / 3, 0, 0));
      pixels.setPixelColor((i + 14) % 16, pixels.Color(255 / 2, 0, 0));
      pixels.setPixelColor((i + 15) % 16, pixels.Color(255, 0, 0));
      pixels.show();
      delay(delay_value);
    }
  }
}
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pixels.begin();
  pixels.show();
  while(!bme.begin()){
    blinking();
  }
  delay(1000);
  for (int i = 0; i < 8; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.show();
    delay(100);
  }
  pixels.setPixelColor(10, pixels.Color(0, 0, 255));
  pixels.show();
  delay(100);
  pixels.setPixelColor(13, pixels.Color(0, 0, 255));
  pixels.show();
  delay(2000);
  for (int i = 0; i < 16; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
  for (int i = 0; i < 16; ++i)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
  }
  pixels.show();
}
void printBME280Data(){
  float temp(NAN), humi(NAN), pres(NAN);
   uint8_t pressureUnit(3);
   bme.read(pres, temp, humi, metric, pressureUnit);
   int temp1 = int(temp);
   int humi2 = int(humi);
   int bin1[8];
   int bin2[8];
   for(int i = 0;i < 8;i++){
    bin1[i] = temp1%2;
    temp1/=2;
    }
   for(int i = 0;i < 8;i++){
    bin2[i] = humi2%2;
    humi2/=2;
    }
    Serial.println();
    for(int i = 7;i >= 0;i--){
      Serial.print(bin1[i]);
      }
    Serial.println();
    for(int i = 7;i >= 0;i--){
      Serial.print(bin2[i]);
      }
   lcd.begin(16,2);
   lcd.setCursor(0, 0);
   lcd.write("T:");
   lcd.print(int(temp));
   lcd.write(metric ? 'C' :'F');
   lcd.write(" H:");
   lcd.print(int(humi));
   lcd.write("%RH");
   lcd.setCursor(0, 1);
   lcd.write("P:");
   lcd.print(pres);
   lcd.write("atm");
}
void printBME280CalculatedData(){
  float altitude = bme.alt(metric);
  float dewPoint = bme.dew(metric);
  lcd.begin(16,2);
  lcd.setCursor(0, 0);
  lcd.write("Alt:");
  lcd.print(altitude);
  lcd.write((metric ? "m" : "ft"));
  lcd.setCursor(0, 1);
  lcd.write("Dp:");
  lcd.print(dewPoint);
  lcd.write(metric ? 'C' :'F');

}
int integral_sum = 0, step_color = 255 / 16;
void loop() {
  ring();
  printBME280Data();
  ring();
  ring();
  printBME280CalculatedData();
  ring();
  smooth_green();
  smooth_red();
  smooth_blue();
  searching_from_cd();
  blinking();
  full_ring();
  sending();
  cheres();
}
