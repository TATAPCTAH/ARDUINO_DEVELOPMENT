#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define X A0
#define Y A1
#define CLK 2
char matrix[4][20];
char massiv[40];
byte x_c = 0;
byte y_c = 0;
byte chet = 0;
void(* resetFunc) (void) = 0;
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
    while(digitalRead(CLK) == 0){}
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
    in();//FIRST
    byte firstx = x_c;
    byte firsty = y_c;
    while(digitalRead(CLK) == 0){}
    lcd.setCursor(firstx,firsty);
    lcd.noBlink();
    lcd.setCursor(firstx,firsty);
    lcd.print(matrix[firsty][firstx]);//END FIRST
    
    in();//SECOND
    byte secondx = x_c;
    byte secondy = y_c;
    while(digitalRead(CLK) == 0){}
    lcd.setCursor(secondx,secondy);
    lcd.noBlink();
    lcd.setCursor(secondx,secondy);
    lcd.print(matrix[secondy][secondx]);//END SECOND
    
    if(firstx == secondx && firsty == secondy){}
    else{
    if(matrix[firsty][firstx] == matrix[secondy][secondx]){chet++;}
    else{
      delay(1000);
      lcd.setCursor(firstx,firsty);
    lcd.print(" ");
    lcd.setCursor(secondx,secondy);
    lcd.print(" ");
      }
      if(chet == 20){
        lcd.clear();
        lcd.setCursor(1,1);
        lcd.print("You open all cards");
        lcd.setCursor(0,2);
        lcd.print("To see the cards");
        lcd.setCursor(0,3);
        lcd.print("Push joystick AHEAD");
        lcd.setCursor(0,1);
        lcd.print("else BACK");
        while(true){
          if(analogRead(Y) >= 768){
            for(byte j = 0;j < 4;j++){
              for(byte i = 0;i < 20;i++){
                lcd.setCursor(i,j);
                lcd.print(matrix[j][i]);
                }
              }
            }
          if(analogRead(Y) <= 256){resetFunc();}
          }
        }
      }
      lcd.setCursor(x_c,y_c);
      lcd.blink();
}
}
