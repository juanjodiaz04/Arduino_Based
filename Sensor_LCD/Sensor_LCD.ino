//RETOS 

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>

//Ultrasonido
const int EchoPin = 2;
const int TriggerPin = 3;
int cm; 

//Relé
const int rele = 41;

//Variables Sensor de Lluvia
int analog; //Variable donde se va a almacenar lo que lea el pin A0
int dig;
int vol;

//Variables Motor
int enA = 10;
int in3 = 8;
int in4 = 9;

byte Ban = true;


//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //

void setup() {
  //Serial
  Serial.begin(9600);
  //Luvia
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  //Relé
  pinMode(rele, OUTPUT); 
  //Motor
  pinMode(enA, OUTPUT);
  pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
  //Estado Inicial
  digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);

  //Interruption
  Timer1.initialize(200000);
  Timer1.attachInterrupt(int_timer);


  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  lcd.print("Intro Ing Electr");
  delay(1000);
  lcd.clear(); //Borra la pantalla
}

void loop() {
  
  analog = analogRead(14);
  vol = map(analog,0,1023,0,6);
  digitalWrite(rele, LOW);


if (vol <= 3){
  lcd.clear();
     // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 0);
   // Escribimos el número de segundos trascurridos
  lcd.print("USOUND: ");
  lcd.setCursor(8, 0);
  lcd.print(cm);
  lcd.setCursor(11, 0);
  lcd.print("cm");

  lcd.setCursor(0, 1);
  lcd.print("Hay Lluvia ");
  lcd.setCursor(12, 1);
  lcd.print(vol);
  lcd.setCursor(14, 1);
  lcd.print("V");
  delay(300);

  if (cm <= 5) {
    lcd.setCursor(0, 1);
    lcd.print("               ");
    lcd.setCursor(0, 1);
    lcd.print("Max NV de agua");
    }
  else if (cm > 5  && Ban == true) {
      //Abre la Compuerta
        digitalWrite(in3, LOW);
	      digitalWrite(in4, HIGH);
        digitalWrite(enA,80);
        delay(2000);
        digitalWrite(in3, LOW);
	      digitalWrite(in4, LOW);

        while (cm > 5){
          lcd.setCursor(0, 1);
          lcd.print("               ");
          lcd.setCursor(0, 1);
          lcd.print("Llenando");
          delay(100);
        }
        lcd.setCursor(0, 1);
        lcd.print("               ");
        lcd.setCursor(0, 1);
        lcd.print("Max NV de agua");
        delay(100);

        digitalWrite(in3, HIGH);
	      digitalWrite(in4, LOW);
        digitalWrite(enA,80);
        delay(2000);
        digitalWrite(in3, LOW);
	      digitalWrite(in4, LOW);

        

    }
    lcd.setCursor(0, 1);
    lcd.print("               ");
    lcd.setCursor(0, 1);
    lcd.print("Vaciando");
    delay(100);
    digitalWrite(rele, HIGH);
    delay(1000);

  
}
else if (vol > 3){
  lcd.clear();
     // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 0);
   // Escribimos el número de segundos trascurridos
  lcd.print("USOUND: ");
  lcd.setCursor(8, 0);
  lcd.print(cm);
  lcd.setCursor(11, 0);
  lcd.print("cm");
  

  lcd.setCursor(0, 1);
  lcd.print("No Lluvia ");
  lcd.setCursor(11, 1);
  lcd.print(vol);
  lcd.setCursor(13, 1);
  lcd.print("V");
  delay(1000);
  
}
}

int ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;
  
  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  
  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  
  distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
  return distanceCm;
}

void int_timer(){
  cm = ping(TriggerPin, EchoPin);
  Serial.print("Distancia: ");
  Serial.println(cm);
  if (cm <=4) {
    Ban = false;
  }
  else {
    Ban = true;
  } 
}
