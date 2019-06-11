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
bool game = true;
//RUN AWAY
uint8_t r1[8] = {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};
uint8_t r2[8] = {0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3};
uint8_t r3[8] = {0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7};
uint8_t r4[8] = {0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf};
uint8_t l4[8] = {0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,0x1e};
uint8_t l3[8] = {0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c};
uint8_t l2[8] = {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18};
uint8_t l1[8] = {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10};
//SPACE INVADERS
uint8_t empty[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
uint8_t spaceship[8] = {0x18, 0xc, 0xe, 0xf, 0xf, 0xe, 0xc, 0x18};
uint8_t gem[8] = {0x0, 0x0, 0x4, 0xe, 0xe, 0x4, 0x0, 0x0};
uint8_t meteor[8] = {0x4, 0xe, 0x1f, 0x1f, 0x1f, 0x1f, 0xe, 0x4};
uint8_t bullet[8] = {0x0, 0x0, 0x0, 0xe, 0xe, 0x0, 0x0, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0, 0x0};
uint8_t lmeteor[8] = {0x0, 0x1, 0x3, 0x3, 0x3, 0x3, 0x1, 0x0};
uint8_t rmeteor[8] = {0x0, 0x10, 0x18, 0x18, 0x18, 0x18, 0x10, 0x0};
//RUN AWAY
int score = 0;
int con = 1;
int x_r = 0,y_r= 3;
char p = char(251);
//SPACE INVADERS
byte score_s = 0;
byte x_s = 0;
byte y_s = 1;
byte health = 5;
byte matrix[4][20] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4},
                      {7, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2, 0, 1, 0, 2, 0, 1, 0, 0, 2},
                      {0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0},
                      {2, 0, 1, 0, 0, 0, 0, 2, 0, 2, 0, 1, 0, 2, 0, 0, 0, 2, 0, 0}
};
byte matrix_real[4][20] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4},
                      {7, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2, 0, 1, 0, 2, 0, 1, 0, 0, 2},
                      {0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0},
                      {2, 0, 1, 0, 0, 0, 0, 2, 0, 2, 0, 1, 0, 2, 0, 0, 0, 2, 0, 0}
};
void(* resetFunc) (void) = 0;
void input() {
  if (analogRead(X) >= 768 && x_s < 19 && matrix[y_s][x_s+1] != 2 && matrix[y_s][x_s+1] != 3 && matrix[y_s][x_s+1] != 5 && matrix[y_s][x_s+1] != 6) {
    matrix[y_s][x_s] = 0;
    x_s++;
    matrix[y_s][x_s] = 7;
    tone(3,400, 10);
  }
  if (analogRead(Y) >= 768 && y_s > 1 && matrix[y_s-1][x_s] != 2 && matrix[y_s-1][x_s] != 3 && matrix[y_s-1][x_s] != 5 && matrix[y_s-1][x_s] != 6) {
    matrix[y_s][x_s] = 0;
    y_s--;
    matrix[y_s][x_s] = 7;
    tone(3,400, 10);
  }
  if (analogRead(X) <= 256 && x_s > 0 && matrix[y_s][x_s-1] != 2 && matrix[y_s][x_s-1] != 3 && matrix[y_s][x_s-1] != 5 && matrix[y_s][x_s-1] != 6) {
    matrix[y_s][x_s] = 0;
    x_s--;
    matrix[y_s][x_s] = 7;
    tone(3,400, 10);
  }
  if (analogRead(Y) <= 256 && y_s < 3 && matrix[y_s+1][x_s] != 2 && matrix[y_s+1][x_s] != 3 && matrix[y_s+1][x_s] != 5 && matrix[y_s+1][x_s] != 6) {
    matrix[y_s][x_s] = 0;
    y_s++;
    matrix[y_s][x_s] = 7;
    tone(3,400, 10);
  }
}
void update_tact() {
  for (byte j = 0; j < 4; j++) {
    for (byte i = 0; i < 20; i++) {
      if(matrix[j][i] == 1 && i > 0){
        if (matrix[j][i - 1] == 7) {
          matrix[j][i] = 0;
          score_s+=2;
        }
        else{
        matrix[j][i - 1] = 1;
        matrix[j][i] = 0;
        }
        }
      if (matrix[j][i] == 2 && i > 0) {
        if (matrix[j][i - 1] == 7) {
          matrix[j][i] = 0;
          matrix[0][14+health] = 0;
          health--;
        }
        else{
        matrix[j][i - 1] = 5;
        matrix[j][i] = 6;
        }
      }
      if (matrix[j][i] == 2 && i == 0) {
        matrix[j][19] = 2;
        matrix[j][0] = 0;
      }
      if(matrix[j][i] == 1 && i == 0){
        matrix[j][19] = 1;
        matrix[j][0] = 0;
        }
      if (matrix[j][i] == 5) {
        matrix[j][i] = 2;
        matrix[j][i + 1] = 0;
      }
    }
  }
  score_s++;
}
void render() {
  for (byte j = 0; j < 4; j++) {
    for (byte i = 0; i < 20; i++) {
      lcd.setCursor(i, j);
      lcd.printByte(matrix[j][i]);
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
    lcd.begin(20,4);
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
  pinMode(CLK,INPUT);
  digitalWrite(CLK, HIGH);
lcd.setCursor(6,1);
lcd.print("RUN AWAY");
lcd.setCursor(3,2);
lcd.print("SPACE INVADERS");
lcd.setCursor(0,1);
    lcd.print(char(126));
    lcd.setCursor(19,1);
    lcd.print(char(127));
while(digitalRead(CLK) != 0){
  if(analogRead(Y) >= 768){
    tone(3,400,100);
    lcd.setCursor(0,1);
    lcd.print(char(126));
    lcd.setCursor(19,1);
    lcd.print(char(127));
    game = true;
    lcd.setCursor(0,2);
    lcd.print(" ");
    lcd.setCursor(19,2);
    lcd.print(" ");
    }
  else if(analogRead(Y) <= 256){
    tone(3,400,100);
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.setCursor(19,1);
    lcd.print(" ");
    game = false;
    lcd.setCursor(0,2);
    lcd.print(char(126));
    lcd.setCursor(19,2);
    lcd.print(char(127));
    }
  }
  lcd.clear();
lcd.setCursor(0,1);
  lcd.print("WELCOME TO THE GAME:");
  if(game == true){//RUN AWAY
   lcd.setCursor(6,2);
  lcd.print("RUN AWAY");
  lcd.createChar(0, l4);
lcd.createChar(1, r1);
lcd.createChar(2, l3);
lcd.createChar(3, r2);
lcd.createChar(4, l2);
lcd.createChar(5, r3);
lcd.createChar(6, l1);
lcd.createChar(7, r4);
 delay(2000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(char(126));
  lcd.setCursor(2,1);
  lcd.print("CHOOSE CHARACTER");
  lcd.setCursor(19,1);
  lcd.print(char(127));
  lcd.setCursor(6,2);
  lcd.print("CONTINUE");
  while(digitalRead(CLK) != 0){
    if(analogRead(Y) >= 768 && con != 1){
      con = 1;
      lcd.setCursor(0,2);
  lcd.print(" ");
  lcd.setCursor(19,2);
  lcd.print(" ");
      lcd.setCursor(0,1);
  lcd.print(char(126));
  lcd.setCursor(19,1);
  lcd.print(char(127));
    }
    if(analogRead(Y) <= 256 && con != 2){
      con = 2;
      lcd.setCursor(0,1);
  lcd.print(" ");
  lcd.setCursor(19,1);
  lcd.print(" ");
      lcd.setCursor(0,2);
  lcd.print(char(126));
  lcd.setCursor(19,2);
  lcd.print(char(127));
      }
      }
      delay(1000);
    if(con == 1){
      lcd.clear();
      lcd.setCursor(0,0);
    for(int i = 161;i < 181;i++){
      lcd.print(char(i));
      }
      lcd.setCursor(0,1);
    for(int i = 181;i < 201;i++){
      lcd.print(char(i));
      }
      lcd.setCursor(0,2);
    for(int i = 201;i < 221;i++){
      lcd.print(char(i));
      }
      lcd.setCursor(0,3);
    for(int i = 221;i < 241;i++){
      lcd.print(char(i));
      }
      while(digitalRead(CLK) != 0){
        if(analogRead(X) >= 768 && x_r < 19){lcd.setCursor(x_r,y_r);lcd.print(char(161 + x_r + y_r*20));x_r++;lcd.setCursor(x_r,y_r);lcd.print(char(0xFF));tone(3,400, 50);}
        if(analogRead(Y) >= 768 && y_r > 0){lcd.setCursor(x_r,y_r);lcd.print(char(161 + x_r + y_r*20));y_r--;lcd.setCursor(x_r,y_r);lcd.print(char(0xFF));tone(3,400, 50);}
        if(analogRead(X) <= 256 && x_r > 0){lcd.setCursor(x_r,y_r);lcd.print(char(161 + x_r + y_r*20));x_r--;lcd.setCursor(x_r,y_r);lcd.print(char(0xFF));tone(3,400, 50);}
        if(analogRead(Y) <= 256 && y_r < 3){lcd.setCursor(x_r,y_r);lcd.print(char(161 + x_r + y_r*20));x_r++;lcd.setCursor(x_r,y_r);lcd.print(char(0xFF));tone(3,400, 50);}
        delay(200);
        }
        p = char(161 + x_r + y_r*20);
      }
x_r = 0;
y_r = 3;
  }
  else{
    lcd.setCursor(3, 2);
  lcd.print("SPACE INVADERS");
  delay(2000);
  lcd.clear();
  lcd.createChar(0, empty);
  lcd.createChar(1, gem);
  lcd.createChar(2, meteor);
  lcd.createChar(3, bullet);
  lcd.createChar(4, heart);
  lcd.createChar(5, lmeteor);
  lcd.createChar(6, rmeteor);
  lcd.createChar(7, spaceship);
    } 
}
int down = 0;
int chet = 0;
int index1 = 3;
int index2 = 7;
int index3 = 11;
int index4 = 15;
int index5 = 19;
void loop() {
  // put your main code here, to run repeatedly:
  if(game == true){
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print(char(35));
    lcd.print(char(35));
    lcd.print(char(35));
    lcd.print(char(35));
    lcd.print(char(35));
  lcd.setCursor(x_r,y_r);
    lcd.print(p);
  lcd.setCursor(3,3);
  lcd.print(char(0xFF));
  lcd.setCursor(7,3);
  lcd.print(char(0xFF));
  lcd.setCursor(11,3);
  lcd.print(char(0xFF));
  lcd.setCursor(15,3);
  lcd.print(char(0xFF));
  lcd.setCursor(19,3);
  lcd.print(char(0xFF));
  delay(3000);
  while(true){
  while(index1 > 0){
    lcd.setCursor(0,0);
    lcd.print("               ");
    lcd.setCursor(0,0);
    lcd.print("SCORE: ");
    lcd.print(score);
    while(chet < 7){
      if(y_r < 3){down++;}
      lcd.setCursor(x_r,y_r);
    lcd.print(p);
if(analogRead(X) >= 768 && x_r < 19){
        lcd.setCursor(x_r,y_r);
    lcd.print(" ");
    x_r++;
    lcd.setCursor(x_r,y_r);
    lcd.print(p);
    tone(3,200, 50);
        }
    if(analogRead(Y) >= 768 && y_r == 3){
      lcd.setCursor(x_r,y_r);
    lcd.print(" ");
    y_r-=2;
    lcd.setCursor(x_r,y_r);
    lcd.print(p);
    tone(3,400, 50);
      }
    if(analogRead(X) <= 256 && x_r > 0){
      lcd.setCursor(x_r,y_r);
    lcd.print(" ");
    x_r--;
    lcd.setCursor(x_r,y_r);
    lcd.print(p);
    tone(3,200, 50);
      }
    if(down == 5 && y_r < 3){
      lcd.setCursor(x_r,y_r);
    lcd.print(" ");
    y_r++;
    lcd.setCursor(x_r,y_r);
    lcd.print(p);
    down = 0;
    tone(3,100, 50);
      }
    lcd.setCursor(index5,3);
    lcd.printByte(chet);
    lcd.setCursor(index5-1,3);
    lcd.printByte(chet+1);
    
    lcd.setCursor(index4,3);
    lcd.printByte(chet);
    lcd.setCursor(index4-1,3);
    lcd.printByte(chet+1);

    lcd.setCursor(index3,3);
    lcd.printByte(chet);
    lcd.setCursor(index3-1,3);
    lcd.printByte(chet+1);

    lcd.setCursor(index2,3);
    lcd.printByte(chet);
    lcd.setCursor(index2-1,3);
    lcd.printByte(chet+1);

    lcd.setCursor(index1,3);
    lcd.printByte(chet);
    lcd.setCursor(index1-1,3);
    lcd.printByte(chet+1);
    
    delay(200);
    chet+=2;
    if(y_r == 3 && (x_r == index5 || x_r == index4 || x_r == index3 || x_r == index2 || x_r == index1)){lcd.setCursor(14+health,0);lcd.print(" ");health--;}
  }
  lcd.setCursor(index1,3);
  lcd.print(" ");
  lcd.setCursor(index1-1,3);
  lcd.print(char(0xFF));
  lcd.setCursor(index2,3);
  lcd.print(" ");
  lcd.setCursor(index2-1,3);
  lcd.print(char(0xFF));
  lcd.setCursor(index3,3);
  lcd.print(" ");
  lcd.setCursor(index3-1,3);
  lcd.print(char(0xFF));
  lcd.setCursor(index4,3);
  lcd.print(" ");
  lcd.setCursor(index4-1,3);
  lcd.print(char(0xFF));
  lcd.setCursor(index5,3);
  lcd.print(" ");
  lcd.setCursor(index5-1,3);
  lcd.print(char(0xFF));
  delay(250);
  chet = 0;
  index1--;
  index2--;
  index3--;
  index4--;
  index5--;
  if(y_r == 3 && (x_r == index5 || x_r == index4 || x_r == index3 || x_r == index2 || x_r == index1)){lcd.setCursor(14+health,0);lcd.print(" ");health--;}
  score++;
    }
    lcd.setCursor(0,3);
  lcd.print(" ");
    index1 = index2;
    index2 = index3;
    index3 = index4;
    index4 = index5;
    index5 = 19;
    if(health <= 0){break;}
}
}
else{
  for (byte j = 1; j < 4; j++) {
    for (byte i = 0; i < 20; i++) {
      lcd.setCursor(i, j);
      lcd.printByte(matrix_real[j][i]);
    }
  }
  for (byte j = 1; j < 4; j++) {
    for (byte i = 0; i < 20; i++) {
      matrix[j][i] = matrix_real[j][i];
    }
  }
  delay(1000);
  while (true) {
    input();
    update_tact();
    render();
    if(health == 0){break;}
  }
  }
  lcd.clear();
  if(game == true){
    lcd.setCursor(0,0);
  lcd.print("YOUR SCORE: ");
  lcd.print(score);
  }
  else{
     lcd.setCursor(0,0);
  lcd.print("YOUR SCORE: ");
  lcd.print(score_s);
    }
  lcd.setCursor(1,1);
  lcd.print("DO YOU REALLY WANT");
  lcd.setCursor(5,2);
  lcd.print("TO CONTINUE?");
  delay(3000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("IF YOU WNAT");
  lcd.setCursor(2,1);
  lcd.print("SWITCH JOYSTICK");
  lcd.setCursor(0,2);
  lcd.print("FORWARD OR BACK");
  while(true){
    if(analogRead(Y) >= 768){score = 0;score_s = 0;health = 5;x_s = 0;y_s = 1;x_r = 0;y_r = 3;break;}
    else if(analogRead(Y) <= 256){score = 0;score_s = 0;health = 5;x_s = 0;y_s = 1;x_r = 0;y_r = 3;resetFunc();}
    }
}
