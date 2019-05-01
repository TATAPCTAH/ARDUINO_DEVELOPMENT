#include <iarduino_DHT.h>
#include <LiquidCrystal.h>
#include <MemoryFree.h>
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);
iarduino_DHT sensor(2);
#define sound {tone(3,100);delay(500);noTone(3);delay(500);}
byte* sensor_analyze() {
  switch (sensor.read()) {
    case DHT_OK:               return new byte [2] {sensor.tem, sensor.hum}; break;
    case DHT_ERROR_CHECKSUM:   break;
    case DHT_ERROR_DATA:       break;
    case DHT_ERROR_NO_REPLY:   break;
    default:                   break;
  }
}
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////

byte** buff = 0;
int rows = 2;
int bl;//buffer length
int li;//last index
int fi;//first index
double f;//frequency
int oi;//offset index
int d;//delta
int os;//offset seconds
int ds;//delta seconds
int data;//
float ec;//elements count
int n;//number
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SD.begin(53);
  DataFile = SD.open("data.txt",FILE_WRITE);
  int memory = freeMemory() * 0.8, b = 0;
  while (memory != 1) {
    b++;
    memory /= 2;
  }
  memory = 1 << b;
  bl = memory / 2;
  fi = 0;
  li = 0;
  f = 0.5;
  oi = li;
  d = 0;
  if (buff != 0) {
    delete [] buff;
  }
  buff = new byte*[rows];
  for (int i = 0; i < rows; i++) {
    buff[i] = new byte[bl];
  }
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.write("Buff Length:");
  lcd.print(bl);
  delay(1000);
}
void loop() {
  delay(2000);
  sound;
  byte* arr = sensor_analyze();
  if (fi == (li + 1) % bl) {
    fi = (fi + bl / 5) % bl;
  }
  li = (li + 1) % bl;
  buff[0][li] = arr[0];
  buff[1][li] = arr[1];
  sound;
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.write("TEMPERATURE:");
  lcd.print(arr[0]);
  lcd.print((char)(223));
  lcd.print('C');
  lcd.setCursor(0, 1);
  lcd.write("   HUMIDITY:");
  lcd.print(arr[1]);
  lcd.write("%");
  sound;
  Serial.println((String)arr[0] + "" + arr[1]);
  if (Serial.available() > 0)
  {
    data  = Serial.read();
    sound;
   switch (data) { //data range getting function
      case '1': {
          delay(3000);
          if (Serial.available() == 4) {
            os = Serial.read() | Serial.read() << 8;
            ds = Serial.read() | Serial.read() << 8;
            oi = (bl + li - (int)(oi * f)) % bl;
           d *= f;
            if ((0 <= oi && oi < bl) && (oi >= fi || oi <= li) && (d >= 0 && d <= bl)) {
              lcd.begin(16, 2);
              lcd.setCursor(0, 0);
              lcd.print(oi);
              lcd.setCursor(0, 1);
              lcd.print(d);
              for (int i = oi; d > 0; i = (i + 1) % bl) {
                Serial.println((String)buff[0][i] + "" + buff[1][i]);
              }
            }
          }
          break;
        }
      case '0': {
          if (fi <= li) {
            ec = (li - fi + 1);
            lcd.begin(16, 2);
            lcd.setCursor(0, 0);
            lcd.print((int)(ec / f));
           lcd.setCursor(0, 1);
            lcd.print(ec);
          }
          else {
            ec = (li + 1 + bl - fi);
            lcd.begin(16, 2);
            lcd.setCursor(0, 0);
            lcd.print((int)(ec / f));
            lcd.setCursor(0, 1);
            lcd.print(ec);
          }
          ec/=f;
          //unsigned char bytes[sizeof(ec)];
          //memcpy(bytes, &ec, sizeof(ec));
          Serial.println((String)ec);
        }
    }
  }
}
