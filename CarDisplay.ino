   //////////////////////////////////////////////
  //        2.8" CAR DISPLAY DEMO             //
 //                                          //
//           http://www.educ8s.tv           //
/////////////////////////////////////////////

#include <Adafruit_TFTLCD.h> 

#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4 

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY     0xD6BA

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

extern uint8_t car[];
extern uint8_t title[];

void setup() {
  Serial.begin(9600);
  Serial.print("Starting...");
  
  tft.reset();
  tft.begin(0x9325);
  tft.setRotation(1);
  

}

void loop() 
{  
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,319,240,WHITE); //Draw white frame

  drawBitmap(30, 10, title, 275, 31,WHITE);
  drawBitmap(65, 70, car, 195, 146,GREEN);
  delay(2000);
  drawBitmap(30, 10, title, 275, 31,BLUE);
  drawBitmap(65, 70, car, 195, 146,RED);
  delay(2000);
  drawBitmap(30, 10, title, 275, 31,RED);
  drawBitmap(65, 70, car, 195, 146,BLUE);
  delay(2000); 
  tft.fillScreen(WHITE); //Make screen white
  drawBitmap(30, 10, title, 275, 31,BLACK);
  drawBitmap(65, 70, car, 195, 146,BLACK);
  delay(2000);
}

void drawBitmap(int16_t x, int16_t y,
 const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++) {
      if(i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if(byte & 0x80) tft.drawPixel(x+i, y+j, color);
    }
  }
}

