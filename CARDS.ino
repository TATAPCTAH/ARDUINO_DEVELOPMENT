#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define X A0
#define Y A1
#define CLK 2
char matrix[4][20];
char massiv[40];
byte x_c = 0;
byte y_c = 0;
void in(){
  while(digitalRead(CLK) != 0){
    if(analogRead(X) >= 768 && x_c < 19){
      lcd.setCursor(x_c,y_c);
        lcd.noBlink();
        x_c++;
        lcd.setCursor(x_c,y_c);
        lcd.blink();
      }
    if(analogRead(Y) >= 768 && y_c > 0){
      lcd.setCursor(x_c,y_c);
        lcd.noBlink();
        y_c--;
        lcd.setCursor(x_c,y_c);
        lcd.blink();
      }
    if(analogRead(X) <= 256 && x_c > 0){
      lcd.setCursor(x_c,y_c);
        lcd.noBlink();
        x_c--;
        lcd.setCursor(x_c,y_c);
        lcd.blink();
      }
    if(analogRead(Y) <= 256 && y_c < 3){
      lcd.setCursor(x_c,y_c);
        lcd.noBlink();
        y_c++;
        lcd.setCursor(x_c,y_c);
        lcd.blink();
      }
      delay(200);
    }
  }
void setup() {
  // put your setup code here, to run once:
   for(int i = 161;i < 201;i++){
      massiv[i-161] = char(i);
      }
      for(byte j = 0;j < 4;j++){
        for(byte i = 0;i < 20;i++){
          matrix[j][i] = 'a';
          }
        }
   lcd.init();
  lcd.backlight();
    lcd.begin(20,4);
    pinMode(X,INPUT);
  pinMode(Y,INPUT);
  pinMode(CLK,INPUT);
  digitalWrite(CLK, HIGH);
  lcd.setCursor(0,1);
  lcd.print("Welcome to the game:");
  lcd.setCursor(6,2);
  lcd.print("Cards!");
  delay(2000);
  lcd.clear();
  for(byte j = 0;j < 40;j++){
    while(true){
    byte xrandom = random(0,20);
    byte yrandom = random(0,4);
    if(matrix[yrandom][xrandom] == 'a'){
      matrix[yrandom][xrandom] = massiv[j];
      lcd.setCursor(xrandom,yrandom);
      lcd.print("0");
      break;
      }
      }
      delay(50);
    }
    for(byte j = 0;j < 40;j++){
    while(true){
    byte xrandom = random(0,20);
    byte yrandom = random(0,4);
    if(matrix[yrandom][xrandom] == 'a'){
      matrix[yrandom][xrandom] = massiv[j];
      lcd.setCursor(xrandom,yrandom);
      lcd.print("0");
      break;
      }
      }
      delay(50);
    }
    delay(1000);
    lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(true){
    in();
    byte lastx = x_c;
    byte lasty = y_c;
    while(digitalRead(CLK) == 0){}
    lcd.setCursor(lastx,lasty);
    lcd.noBlink();
    lcd.setCursor(lastx,lasty);
    lcd.print(matrix[lasty][lastx]);
    in();
    while(digitalRead(CLK) == 0){}
    if(lastx == x_c && lasty == y_c){}
    else{
      lcd.setCursor(x_c,y_c);
    lcd.print(matrix[y_c][x_c]);
    if(matrix[lasty][lastx] == matrix[y_c][x_c]){}
    else{
      delay(1000);
      lcd.setCursor(x_c,y_c);
    lcd.print(" ");
    lcd.setCursor(lastx,lasty);
    lcd.print(" ");
      }
      }
}
}
