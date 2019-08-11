#include <TFT_ILI9341.h>
TFT_ILI9341 tft = TFT_ILI9341();
#include "paq_orig.h"
#include "gruss_orig.h"
#include "weed_orig.h"
#include "erth_orig.h"
#include "ground_orig.h"
byte matrix[15][20] ={{},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
};
void setup() {
  // put your setup code here, to run once:
  // инициализируем дисплей
 tft.begin();
  tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    for(int i = 1; i < 30;i++){
    for(int j = 1;j < 40;j++){
  drawIcon(ground_orig, (j-1)*8 + 1, (i-1)*8 + 1, 8, 8);
    }
//  for(int i = 1; i < 16;i++){
//    for(int j = 1;j < 21;j++){
//      if(matrix[i-1][j-1] == 0){
//  drawIcon(weed_orig, (j-1)*16 + 1, (i-1)*16 + 1, 16, 16);
//      }
//      else if(matrix[i-1][j-1] == 1){
//  drawIcon(gruss_orig, (j-1)*16 + 1, (i-1)*16 + 1, 16, 16);
//      }
//      else{
//  drawIcon(erth_orig, (j-1)*16 + 1, (i-1)*16 + 1, 16, 16);
//      }
//    }
}
drawIcon(paq_orig, 160, 64, 64, 64);
}

void loop() {
  // put your main code here, to run repeatedly:
}
#define BUFF_SIZE 64
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
