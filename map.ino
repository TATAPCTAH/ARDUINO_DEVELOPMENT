#include <TFT_ILI9341.h>
#include "cursor_up.h"
#include "cursor_down.h"
#include "cursor_left.h"
#include "cursor_right.h"
TFT_ILI9341 tft = TFT_ILI9341();
#define BUFF_SIZE 64
#define X A0
#define Y A1
//byte matrix[15][20] ={{},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
//{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
//{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
//{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
//{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
//{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
//};
int x = 0,y = 0;
void input(){
  if(analogRead(X) >= 768 && x < 288){
    tft.fillRect(x, y, 32, 32,TFT_BLACK);
    x++;
    drawIcon(cursor_right, x, y, 32, 32);
    }
  else if(analogRead(X) <= 256 && x > 0){
    tft.fillRect(x, y, 32, 32,TFT_BLACK);
    x--;
    drawIcon(cursor_left, x, y, 32, 32);
}
  if(analogRead(Y) >= 768 && y > 0){
    tft.fillRect(x, y, 32, 32,TFT_BLACK);
    y--;
    drawIcon(cursor_up, x, y, 32, 32);}
  else if(analogRead(Y) <= 256 && y < 208){
    tft.fillRect(x, y, 32, 32,TFT_BLACK);
    y++;
    drawIcon(cursor_down, x, y, 32, 32);}
  }
  bool motion(){
    if((analogRead(X) >= 768 && x < 288) || (analogRead(X) <= 256 && x > 0) || (analogRead(Y) >= 768 && y > 0) || (analogRead(Y) <= 256 && y < 208)){return true;}
    else {return false;}
  }
void drawIcon(const unsigned short* icon, int16_t x, int16_t y, int8_t width, int8_t height) {

  uint16_t  pix_buffer[BUFF_SIZE];   // Pixel buffer (16 bits per pixel)

  // Set up a window the right size to stream pixels into
  tft.setWindow(x, y, x + width - 1, y + height - 1);

  // Work out the number whole buffers to send
  uint16_t nb = ((uint16_t)height * width) / BUFF_SIZE;

  // Fill and send "nb" buffers to TFT
  for (int i = 0; i < nb; i++) {
    for (int j = 0; j < BUFF_SIZE; j++) {
      pix_buffer[j] = pgm_read_word(&icon[i * BUFF_SIZE + j]);
    }
    tft.pushColors(pix_buffer, BUFF_SIZE);
  }

  // Work out number of pixels not yet sent
  uint16_t np = ((uint16_t)height * width) % BUFF_SIZE;

  // Send any partial buffer left over
  if (np) {
    for (int i = 0; i < np; i++) pix_buffer[i] = pgm_read_word(&icon[nb * BUFF_SIZE + i]);
    tft.pushColors(pix_buffer, np);
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
tft.begin();
  tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    drawIcon(cursor_up, x, y, 32, 32);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(motion() == true){
    input();
  }
  delay(10);
}
