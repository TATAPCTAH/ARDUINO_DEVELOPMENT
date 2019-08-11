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
uint8_t empty[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
uint8_t spaceship[8] = {0x18, 0xc, 0xe, 0xf, 0xf, 0xe, 0xc, 0x18};
uint8_t gem[8] = {0x0, 0x0, 0x4, 0xe, 0xe, 0x4, 0x0, 0x0};
uint8_t meteor[8] = {0x4, 0xe, 0x1f, 0x1f, 0x1f, 0x1f, 0xe, 0x4};
uint8_t bullet[8] = {0x0, 0x0, 0x0, 0xe, 0xe, 0x0, 0x0, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0, 0x0};
uint8_t lmeteor[8] = {0x0, 0x1, 0x3, 0x3, 0x3, 0x3, 0x1, 0x0};
uint8_t rmeteor[8] = {0x0, 0x10, 0x18, 0x18, 0x18, 0x18, 0x10, 0x0};
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
  if (analogRead(X) >= 768 && x_s < 19 && matrix[y_s][x_s + 1] != 2 && matrix[y_s][x_s + 1] != 3 && matrix[y_s][x_s + 1] != 5 && matrix[y_s][x_s + 1] != 6) {
    matrix[y_s][x_s] = 0;
    x_s++;
    matrix[y_s][x_s] = 7;
    tone(3, 400, 10);
  }
  if (analogRead(Y) >= 768 && y_s > 1 && matrix[y_s - 1][x_s] != 2 && matrix[y_s - 1][x_s] != 3 && matrix[y_s - 1][x_s] != 5 && matrix[y_s - 1][x_s] != 6) {
    matrix[y_s][x_s] = 0;
    y_s--;
    matrix[y_s][x_s] = 7;
    tone(3, 400, 10);
  }
  if (analogRead(X) <= 256 && x_s > 0 && matrix[y_s][x_s - 1] != 2 && matrix[y_s][x_s - 1] != 3 && matrix[y_s][x_s - 1] != 5 && matrix[y_s][x_s - 1] != 6) {
    matrix[y_s][x_s] = 0;
    x_s--;
    matrix[y_s][x_s] = 7;
    tone(3, 400, 10);
  }
  if (analogRead(Y) <= 256 && y_s < 3 && matrix[y_s + 1][x_s] != 2 && matrix[y_s + 1][x_s] != 3 && matrix[y_s + 1][x_s] != 5 && matrix[y_s + 1][x_s] != 6) {
    matrix[y_s][x_s] = 0;
    y_s++;
    matrix[y_s][x_s] = 7;
    tone(3, 400, 10);
  }
}
void update_tact() {
  for (byte j = 0; j < 4; j++) {
    for (byte i = 0; i < 20; i++) {
      if (matrix[j][i] == 1 && i > 0) {
        if (matrix[j][i - 1] == 7) {
          matrix[j][i] = 0;
          score_s += 2;
        }
        else {
          matrix[j][i - 1] = 1;
          matrix[j][i] = 0;
        }
      }
      if (matrix[j][i] == 2 && i > 0) {
        if (matrix[j][i - 1] == 7) {
          matrix[j][i] = 0;
          matrix[0][14 + health] = 0;
          health--;
        }
        else {
          matrix[j][i - 1] = 5;
          matrix[j][i] = 6;
        }
      }
      if (matrix[j][i] == 2 && i == 0) {
        matrix[j][19] = 2;
        matrix[j][0] = 0;
      }
      if (matrix[j][i] == 1 && i == 0) {
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
  health = 5;
  lcd.init();
  lcd.backlight();
  lcd.begin(20, 4);
  lcd.createChar(0, empty);
  lcd.createChar(1, gem);
  lcd.createChar(2, meteor);
  lcd.createChar(3, bullet);
  lcd.createChar(4, heart);
  lcd.createChar(5, lmeteor);
  lcd.createChar(6, rmeteor);
  lcd.createChar(7, spaceship);
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(CLK, INPUT);
  digitalWrite(CLK, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("WELCOME TO THE GAME:");
  lcd.setCursor(3, 2);
  lcd.print("SPACE INVADERS");
  delay(2000);
  lcd.clear();
  x_s = 0;
  y_s = 1;
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
}
//const unsigned  int fps = 60;
//const  int frame_millis = 1000 / fps;
void loop() {
  // put your main code here, to run repeatedly:
  while (true) {
    input();
    update_tact();
    render();
    if (health == 0) {
      resetFunc();
    }
  }
}
