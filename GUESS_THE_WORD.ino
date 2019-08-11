#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define X A0
#define Y A1
#define CLK 2
String massiv[10] = {"church", "fish", "tooth", "violent", "nostalgic", "ducks", "receive", "rhyme", "deliver", "expect"};
String massiv_without[10] = {"___r__", "__s_", "___t_", "___l___", "__s______", "__c__", "____i__", "_h___", "____v__", "__p___"};
String definition[] = {
  "a building used for public Christian worship",
  "an animal that lives in water, is covered with scales",
  "white objects in the mouth that are used for biting and chewing",
  "using force to hurt or attack",
  "feeling happy and sadness when you think about things that happened in past",
  "a bird that lives by water and has webbed feet and short neck",
  "to get or be given something",
  "a word that has the same last sound as another word",
  "to give, direct",
  "to think or believe something will happen, or someone will arrive"
};
char letter1[13] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'};
char letter2[13] = {'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
byte word_index = 0;
byte y_g = 0;
byte letter_index = 0;
char choise = 'a';
bool half = true;
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.begin(20, 4);
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(CLK, INPUT);
  digitalWrite(CLK, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Welcome to the game:");
  lcd.setCursor(2, 2);
  lcd.print("Guess the word");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (byte i = 0; i < 10; i++) {
    String fake = massiv[i];
    String without = massiv_without[i];
    byte word_size = without.length();
    while (fake != without) {
      lcd.setCursor(0, 2);
    lcd.print(without);
    lcd.setCursor(0, 0);
  for (int i = 0; i < 13; i++) {
    lcd.print(letter1[i]);
  }
  lcd.setCursor(17,3);
  lcd.print("DEF");
   lcd.setCursor(13,0);
            lcd.print(char(127));
      while (digitalRead(CLK) != 0) {
        if (analogRead(Y) >= 786 && y_g > 0) {//1 and 2
          if(y_g == 1){//1
            lcd.setCursor(word_size,2);
            lcd.print(" ");
            }
          else{//2
            lcd.setCursor(16,3);
            lcd.print(" ");
            }
          y_g--;
          if(y_g == 1){//1
            lcd.setCursor(word_size,2);
            lcd.print(char(127));
            }
          else{//0
            lcd.setCursor(13,0);
            lcd.print(char(127));
            }
          delay(350);
        }
        if (analogRead(Y) <= 256 && y_g < 2) {//0 and 1
          if(y_g == 0){//0
            lcd.setCursor(13,0);
            lcd.print(" ");
            }
          else{//1
            lcd.setCursor(word_size,2);
            lcd.print(" ");
            }
          y_g++;
          if(y_g == 1){//1
            lcd.setCursor(word_size,2);
            lcd.print(char(127));
            }
          else{//2
            lcd.setCursor(16,3);
            lcd.print(char(126));
            }
          delay(350);
        }
      }
      while (digitalRead(CLK) == 0) {}


      
      if (y_g == 0) {
        while (digitalRead(CLK) != 0) {
          if (analogRead(Y) <= 256) {
            half = false; lcd.setCursor(0, 0);
            for (int j = 0; j < 13; j++) {
              lcd.print(letter2[j]);
            }
          }
          else if (analogRead(Y) >= 786) {
            half = true; lcd.setCursor(0, 0);
            for (int j = 0; j < 13; j++) {
              lcd.print(letter1[j]);
            }
          }
        }
        while (digitalRead(CLK) == 0) {}
        lcd.setCursor(0, 0);
        lcd.blink();
        while (digitalRead(CLK) != 0) {
          if (analogRead(X) >= 786 && letter_index < 13) {
            letter_index++;
            lcd.setCursor(letter_index, 0);
            lcd.blink();
          }
          else if (analogRead(X) <= 256 && letter_index > 0) {
            letter_index--;
            lcd.setCursor(letter_index, 0);
            lcd.blink();
          }
          delay(200);
        }
        while (digitalRead(CLK) == 0) {}
        lcd.setCursor(letter_index, 0);
        lcd.noBlink();
        if (half == true) {
          choise = letter1[letter_index];
        }
        else {
          choise = letter2[letter_index];
        }
      }


      
      else if (y_g == 1) {
        lcd.setCursor(0, 2);
        lcd.blink();
        while (digitalRead(CLK) != 0) {
          if (analogRead(X) >= 786 && word_index < word_size) {
            word_index++;
            lcd.setCursor(word_index, 2);
            lcd.blink();
          }
          else if (analogRead(X) <= 256 && word_index > 0) {
            word_index--;
            lcd.setCursor(word_index, 2);
            lcd.blink();
          }
          delay(200);
        }
        while (digitalRead(CLK) == 0) {}
        lcd.setCursor(word_index, 2);
        lcd.noBlink();
        if(fake[word_index] == choise){
        without[word_index] = choise;
        lcd.setCursor(0, 2);
        lcd.print(without);
        }
        else{
          lcd.setCursor(15,0);
          lcd.print("WRONG");
          delay(1000);
          lcd.setCursor(15,0);
          lcd.print("     ");
          }
      }


      
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(definition[i]);
        while(digitalRead(CLK) != 0){}
        lcd.clear();
        }


        
      letter_index = 0;
      word_index = 0;
      y_g = 0;
    }
  }
}
