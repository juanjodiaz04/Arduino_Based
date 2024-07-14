#include <Adafruit_L3GD20.h>
#include <Adafruit_L3GD20_U.h>
#include <LSM303.h>


#define MOSTRAR_DATOS
//#define MOSTRAR_DATOS_COMAS
LSM303 compass;

float beta = (0.160 / 1000); //factor de conversion para magnetómetro. Retorna datos en gauss
float gama = (0.061 / 1000); //factor de coneversión aceleracion (AUN POR CONFIRMAR). Rretorna datos en g
float ax = 0;
float ay = 0;
float az = 0;
float mx = 0;
float my = 0;
float mz = 0;

Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);// Giroscopo

float gx = 0;
float gy = 0;
float gz = 0;


void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
   // Inicializar Acelerometro y Magnetometro

  if (compass.init());
  {
    Serial.println("LSM303 iniciado correctamente \n");
  }

  if (!compass.init()) {
    Serial.println("Error al iniciar LSM303 \n");
    while (1);
  }
  compass.enableDefault();

  // Giroscopo
  gyro.enableAutoRange(true);

  if (!gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.println("Error al iniciar L3GD20 \n");
    while (1);
  }
  else {
    Serial.println("L3GD20 iniciado correctamente \n");
  }

}

void loop() {
  // Acelerometro y Magnetometro
  compass.read();

  ax = compass.a.x * (gama); //Aceleracion con conversión
  ay = compass.a.y * (gama);
  az = compass.a.z * (gama);

  mx = compass.m.x * (beta); //Intensidad del campo con conversión
  my = compass.m.y * (beta);
  mz = compass.m.z * (beta);

  // Giroscopo
  sensors_event_t event;
  gyro.getEvent(&event);

  gx = event.gyro.x;
  gy = event.gyro.y;
  gz = event.gyro.z;

#ifdef  MOSTRAR_DATOS
  //Serial.println("Tiempo: " + String(tiempo) + " ms");
  //Serial.print("Altitud relativa : "); // Barometro
  //Serial.print(Altura);
  //Serial.println(" m");
  //Serial.println("-----------Analisis Altura----------------");
  //Serial.println("\tAscensoMaximo: " + String(ascensoMaximo));
  //Serial.println("\tDescensoMaximo: " + String(descensoMaximo));
  //Serial.println("-----------------------------------------");
  //Serial.println("\tAscenso actual: " + String(ascensoActual));
  //Serial.println("\tDescenso actual: " + String(descensoActual));
  //Serial.println("\tDelta altura: " + String(deltaAltura));
  Serial.println("-----------------------------------------");
  Serial.println("-----------------------------------------");
  Serial.print("\tAx: "); Serial.print(ax); Serial.print("  "); // Acelerometro y Magnetometro
  Serial.print("Ay: "); Serial.print(ay); Serial.print("  ");
  Serial.print("Az: "); Serial.print(az); Serial.println("  ");
  Serial.print("\tMx: "); Serial.print(mx); Serial.print("  ");
  Serial.print("My: "); Serial.print(my); Serial.print("  ");
  Serial.print("Mz: "); Serial.print(mz); Serial.println("  ");
  Serial.print("\tGx: "); Serial.print(gx); Serial.print("  "); // Giroscopo
  Serial.print("Gy: "); Serial.print(gy); Serial.print("  ");
  Serial.print("Gz: "); Serial.print(gz); Serial.println("  ");
  Serial.println("-----------------------------------------");
  Serial.println("-----------------------------------------");
#endif

#ifdef MOSTRAR_DATOS_COMAS
  /*
    Serial.print(String(tiempo) + ',' + String(Altura) + ',' + String(ascensoMaximo) + ',');
    Serial.print(String(descensoMaximo) + ',' + String(ascensoActual) + ',' + String(descensoActual));
    Serial.print(',' + String(deltaAltura));
    Serial.print(',' + String(ax) + ',' + String(ay) + ',' + String(az)
                 + ',' + String(mx) + ',' + String(my) + ',' + String(mz));
    Serial.println(',' + String(gx) + ',' + String(gy) + ',' + String(gz));
  */
  Serial.println( String(ax) + ',' + String(ay) + ',' + String(az));
                 

  //Serial.println(String(tiempo) + ',' + String(ax) + ',' + String(ay) + ',' + String(az) + String(Altura) );
#endif
delay (100);
}
