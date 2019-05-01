#include <LiquidCrystal_I2C.h>
#include <GyverEncoder.h>
#include <BME280I2C.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h> 
#define PIN 6
#define NUMB_PIXELS 16
#define CLK 7//MUST BE CHANGED
#define DT 8//MUST BE CHANGED
#define SW 9//MUST BE CHANGED
LiquidCrystal_I2C lcd(0x3f, 20, 4);//MUST BE CHANGED
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMB_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
BME280I2C bme;
Encoder enc1(CLK, DT, SW);
bool metric = true;
void setup() {
  pinMode(X);//MUST BE CHANGED
  pinMode(X);//MUST BE CHANGED
    pixels.begin();
  pixels.show();
  lcd.init();
  lcd.backlight();
  while(!bme.begin()){
    blinking();
  }
  delay(1000);
  lcd.setCursor(0,0);
  lcd.write("PROJECT: BOX");
  lcd.setCursor(0,1);
  lcd.write("MILITARY DEVELOPMENT");
  delay(1000);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.write("STAY AWAY");
  lcd.setCursor(0,1);
  lcd.write("FROM PLANT");
  delay(1000);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.write("GOOD LUCK");
  lcd.setCursor(0,1);
  lcd.write("ENJOY USING)");
  delay(1000);
}
int get_th(int index){
  float temp(NAN), humi(NAN), pres(NAN);
   uint8_t pressureUnit(3);
   bme.read(pres, temp, humi, metric, pressureUnit);
   if(index == 0){
    return temp;
    }
   else{
    return humi;
    }
  }
  int get_w(){
    return analogRead(X);//MUST BE CHANGED
    }
    int get_l(){
    return analogRead(X);//MUST BE CHANGED
    }
int con = 0;
String choose[4]{"Change: Temp","Change: Hum","Change: Water","Change: Atm SOON"}
void loop() {
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.write("IF YOU WANT TO START");
  lcd.setCursor(0, 1);
  lcd.write("JUST SCROLL OR TOUCH");
  lcd.setCursor(0, 2);
  lcd.write("ENCODER, WICH ");
  while(true){
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.write("Please scrool");
  lcd.setCursor(0, 1);
  lcd.write("Encoder to see");
  lcd.setCursor(0, 2);
  lcd.write("Methods");
  enc1.tick();
  while(not enc1.isTurn()){enc1.tick();}
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.write("Change: Temp");
  lcd.setCursor(0, 1);
  lcd.write("Change: Hum");
  lcd.setCursor(0, 2);
  lcd.write("Change: Water");
  lcd.setCursor(0, 3);
  lcd.write("Change: Atm SOON");
  while(true){
    if (enc1.isRight() && con != 0){con--;}
  else if (enc1.isLeft() && con != 2){con++;}
  else if (enc1.isHolded()){break;}
  lcd.setCursor(0, con);
  lcd.write("                ");
  lcd.write(choose[con]);
    }
    
    if(con == 0){
      int temp = get_th(0);
  lcd.setCursor(0, 0);
  lcd.write("                ");
  while(true){
    if (enc1.isRight() && temp!= XXXXXXXXX){temp--;}
  else if (enc1.isLeft() && temp != XXXXXXXXX){temp++;}
  else if (enc1.isHolded()){break;}
  lcd.setCursor(0, 0);
  lcd.write("                ");
  lcd.write("Temp = " + temp);
  }
  }
    else if(con == 1){
      int humi = get_th(1);
      while(true){
       enc1.tick();
      if (enc1.isRight() && humi != XXXXXXXXXX){humi--;}
  else if (enc1.isLeft() && humi != XXXXXXXXXX){humi++;}
  else if (enc1.isHolded()){break;}
  lcd.setCursor(0, 1);
  lcd.write("                ");
  lcd.write("Hum = " + humi);
      }
    }
    else if(con == 2){
      int water = get_w();
      while(true){
        enc1.tick();
      if (enc1.isRight() && water != XXXXXXXXXXXXXX){water--;}
  else if (enc1.isLeft() && water != XXXXXXXXXXXXXX){water++;}
  else if (enc1.isHolded()){break;}
  lcd.setCursor(0, 2);
  lcd.write("                ");
  lcd.write("Water = " + water);
      }
    }
//    else{
//      lcd.setCursor(0, 3);
//  lcd.write("                ");
//  lcd.write("Atm = " + );
//      }

}
}
