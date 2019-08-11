#include <SoftwareSerial.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mp3(10, 11);
DFRobotDFPlayerMini myDFPlayer;
//SoftwareSerial hc05(2, 3);
int val = 10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mp3.begin(9600);
  if (!myDFPlayer.begin(mp3)) {  //Use softwareSerial to communicate with mp3.
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  myDFPlayer.volume(10);
  myDFPlayer.play(1);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available() > 0){
  char data = Serial.read();
  if(data == 's' || data == 'S'){Serial.println("START");myDFPlayer.start();}
  else if(data == 'p' || data == 'P'){Serial.println("PAUSE");myDFPlayer.pause();}
  else if(data == 'n' || data == 'N'){Serial.println("NEXT");myDFPlayer.next();}
  else if(data == 'b' || data == 'B'){Serial.println("PREVIOUS");myDFPlayer.previous();}
  else if(data == 'u' || data == 'U'){Serial.println("VOLUME UP");myDFPlayer.volumeUp();}
  else if(data == 'd' || data == 'D'){Serial.println("VOLUME DOWN");myDFPlayer.volumeDown();}
  }
}
