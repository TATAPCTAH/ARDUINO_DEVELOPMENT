#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "GyverEncoder.h"
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
#define CLK 4//MUST BE CHANGED
#define DT 2//MUST BE CHANGED
#define SW 5//MUST BE CHANGED
Encoder enc1(CLK, DT, SW);
int val = 0;
void setup()
{
  enc1.setType(TYPE2);
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
//  myDFPlayer.enableLoop();
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
}

void loop()
{
  enc1.tick();
  if(enc1.isHolded()){
    myDFPlayer.next();
    Serial.println("NEXT");
    }
}
