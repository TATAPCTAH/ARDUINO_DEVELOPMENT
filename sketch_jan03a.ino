#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);
int count = 10;
void setup() {
}
void loop(){
  if(count == 100){count=0;}
   else{lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print(count);
count++;
delay(800);}}
