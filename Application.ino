#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMB_PIXELS 16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMB_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delay_value = 50;
int s1[7]{7,6,5,4,3,2,1};
int s2[7]{9,10,11,12,13,14,15};
int s3[7]{1,2,3,4,5,6,7};
int s4[7]{15,14,13,12,11,10,9};
int m[23]{0,0,0,0,0,0,0,255,255/2,255/4,255/8,255/16,255/32,255/64,255/128,0,0,0,0,0,0,0,0};
void smooth_green() {
  delay(500);
  for (int l = 0; l < 255; l += 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, l, 0));
    }
    pixels.show();
    delay(25);
  }
  delay(100);
  for (int l = 255; l >= 0; l -= 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, l, 0));
    }
    pixels.show();
    delay(25);
  }
}
void smooth_blue() {
  delay(500);
  for (int l = 0; l < 255; l += 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, l));
    }
    pixels.show();
    delay(25);
  }
  delay(100);
  for (int l = 255; l >= 0; l -= 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, l));
    }
    pixels.show();
    delay(25);
  }
}
void cheres(){
  for(int i = 0;i < 16;i++){
    if(i%2 == 0){}
    else{
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
      pixels.show();
      delay(20);
    }
    for(int i = 0;i < 16;i++){
    if(i%2 == 0){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
    else{
      }
      pixels.show();
      delay(20);
    }
    for(int i = 0;i < 16;i++){
    if(i%2 == 0){}
    else{
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      }
      pixels.show();
      delay(20);
    }
    for(int i = 0;i < 16;i++){
    if(i%2 == 0){}
    else{
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
      pixels.show();
      delay(20);
    }
    for(int i = 0;i < 16;i++){
    if(i%2 == 0){
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      }
    else{
      }
      pixels.show();
      delay(20);
    }
    for(int i = 0;i < 16;i++){
    if(i%2 == 0){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
    else{
      }
      pixels.show();
      delay(20);
    }
  }
void ring() {
    for (int i = 0; i < 16; ++i)
    {
      pixels.setPixelColor(i % 16, pixels.Color(31, 236, 240));
      pixels.setPixelColor((i + 1) % 16, pixels.Color(255/3, 0, 0));
      pixels.setPixelColor((i + 2) % 16, pixels.Color(255/2, 0, 0));
      pixels.setPixelColor((i + 3) % 16, pixels.Color(255, 0, 0));
      pixels.show();
      delay(delay_value);
    }
}
void blinking() {
  delay(500);
  for (int i = 0; i < 16; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
  }
  pixels.show();
  delay(500);
  for (int i = 0; i < 16; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
  delay(500);
  for (int i = 0; i < 16; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
  }
  pixels.show();
  delay(500);
  for (int i = 0; i < 16; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}
void smooth_red() {
  delay(500);
  for (int l = 0; l < 255; l += 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(l, 0, 0));
    }
    pixels.show();
    delay(25);
  }
  delay(100);
  for (int l = 255; l >= 0; l -= 5) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(l, 0, 0));
    }
    pixels.show();
    delay(25);
  }
}
void sending() {
  pixels.show();
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.setPixelColor(8, pixels.Color(0, 0, 255));
  for (int i = 0; i < 16; i++) {
    for(int j = 0;j < 7;j++){
    pixels.setPixelColor(s1[j], pixels.Color(m[i+j], 0, 0));
    pixels.setPixelColor(s2[j], pixels.Color(m[i+j], 0, 0));
    delay(5);
    pixels.show();
    }
  }
  for (int i = 0; i < 16; i++) {
    for(int j = 0;j < 7;j++){
    pixels.setPixelColor(s3[j], pixels.Color(m[i+j], 0, 0));
    pixels.setPixelColor(s4[j], pixels.Color(m[i+j], 0, 0));
    delay(5);
    pixels.show();
    }
  }
}
void searching_from_cd() {
  pixels.show();
  for (int i = 0; i < 4; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.setPixelColor(i + 4, pixels.Color(0, 255, 0));
    pixels.setPixelColor(i + 8, pixels.Color(0, 255, 0));
    pixels.setPixelColor(i + 12, pixels.Color(0, 255, 0));
    pixels.show();
    delay(50);
  }
  delay(200);
  for (int i = 0; i < 4; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.setPixelColor(i + 4, pixels.Color(0, 0, 0));
    pixels.setPixelColor(i + 8, pixels.Color(0, 0, 0));
    pixels.setPixelColor(i + 12, pixels.Color(0, 0, 0));
    pixels.show();
    delay(50);
  }
}
void full_ring() {
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 16; ++i)
    {
      pixels.setPixelColor(i % 16, pixels.Color(255 / 16, 0, 0));
      pixels.setPixelColor((i + 1) % 16, pixels.Color(255 / 15, 0, 0));
      pixels.setPixelColor((i + 2) % 16, pixels.Color(255 / 14, 0, 0));
      pixels.setPixelColor((i + 3) % 16, pixels.Color(255 / 13, 0, 0));
      pixels.setPixelColor((i + 4) % 16, pixels.Color(255 / 12, 0, 0));
      pixels.setPixelColor((i + 5) % 16, pixels.Color(255 / 11, 0, 0));
      pixels.setPixelColor((i + 6) % 16, pixels.Color(255 / 10, 0, 0));
      pixels.setPixelColor((i + 7) % 16, pixels.Color(255 / 9, 0, 0));
      pixels.setPixelColor((i + 8) % 16, pixels.Color(255 / 8, 0, 0));
      pixels.setPixelColor((i + 9) % 16, pixels.Color(255 / 7, 0, 0));
      pixels.setPixelColor((i + 10) % 16, pixels.Color(255 / 6, 0, 0));
      pixels.setPixelColor((i + 11) % 16, pixels.Color(255 / 5, 0, 0));
      pixels.setPixelColor((i + 12) % 16, pixels.Color(255 / 4, 0, 0));
      pixels.setPixelColor((i + 13) % 16, pixels.Color(255 / 3, 0, 0));
      pixels.setPixelColor((i + 14) % 16, pixels.Color(255 / 2, 0, 0));
      pixels.setPixelColor((i + 15) % 16, pixels.Color(255, 0, 0));
      pixels.show();
      delay(delay_value);
    }
  }
}
void setup() {}
void loop() {}
