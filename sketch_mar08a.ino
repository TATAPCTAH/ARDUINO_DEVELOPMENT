#include <SoftwareSerial.h>
#include <BME280I2C.h>
#include <Wire.h> 
#include <SPI.h>
BME280I2C bme;
SoftwareSerial conn(51,2);
void setup() {
  pinMode(51,INPUT);
  pinMode(2,OUTPUT);
  conn.begin(9600);
  Serial.begin(9600);
}
bool metric = true;
void printBME280Data(){
  float temp(NAN), humi(NAN), pres(NAN);
   uint8_t pressureUnit(3);
   bme.read(pres, temp, humi, metric, pressureUnit);
   conn.write(int(temp));
   Serial.println((String)int(temp) + "ARDUINO");
   while(conn.available() > 0){}
   int b = conn.read();
   while(conn.available() > 0){}
    conn.write(int(humi));
   Serial.println((String)int(humi) + "ARDUINO");
   int f = conn.read();
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  printBME280Data();
}
