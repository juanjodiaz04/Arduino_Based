
#include "ThingSpeak.h"
#include "WiFi.h"


const char* ssid = "BLA BLA";                        //SSID.
const char* password = "BLA BLA";                //Password.

unsigned long channelID = 1234567;                //ID ThinksSpeak.
const char* WriteAPIKey = "-----------";     //APIKey.

WiFiClient cliente;

#include "DHT.h"

#define pin1 14   //Temp
const int pg = 36;  
int gas = 0;  


DHT dht(pin1, DHT11);    

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Test de sensores:");

  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi conectado!");

  ThingSpeak.begin(cliente);

  dht.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  leerdht();
  gas = analogRead(pg);
  Serial.print("Sensor de gases: ");
  Serial.println(gas);
  delay(1000);
  Serial.println("-----------------------");
  ThingSpeak.setField (3,gas);


  ThingSpeak.writeFields(channelID,WriteAPIKey);
  Serial.println("Datos enviados a ThingSpeak!");
  delay(14000);
}

void leerdht() {
  
  float t1 = dht.readTemperature();
  float h1 = dht.readHumidity();
  

  while (isnan(t1) || isnan(h1)){
    Serial.println("Lectura fallida en el sensor DHT11, repitiendo lectura...");
    delay(2000);
    t1 = dht.readTemperature();
    h1 = dht.readHumidity();
  }

  Serial.print("Temperatura DHT11: ");
  Serial.print(t1);
  Serial.println(" ºC.");

  Serial.print("Humedad DHT11: ");
  Serial.print(h1);
  Serial.println(" %.");


  ThingSpeak.setField (1,t1);
  ThingSpeak.setField (2,h1);
}