#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
uint8_t a1[8] = {0x0,0x0,0x0,0x1f,0x8,0x4,0x2,0x1};
uint8_t a3[8] = {0x0,0x0,0x0,0x1f,0x2,0x4,0x8,0x10};
uint8_t a2[8] = {0x1,0x2,0x4,0x8,0x1f,0x0,0x0,0x0};
uint8_t a4[8] = {0x10,0x8,0x4,0x2,0x1f,0x0,0x0,0x0};
uint8_t b1[8] = {0x4,0xa,0x11,0x1f,0x0,0x0,0x0,0x0};
uint8_t b2[8] = {0x0,0x0,0x0,0x0,0x1f,0x11,0xa,0x4};
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif
void setup() {
  // put your setup code here, to run once:
lcd.init();
  lcd.backlight();
  lcd.begin(20,4);
  lcd.createChar(0, a1);
    lcd.createChar(1, a3);
    lcd.createChar(2, a4);
    lcd.createChar(3, a2);
    lcd.createChar(4, b1);
    lcd.createChar(5, b2);
    lcd.setCursor(0,0);
lcd.printByte(0);
lcd.printByte(1);
lcd.printByte(4);
lcd.printByte(0);
lcd.printByte(1);
lcd.setCursor(0,1);
lcd.printByte(3);
lcd.printByte(2);
lcd.printByte(5);
lcd.printByte(3);
lcd.printByte(2);
    lcd.setCursor(5,0);
lcd.printByte(0);
lcd.printByte(1);
lcd.printByte(4);
lcd.printByte(0);
lcd.printByte(1);
lcd.setCursor(5,1);
lcd.printByte(3);
lcd.printByte(2);
lcd.printByte(5);
lcd.printByte(3);
lcd.printByte(2);
    lcd.setCursor(10,0);
lcd.printByte(0);
lcd.printByte(1);
lcd.printByte(4);
lcd.printByte(0);
lcd.printByte(1);
lcd.setCursor(10,1);
lcd.printByte(3);
lcd.printByte(2);
lcd.printByte(5);
lcd.printByte(3);
lcd.printByte(2);
    lcd.setCursor(15,0);
lcd.printByte(0);
lcd.printByte(1);
lcd.printByte(4);
lcd.printByte(0);
lcd.printByte(1);
lcd.setCursor(15,1);
lcd.printByte(3);
lcd.printByte(2);
lcd.printByte(5);
lcd.printByte(3);
lcd.printByte(2);
    lcd.setCursor(0,2);
lcd.printByte(0);
lcd.printByte(1);
lcd.printByte(4);
lcd.printByte(0);
lcd.printByte(1);
lcd.setCursor(0,3);
lcd.printByte(3);
lcd.printByte(2);
lcd.printByte(5);
lcd.printByte(3);
lcd.printByte(2);
lcd.setCursor(5,2);
lcd.printByte(0);
lcd.printByte(1);
lcd.printByte(4);
lcd.printByte(0);
lcd.printByte(1);
lcd.setCursor(5,3);
lcd.printByte(3);
lcd.printByte(2);
lcd.printByte(5);
lcd.printByte(3);
lcd.printByte(2);
lcd.setCursor(10,2);
lcd.printByte(0);
lcd.printByte(1);
lcd.printByte(4);
lcd.printByte(0);
lcd.printByte(1);
lcd.setCursor(10,3);
lcd.printByte(3);
lcd.printByte(2);
lcd.printByte(5);
lcd.printByte(3);
lcd.printByte(2);
lcd.setCursor(15,2);
lcd.printByte(0);
lcd.printByte(1);
lcd.printByte(4);
lcd.printByte(0);
lcd.printByte(1);
lcd.setCursor(15,3);
lcd.printByte(3);
lcd.printByte(2);
lcd.printByte(5);
lcd.printByte(3);
lcd.printByte(2);
}

void loop() {
  // put your main code here, to run repeatedly:

}
