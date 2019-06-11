#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define X A0
#define Y A1
#define CLK 2
String massiv[10] = {"church","fish","tooth","violent","nostalgic","ducks","receive","rhyme","deliver","expect"};
String massiv_without[10] = {"___r__","__s_","___t_","___l___","__s______","__c__","____i__","_h___","____v__","__p___"};
char letter1[13] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'};
char letter2[13] = {'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
byte x_g = 0;
byte y_g = 0;
char choise = 'a';
bool half = true;
void setup() {
  // put your setup code here, to run once:
 lcd.init();
  lcd.backlight();
    lcd.begin(20,4);
    pinMode(X,INPUT);
  pinMode(Y,INPUT);
  pinMode(CLK,INPUT);
  digitalWrite(CLK, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Welcome to the game:");
    lcd.setCursor(2,2);
    lcd.print("Guess the word");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    for(int i = 0;i < 13;i++){
      lcd.print(letter1[i]);
      }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(byte i = 0;i < 10;i++){
    String fake = massiv[i];
      String without = massiv_without[i];
      lcd.setCursor(0,2);
      lcd.print(massiv_without[i]);
  while(fake != without){
    while(digitalRead(CLK) != 0){
      if(analogRead(X) >= 768 && x_g < 19){
        lcd.setCursor(x_g,y_g);
        lcd.noBlink();
        x_g++;
        lcd.setCursor(x_g,y_g);
        lcd.blink();
        }
      if(analogRead(Y) >= 786 && y_g > 0){
        lcd.setCursor(x_g,y_g);
        lcd.noBlink();
        y_g--;
        lcd.setCursor(x_g,y_g);
        lcd.blink();
        }
      if(analogRead(X) <= 256 && x_g > 0){
        lcd.setCursor(x_g,y_g);
        lcd.noBlink();
        x_g--;
        lcd.setCursor(x_g,y_g);
        lcd.blink();
        }
      if(analogRead(Y) <= 256 && y_g < 3){
        lcd.setCursor(x_g,y_g);
        lcd.noBlink();
        y_g++;
        lcd.setCursor(x_g,y_g);
        lcd.blink();
        }
        delay(100);
      }
      delay(1000);
      if(x_g < 13 && y_g == 0){
        while(digitalRead(CLK) != 0){
        if(analogRead(Y) <= 256){half = false;lcd.setCursor(0,0);
        for(int i = 0;i < 13;i++){
      lcd.print(letter2[i]);
      }}
        else if(analogRead(Y) >= 786){half = true;lcd.setCursor(0,0);
        for(int i = 0;i < 13;i++){
      lcd.print(letter1[i]);
      }
        }
        }
        delay(1000);
        while(digitalRead(CLK) != 0){
          if(analogRead(X) >= 768 && x_g < 12){
        lcd.setCursor(x_g,y_g);
        lcd.noBlink();
        x_g++;
        lcd.setCursor(x_g,y_g);
        lcd.blink();
        }
      if(analogRead(X) <= 256 && x_g > 0){
        lcd.setCursor(x_g,y_g);
        lcd.noBlink();
        x_g--;
        lcd.setCursor(x_g,y_g);
        lcd.blink();
        }
        delay(100);
          }
          if(half == true){
            choise = letter1[x_g];
            lcd.setCursor(0,3);
            lcd.print(choise);
            }
          else{
            choise = letter2[x_g];
            lcd.setCursor(0,3);
            lcd.print(choise);
            }
        }
        else if(x_g < fake.length() && y_g == 2){
          if(choise == fake[x_g]){
          lcd.setCursor(x_g,y_g);
          lcd.print(choise);
          lcd.setCursor(0,3);
            lcd.print(" ");
          }
          else{
            choise = 'a';
            lcd.setCursor(15,2);
            lcd.print("WRONG");
            delay(500);
            lcd.setCursor(15,2);
            lcd.print("     ");
            }
          }
    }
  }
}
