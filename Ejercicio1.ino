int ledPin = 13;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the serial input
  char state = Serial.read();
  if(state=='H'){
  digitalWrite(ledPin,HIGH);
  } else if (state==L){
  digitalWrite(ledPin,LOW);
  }
  delay(1);        // delay in between reads for stability
}


