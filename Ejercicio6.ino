#include <LiquidCrystal.h>

const int pinTemp=A0;
LiquidCrystal lcd(12,11,5,4,3,2);
float temperatura;
float TempA;

void setup() {
  lcd.begin(16,2);
  lcd.print("Temperatura ");
  
  float initTemp=((analogRead(pinTemp)/1024.0)*5-0.5)*100;
  delay(5);
  lcd.print(initTemp);
}

void loop() {
  
    TempA=((analogRead(pinTemp)/1024.0)*5-0.5)*100;
    lcd.setCursor(0,1);
    lcd.print("Temperatura ");
    lcd.print(TempA);
    lcd.setCursor(0,1);
    delay(1000);
    
  }
