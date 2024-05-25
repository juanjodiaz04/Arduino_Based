int LDR_pin1 = A1;  // Leeremos el pin 0
int LDR_val1 = 0;
int LDR_pin2 = A0;
int LDR_val2 = 0;
float DIFF;
float vel;
float vel2;
unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
unsigned long TiempoTotal = 0;
String T1="Obstaculo detectado en sensor 1 en t= ";
String T2="Obstaculo detectado en sensor 2 en t= ";
String TT="Tiempo total empleado T= ";
float speedConst = 54;
float speedConst2 = 3.6;

void setup(){
pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
Serial.begin(9600);

Serial.println("*** Sensores listos: Leyendo... ***");
}

void loop(){
LDR_val1 = analogRead(LDR_pin1);
LDR_val2 = analogRead(LDR_pin2);  
digitalWrite(12, HIGH);
digitalWrite(13, HIGH);



  if (LDR_val1 >= 40) {
    tiempo1=millis();
    delay(10);  
  }
    while(tiempo2<tiempo1){
      LDR_val2 = analogRead(LDR_pin2);
      if (LDR_val2 >= 40) { 
        tiempo2=millis();     
        
        delay(5);
      }
      delay(5);
    }

DIFF= tiempo2 - tiempo1;
vel = speedConst / DIFF;
vel2 = vel/speedConst2;
Serial.println(TT);
Serial.println(DIFF);
Serial.print("Vel km/h = ");
Serial.println(vel);
Serial.print("Vel m/s = ");
Serial.println(vel2);
}
