#include <Servo.h>

Servo servo;
int val;

void setup(){
servo.attach(9);
Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
   val=Serial.parseInt();
   if(val>180) {
    val =180;
   } else if (val < 0) {
     val =0;
  }
  }
  delay(5);
}
