#include <SoftwareSerial.h>
#include <Encoder.h>

// Definir los pines RX y TX para el módulo Bluetooth HC-05
const int bluetoothTx = 4;  // Pin TX del módulo Bluetooth conectado al pin RX de Arduino
const int bluetoothRx = 5;  // Pin RX del módulo Bluetooth conectado al pin TX de Arduino

SoftwareSerial BTSerial(bluetoothTx, bluetoothRx);

// Pines del encoder
const int pinA = 2;
const int pinB = 3;
const int pulsesPerRevolution = 2000;  // Número de huecos del encoder (Pulsos por Revolución)

// Variables para el cálculo de la velocidad
volatile long pulseCount = 0;
unsigned long previousMillis = 0;
const long interval = 1000; // Intervalo de tiempo para el cálculo de la velocidad (ms)

Encoder myEncoder(pinA, pinB);

// Pines y variables del PWM y sensor de corriente
const int pwmPin = 9;
int pwm_octo = 100;
int receivednum = 0;
const int offs = 2540;
const float sf = 1000/185.0;

float V;
float Vr;
int curr;
int RPM;
int volt;

// Para enviar datos a la aplicación
unsigned long previousDataMillis = 0;
const long dataInterval = 500;  // Intervalo de tiempo para leer y enviar datos analógicos (500 ms)
String volt_curr;

void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);
  pinMode(pwmPin, OUTPUT);
  pwm_octo = 101; // Inicializa el ciclo de trabajo PWM en 101

  // Configura los pines de interrupción para los canales A y B
  attachInterrupt(digitalPinToInterrupt(pinA), pulseCounter, RISING);
  attachInterrupt(digitalPinToInterrupt(pinB), pulseCounter, RISING);
}

void loop() {
  // Leer el Sensor de Corriente
  V = analogRead(A3);
  Vr = (V/1023.0)*5000.0;
  curr = (Vr - offs) * sf;

  if (BTSerial.available()) {
    // Leer el dato recibido desde el módulo Bluetooth
    int numero = BTSerial.parseInt();
    
    if (numero > 0 && numero <= 101) {
      pwm_octo = 101 - numero;
      volt = 60*(100 - pwm_octo)/(100);
      Serial.print("PWM set to: ");
      Serial.println(numero - 1);
    }
  }

  analogWrite(pwmPin, map(pwm_octo, 0, 100, 0, 255)); // Escribe el valor PWM en el pin

  // Obtener el tiempo actual
  unsigned long currentMillis = millis();
  
  // Verificar si ha pasado el intervalo deseado para calcular RPM
  if (currentMillis - previousMillis >= interval) {
    // Guardar el tiempo actual
    previousMillis = currentMillis;

    // Calcular la velocidad en RPM
    long pulses = pulseCount; // Copiar el valor de pulseCount de forma atómica
    pulseCount = 0; // Reiniciar el contador de pulsos
    RPM = (pulses / (double)pulsesPerRevolution) * (60000.0 / interval);
    
    // Imprimir la velocidad en RPM en el monitor serial
  }

  // Verificar si ha pasado el intervalo deseado para enviar datos
  if (currentMillis - previousDataMillis >= dataInterval) {
    // Guardar el tiempo actual
    previousDataMillis = currentMillis;

    // Construir la cadena de datos
    volt_curr = String(volt) + "," + String(curr) + "," + String(RPM);

    // Enviar el valor leído a través del módulo Bluetooth
    BTSerial.println(volt_curr);
  }
}

// Función de interrupción para contar los pulsos del encoder
void pulseCounter() {
  pulseCount++;
}



