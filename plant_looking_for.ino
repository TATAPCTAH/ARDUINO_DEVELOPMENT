#define sound_dot {tone(sth,100);delay(50);noTone(sth);delay(100);}
#define sound_dash {tone(sth,100);delay(500);noTone(sth);delay(100);}
#define sos{sound_dot;sound_dot;sound_dot;sound_dash;sound_dash;sound_dash;sound_dot;sound_dot;sound_dot;}
void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);//water-level
pinMode(sth,OUTPUT);//MUST BE CHANGED(relay)
pinMode(sth,OUTPUT);//MUST BE CHANGED(sound)
delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(analogRead(A0) > 200){digitalWrite(sth,HIGH);}
  else{
    digitalWrite(sth,LOW);
  while(analogRead(A0) <= 200){sos;}
  }
}
