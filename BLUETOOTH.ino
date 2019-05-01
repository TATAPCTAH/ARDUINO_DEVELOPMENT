#include <iarduino_DHT.h> 
iarduino_DHT sensor(2); 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
}
void loop() {
  if(Serial.available() > 0)
   {
      int data = Serial.read();
      if(data == '1'){
        delay(1000);
        Serial.println("Ok wait.");
        delay(1000);
        Serial.println("Database loading");
        delay(1000);
        int massiv1[360];
        int massiv2[360];
        for(int i = 0;i < 360;i++){
          switch(sensor.read()){
    case DHT_OK:               massiv1[i]=sensor.tem;massiv2[i]=sensor.hum; break;
    case DHT_ERROR_CHECKSUM:   break;
    case DHT_ERROR_DATA:       break;
    case DHT_ERROR_NO_REPLY:   break;
    default:                   break;
  }
  if(i == 0){Serial.println("loaded 0%");tone(9,10,500);}
  if(i == 90){Serial.println("loaded 25%");tone(9,10,500);}
  if(i == 180){Serial.println("loaded 50%");tone(9,10,500);}
  if(i == 270){Serial.println("loaded 75%");tone(9,10,500);}
           delay(2000);}
           Serial.println("loaded 100%");
           delay(1000);
           tone(9,10,500);
           for(int i = 0;i < 360;i++){Serial.println(massiv1[i]);delay(100);tone(9,10,500);}
           for(int i = 0;i < 360;i++){Serial.println(massiv2[i]);delay(100);tone(9,10,500);}}
}
}
