     
    #include <LiquidCrystal.h>  

    LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
      int i =0;
    void setup() {  
      Serial.begin(9600);
      
       //impostiamo il numero di colonne ed il numero di righe di lcd  
      lcd.begin(16, 2);  
      // Visualizzo il messaggio sul display  
      lcd.print("Salve mondo!");  
    }  
      
    void loop() {  
      
      while (Serial.available()){
        char inChar = (char)Serial.read();
        lcd.setCursor(i,1);
        lcd.print(inChar);
        i=i+1;
        if (i==16){
          i=0;
        }
      } 
    }  
