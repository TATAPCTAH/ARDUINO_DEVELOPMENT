#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif
#define X A0
#define Y A1
#define CLK 2
uint8_t r2[8] = {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3};
uint8_t r3[8] = {0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7};
uint8_t l3[8] = {0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c};
uint8_t l2[8] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
uint8_t full[8] = {0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
uint8_t empty[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
uint8_t person[8] = {0x07,0x05,0x17,0x13,0x0a,0x0e,0x0e,0x11};
int score = 0;
int x_r = 0, y_r = 3;
void(* resetFunc) (void) = 0;
byte matrix[4][20] {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {7, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5}
};
void input() {
  if (analogRead(X) >= 768 && x_r < 19 && (matrix[y_r][x_r + 1] < 1 || matrix[y_r][x_r + 1] > 5)) {
    matrix[y_r][x_r] = 0;
    x_r++;
    matrix[y_r][x_r] = 7;
  }
  if (analogRead(Y) >= 768 && y_r == 3) {
    matrix[y_r][x_r] = 0;
    y_r-=2;
    matrix[y_r][x_r] = 7;
  }
  if (analogRead(X) <= 256 && x_r > 0 && x_r < 19 && (matrix[y_r][x_r - 1] < 1 || matrix[y_r][x_r - 1] > 5)) {
    matrix[y_r][x_r] = 0;
    x_r--;
    matrix[y_r][x_r] = 7;
  }
}
void update_screen() {
for(byte j = 0;j < 4;++j){
  for(byte i = 0;i < 20;++i){
    if(matrix[j][i] == 7){
      if(j < 3){
        if(matrix[j+1][i] < 6 && matrix[j+1][i] > 0){resetFunc();}
          else{matrix[j][i] = 0;matrix[j+1][i] = 0;y_r++;}
        }
        }
    if(matrix[j][i] < 6 && matrix[j][i] > 0){
      if(i == 0 && matrix[j][i] == 5){
        if(x_r == 19 && y_r == 3){resetFunc();}
        matrix[j][0] = 1;
        matrix[j][19] = 3;
        }
      else{
      if(matrix[j][i] == 5){
        if(x_r == i-1 && y_r == 3){resetFunc();}
        matrix[j][i] = 1;
        matrix[j][i-1] = 3; 
        }
        else if(matrix[j][i] == 1 && i == 0){
          matrix[j][19] = 4;
          matrix[j][0] = 2;
          }
          else if(matrix[j][i] == 2 && i == 0){
          matrix[j][19] = 5;
          matrix[j][0] = 0;
            }
        else if(matrix[j][i] == 1){
          if(x_r == i-1 && y_r == 3){resetFunc();}
          matrix[j][i] = 2;
          matrix[j][i-1] = 4;
          }
          else if(matrix[j][i] == 2){
          matrix[j][i] = 0;
          matrix[j][i-1] = 5;
            }
      }
      }
    }
  }
}
void render() {
  for (byte j = 0; j < 4; ++j) {
    for (byte i = 0; i < 20; ++i) {
      lcd.setCursor(i, j);
      lcd.printByte(matrix[j][i]);
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.begin(20, 4);
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(CLK, INPUT);
  digitalWrite(CLK, HIGH);
  lcd.createChar(0, empty);
  lcd.createChar(1, l3);
  lcd.createChar(2, l2);
  lcd.createChar(3, r2);
  lcd.createChar(4, r3);
  lcd.createChar(5, full);
  lcd.createChar(7, person);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("WELCOME TO THE GAME:");
  lcd.setCursor(6, 2);
  lcd.print("RUN AWAY");
  delay(2000);
}
void loop() {
  // put your main code here, to run repeatedly:
  while(true){
    input();
    render();
    update_screen();
    render();
    delay(1000);
    }
}
