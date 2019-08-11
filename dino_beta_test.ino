#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif
uint8_t l[8] = {0x00,0x00,0x01,0x03,0x01,0x03,0x01,0x03};
uint8_t r[8] = {0x00,0x10,0x00,0x08,0x10,0x10,0x18,0x10};
uint8_t full[8] = {0x04, 0x06, 0x0c, 0x1d, 0x0e, 0x1e, 0x0f, 0x1e};
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.begin(20, 4);
  lcd.createChar(0, full);
  lcd.createChar(1, l);
  lcd.createChar(2, r);
}

void loop() {
  // put your main code here, to run repeatedly:
while(true){
  for(byte i = 20;i >= 1;i--){
  lcd.clear();
  if(i != 20){
  lcd.setCursor(i,0);
  lcd.printByte(2);
  }
    lcd.setCursor(i-1,0);
  lcd.printByte(1);
  delay(250);
  lcd.clear();
  lcd.setCursor(i-1,0);
  lcd.printByte(0);
  delay(250);
  }
}
}
