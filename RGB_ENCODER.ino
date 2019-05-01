#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>
#include "GyverEncoder.h"
#define PIN 6
#define NUMB_PIXELS 16
#define CLK 4//MUST BE CHANGED
#define DT 2//MUST BE CHANGED
#define SW 5//MUST BE CHANGED
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMB_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);
Encoder enc1(CLK, DT, SW);
void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.show();
  enc1.setType(TYPE2);
}
int r = 0,g = 0,b = 0;
int index = 0;
String rgb[3] {"RED","GREEN","BLUE"};
void loop() {
  // put your main code here, to run repeatedly:
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(String(rgb[index]));
  while(true){
  enc1.tick();
  if(enc1.isHolded()){
    break;
    }
    else if(enc1.isRight() && index != 0){index--;}
    else if(enc1.isLeft() && index != 2){index++;}
    if(enc1.isTurn()){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(String(rgb[index]));
    }
  }
  if(index == 0){
    lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(r);
  for(int i = 0;i < 16;i++){
       pixels.setPixelColor(i, pixels.Color(r, g, b));
      }
      pixels.show();
  while(true){
      enc1.tick();
    if(enc1.isHolded()){
    break;
    }
    else if(enc1.isLeft() && r < 255){r+=5;}
    else if(enc1.isRight() && r != 0){r-=5;}
    if(enc1.isTurn()){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(r);
  for(int i = 0;i < 16;i++){
       pixels.setPixelColor(i, pixels.Color(r, g, b));
      }
      pixels.show();
    }
  }
  }
  else if(index == 1){
    lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(g);
  for(int i = 0;i < 16;i++){
       pixels.setPixelColor(i, pixels.Color(r, g, b));
      }
      pixels.show();
  while(true){
      enc1.tick();
    if(enc1.isHolded()){
    break;
    }
    else if(enc1.isLeft() && g < 255){g+=5;}
    else if(enc1.isRight() && g != 0){g-=5;}
    if(enc1.isTurn()){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(g);
  for(int i = 0;i < 16;i++){
       pixels.setPixelColor(i, pixels.Color(r, g, b));
      }
      pixels.show();
    }
  }
    }
  else{
    lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(r);
  for(int i = 0;i < 16;i++){
       pixels.setPixelColor(i, pixels.Color(r, g, b));
      }
      pixels.show();
  while(true){
      enc1.tick();
    if(enc1.isHolded()){
    break;
    }
    else if(enc1.isLeft() && b < 255){b+=5;}
    else if(enc1.isRight() && b != 0){b-=5;}
    if(enc1.isTurn()){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(b);
  for(int i = 0;i < 16;i++){
       pixels.setPixelColor(i, pixels.Color(r, g, b));
      }
      pixels.show();
    }
  }
    }
    

}
