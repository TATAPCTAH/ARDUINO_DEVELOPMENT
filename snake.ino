#include <LiquidCrystal.h>

#define       JOYSTICK_X_PIN                 A0
#define       JOYSTICK_Y_PIN                 A1
#define       JOYSTICK_Z_PIN                 6


#define       NUM_KEYS                       5

#define       JOYSTICK_RELEASED              0
#define       JOYSTICK_UP_                   1
#define       JOYSTICK_DOWN_                 2
#define       JOYSTICK_LEFT_                 3
#define       JOYSTICK_RIGHT_                4

#define       ROWS                           4 //количество рядов индикатора

#define       levels                         4 //уровни сложности

#define       MAX_SNAKE_LENGTH               25 //максимальная длина змейки



LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
unsigned long time, timeNow; 
int gameSpeed;
boolean skip, gameOver, gameStarted;
int olddir;
int selectedLevel;
byte key=0;
byte oldkey=0;

byte Field[8*ROWS*16];


struct partdef
{
  int row,column,dir; 
  struct partdef *next;
}; 
typedef partdef part;

part *head, *tail;
int collected;
unsigned int pc,pr;

//----------------------------------------------
//отображение на экране
void drawMatrix()
{
  boolean levelz[levels][4][16] = {
{{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}},

{{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true}},

{{true,false,false,false,true,false,false,false,false,false,false,true,false,false,false,true},
{true,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true},
{true,false,false,false,true,false,false,false,false,false,false,true,false,false,false,true},
{true,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true}},

{{true,false,true,false,false,false,false,false,false,true,false,false,false,true,false,false},
{false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true},
{true,false,true,false,false,false,false,false,false,true,false,false,false,true,false,false},
{false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true}}
};



  byte myChar[8];
  boolean special;
  int cc=0;
  
  if (!gameOver)
  {
  ChangeDot(pr, pc, true);
  
  for(int r=0;r<ROWS;r++)
  {    
    for(int c=0;c<16;c++)
    {
      special = false;
      for(int i=0;i<8;i++)
      {
        byte b=B00000;

        if ((Field[16 * (r*8+i) + (c*5+0)/5] & (1 << ((c*5+0) % 5))) >> ((c*5+0) % 5)) {b+=B10000; special = true;}
        if ((Field[16 * (r*8+i) + (c*5+1)/5] & (1 << ((c*5+1) % 5))) >> ((c*5+1) % 5)) {b+=B01000; special = true;}
        if ((Field[16 * (r*8+i) + (c*5+2)/5] & (1 << ((c*5+2) % 5))) >> ((c*5+2) % 5)) {b+=B00100; special = true;}
        if ((Field[16 * (r*8+i) + (c*5+3)/5] & (1 << ((c*5+3) % 5))) >> ((c*5+3) % 5)) {b+=B00010; special = true;}
        if ((Field[16 * (r*8+i) + (c*5+4)/5] & (1 << ((c*5+4) % 5))) >> ((c*5+4) % 5)) {b+=B00001; special = true;}        
 
        myChar[i] = b;

      }
      if (special) 
      {
        lcd.createChar(cc, myChar);
        lcd.setCursor(c,r);
        lcd.write(byte(cc));
  cc++;
      }
      else 
      {
        lcd.setCursor(c,r);
        if (levelz[selectedLevel][r][c]) lcd.write(255);
        else lcd.write(128);
      }
    }
  } 
  }
}
//----------------------------------
void freeList()
{
  part *p,*q;
  p = tail;
  while (p!=NULL)
  {
    q = p;
    p = p->next;
    free(q);
  }
  head = tail = NULL;
}
//----------------------------------
void gameOverFunction()
{
  delay(1000);
  lcd.clear();
  freeList();
  lcd.setCursor(3,0);
  lcd.print("Game Over!");
  lcd.setCursor(4,1);
  lcd.print("Score: ");
  lcd.print(collected);
  delay(1000);
}
//----------------------------------
void growSnake()
{
  part *p;
  p = (part*)malloc(sizeof(part));
  p->row = tail->row;
  p->column = tail->column;
  p->dir = tail->dir;
  p->next = tail;
  tail = p;
}
//----------------------------------
//новая точка на экране
void newPoint()
{
  boolean levelz[levels][4][16] = {
{{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}},

{{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true}},

{{true,false,false,false,true,false,false,false,false,false,false,true,false,false,false,true},
{true,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true},
{true,false,false,false,true,false,false,false,false,false,false,true,false,false,false,true},
{true,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true}},

{{true,false,true,false,false,false,false,false,false,true,false,false,false,true,false,false},
{false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true},
{true,false,true,false,false,false,false,false,false,true,false,false,false,true,false,false},
{false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true}}
};

  
  part *p;
  p = tail;
  boolean newp = true;
  while (newp)
  {
    pr = random(8*ROWS);
    pc = random(80);
    newp = false;
    if (levelz[selectedLevel][pr / 8][pc / 5]) newp=true;
    while (p->next != NULL && !newp) 
    {
      if (p->row == pr && p->column == pc) newp = true;
      p = p->next;
    }
  }
  
  if (collected < MAX_SNAKE_LENGTH && gameStarted) growSnake();
}
//----------------------------------
//движение головы
void moveHead()
{
  boolean levelz[levels][4][16] = {
{{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}},

{{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true}},

{{true,false,false,false,true,false,false,false,false,false,false,true,false,false,false,true},
{true,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true},
{true,false,false,false,true,false,false,false,false,false,false,true,false,false,false,true},
{true,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true}},

{{true,false,true,false,false,false,false,false,false,true,false,false,false,true,false,false},
{false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true},
{true,false,true,false,false,false,false,false,false,true,false,false,false,true,false,false},
{false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true}}
};
  
  
  switch(head->dir) // 1 step in direction
  {
    case 0: head->row--; break;
    case 1: head->row++; break;
    case 2: head->column++; break;
    case 3: head->column--; break;
    default : break;
  }
  if (head->column >= 80) head->column = 0;
  if (head->column < 0) head->column = 79;
  if (head->row >= (8*ROWS)) head->row = 0;
  if (head->row < 0) head->row = (8*ROWS - 1);
  
  if (levelz[selectedLevel][head->row / 8][head->column / 5]) gameOver = true; // wall collision check
  
  part *p;
  p = tail;
  while (p != head && !gameOver) // self collision 
  {
    if (p->row == head->row && p->column == head->column) gameOver = true;
    p = p->next;
  }
  if (gameOver)
    gameOverFunction();
  else
  {
  ChangeDot(head->row, head->column, true);
  
  if (head->row == pr && head->column == pc) // point pickup check
  {
    collected++;
    if (gameSpeed < 25) gameSpeed+=3;
    newPoint();
  }
  }
}
//----------------------------------
//движение змейки
void moveAll()
{
  part *p;
  p = tail;

  ChangeDot(p->row, p->column, false);
  
  while (p->next != NULL) 
  {
    p->row = p->next->row;
    p->column = p->next->column;
    p->dir = p->next->dir;
    p = p->next;
  }
  moveHead();
}
//----------------------------------
//создание змейки
void createSnake(int n) // n = size of snake
{
  for (unsigned int i=0;i<(8*ROWS*16);i++)
    Field[i] = 0;
    
  part *p, *q;
  tail = (part*)malloc(sizeof(part));
  tail->row = 7;
  tail->column = 39 + n/2;
  tail->dir = 3;
  q = tail;
  
  ChangeDot(tail->row, tail->column, true);
  
  for (int i = 0; i < n-1; i++) // build snake from tail to head
  {
    p = (part*)malloc(sizeof(part));
    p->row = q->row;
    p->column = q->column - 1; //initial snake id placed horizoltally
    
    ChangeDot(p->row, p->column, true);
    
    p->dir = q->dir;
    q->next = p;
    q = p;
  }
  if (n>1)
  {
    p->next = NULL;
    head  = p;
  }
  else 
  {
    tail->next = NULL;
    head = tail;
  }
}

void startF()
{
  byte mySnake[8][8] = 
{
{ B00000,
  B00000,
  B00011,
  B00110,
  B01100,
  B11000,
  B00000,
},
{ B00000,
  B11000,
  B11110,
  B00011,
  B00001,
  B00000,
  B00000,
},
{ B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B01110,
},
{ B00000,
  B00000,
  B00011,
  B01111,
  B11000,
  B00000,
  B00000,
},
{ B00000,
  B11100,
  B11111,
  B00001,
  B00000,
  B00000,
  B00000,
},
{ B00000,
  B00000,
  B00000,
  B11000,
  B01101,
  B00111,
  B00000,
},
{ B00000,
  B00000,
  B01110,
  B11011,
  B11111,
  B01110,
  B00000,
},
{ B00000,
  B00000,
  B00000,
  B01000,
  B10000,
  B01000,
  B00000,
}
};
  
  gameOver = false;
  gameStarted = false;
  selectedLevel = 1;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select level: 1");
  for(int i=0;i<8;i++)
  {
    lcd.createChar(i,mySnake[i]);
    lcd.setCursor(i+4,1);
    lcd.write(byte(i));
  }

  lcd.setCursor(5,2);
  lcd.print("PYTHON");
  
  collected = 0;
  gameSpeed = 8;
  createSnake(3);
  time = 0;
}
//----------------------------------
void setup()
{
  digitalWrite(JOYSTICK_Z_PIN, HIGH);
    
  lcd.begin(16, ROWS);
  startF();
}
//----------------------------------
void loop()
{
  if (!gameOver && !gameStarted) //если игра не началась
  {
   key = ScanJoyStick(); //проверка джойстика
   if (key != oldkey)    
   {
     delay(50);  
     key = ScanJoyStick();
     if (key != oldkey)    
     {   
       oldkey = key;
       if (key > 0)
       {
         olddir = head->dir;
         if (key==JOYSTICK_UP_ && selectedLevel<levels) selectedLevel++; //увеличение выбираемого уровня
         else if (key==JOYSTICK_DOWN_ && selectedLevel>1) selectedLevel--; //уменьшение выбираемого уровня
       }
     }
   }

   else if (digitalRead(JOYSTICK_Z_PIN)) //если нажата кнопка джойстика, начало игры
   {
     lcd.clear();
     selectedLevel--;
     newPoint();
     gameStarted = true;
    }
   else //иначе продолжение отображения уровня игры
    {
      lcd.setCursor(14,0);
      lcd.print(selectedLevel);
    }
  }
  
  else if (!gameOver && gameStarted) //если идет игра
  {
   skip = false;
   
   key = ScanJoyStick(); //проверка джойстика
   if (key != oldkey)   
   {
     delay(50);  
     key = ScanJoyStick();
     if (key != oldkey)    
     {   
       oldkey = key;
       if (key > 0)
       {
         //выбор направления движения змейки в зависимости от положения джойстика
         olddir = head->dir;
         if (key==JOYSTICK_RIGHT_ && head->dir!=3) head->dir = 2;
         else if (key==JOYSTICK_UP_    && head->dir!=1) head->dir = 0;
         else if (key==JOYSTICK_DOWN_  && head->dir!=0) head->dir = 1;
         else if (key==JOYSTICK_LEFT_  && head->dir!=2) head->dir = 3;
         
         if (olddir != head->dir)
         {
           skip = true;
           delay(1000/gameSpeed);
           moveAll();
           drawMatrix();
         }
       }
     }
   }
   if (!skip)
   {
     timeNow = millis();
     if (timeNow - time > 1000 / gameSpeed)
     {
       moveAll();
       drawMatrix();
       time = millis();
     }
   }
  }
  
  if(gameOver) //если игра окончена
  {
   key = ScanJoyStick();//проверка джойстика
   if (key != oldkey)   
   {
     delay(50);  
     key = ScanJoyStick();
     if (key != oldkey)    
     {   
       oldkey = key;
       if (key > 0) //начало игры при изменении положения джойстика в любом направлении
       {
          startF();
       }
     }
   }
   
  }
}
//-----------------------------------
//проверка джойстика
byte ScanJoyStick()
{
  byte Direction = JOYSTICK_RELEASED;
  unsigned int X_Val = analogRead(JOYSTICK_X_PIN);
  unsigned int Y_Val = analogRead(JOYSTICK_Y_PIN);
  
  if ((Y_Val >= 900) && (X_Val >= 400))
  {
    Direction = JOYSTICK_UP_;
  }
  else if ((Y_Val <= 400) && (X_Val >= 400))
  {
    Direction = JOYSTICK_DOWN_;
  }
  else if ((Y_Val >= 400) && (X_Val >= 900))
   {
    Direction = JOYSTICK_RIGHT_;
   }
  else if ((Y_Val >= 400) && (X_Val <= 400))
  {
    Direction = JOYSTICK_LEFT_;
  }
  
  return Direction;
}
//-----------------------------------------------------
//внесение изменений в матрицу точек на эране
void ChangeDot(unsigned int RowVal, unsigned int ColVal, boolean NewVal)
{
  Field[16 * RowVal + ColVal/5] &= ~(1 << (ColVal % 5));

  if (NewVal)
    Field[16 * RowVal + ColVal/5] |= 1 << (ColVal % 5);
}
