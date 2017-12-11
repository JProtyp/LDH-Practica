
int segPins[] = { 
 0, 1, 2, 3, 4, 5, 6, 7}; 
 
 int tiempototal= 1000;
 
 int j = 40;
 
 
 
 int disp1 =8;
 int disp2= 9;
 
 int dat1 = 1;
 int dat0 = 0;
 
void setup() {
  // put your setup code here, to run once:
 // loop over the pin array and set them all to output:
  for (int thisseg = 0; thisseg < 8; thisseg++) {
    pinMode(segPins[thisseg], OUTPUT); 
  }
  pinMode(disp1, OUTPUT);
  pinMode(disp2, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly: 
//  dat1 = 0;
//  dat0 = 0;
// while (1) {
//LLamada a función refresh pasando los datos correctos


// Cálculo correcto de los datos dat1, dat0 --> desde 0 0  hasta 5 9
refresh(dat1,dat0);
dat0 = dat0 + 1;
  if(dat0 ==10){
    dat0 = 0;
    dat1 = dat1 + 1;
  }
  if(dat1 == 2 ) {
    dat1 = 1;
  }
     
}

// Función refresh: Duración total de ejecución de refresh: tiempototal. 
//Se van intercambiando los displays (disp1 con dat0 y disp2 con dat1) a una frecuencia que evite el parpadeo (j--> numero de veces que se activan ambos displays) 
void refresh( int data1, int data0) {
  int tiempo_refresco = tiempototal/(2*j);
  while(j>0){
   digitalWrite(disp2,LOW);
   digitalWrite(disp1,HIGH);
   write_data(data1);
   delay(tiempo_refresco);
   digitalWrite(disp1,LOW);
   digitalWrite(disp2,HIGH);
   write_data(data0);
   delay(tiempo_refresco);
   j =j - 1;
  }
  j =40;
// Bucle de activación de los displays. El bucle se ejecuta j veces. Para escribir en los displays se llama a la función write_data (dato)

}


// Función write_data(dato): Transforma dato en su código siete segmentos para escribirlo en el display

void write_data (int arg) {
  
  switch (arg) {
    case 0:
      //do something when var equals 1
      write7seg(0x7e);
      break;
    case 1:
      //do something when var equals 2
       write7seg(0x30);
      break;
    case 2:
      //do something when var equals 1
      write7seg(0x6d);
      break;
    case 3:
      //do something when var equals 2
       write7seg(0x79);
      break;
    case 4:
      //do something when var equals 1
      write7seg(0x33);
      break;
    case 5:
      //do something when var equals 2
       write7seg(0x5b);
      break;
    case 6:
      //do something when var equals 1
      write7seg(0x1f);
      break;
    case 7:
      //do something when var equals 2
       write7seg(0x70);
      break;
     case 8:
      //do something when var equals 1
      write7seg(0x7f);
      break;
      case 9:
      //do something when var equals 1
      write7seg(0x73);
      break;
  
  }
  
}

// Función write7seg(dato_7seg): escribe el valor dato_7seg en el dsiplay

void write7seg (unsigned char arg) {
  unsigned char segmen = 0x01;
  unsigned char display1;
  display1 = arg;
  
  for (int i = 0; i < 8; i++) {
  if ((display1 & segmen) == 0x00)
    digitalWrite(i, LOW);
  else
    digitalWrite(i, HIGH);
    
  segmen <<= 1; }
  
}
  
