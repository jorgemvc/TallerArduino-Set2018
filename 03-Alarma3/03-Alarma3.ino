/** @file    03-Alarma3.cpp
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    21.Set.2018  
 *  @version 1.0 
 *  
 *  @brief   Uso de la biblioteca NeoFire
 *
 *  @licence  MIT License
 */
#include <Adafruit_NeoPixel.h>

// ---- Constantes
const int   trigPin   = 9;     // Puerto de envío
const int   echoPin   = 10;    // Puerto de recepción
const int   ledPin    = 11;    // Puerto del led (PWM)
const int   buzzerPin = 8;     // Puerto para el buzzer 
const int   potPin    = A0;    // Puerto del potenciometro
const int   touchPin  = 3;     // Puerto del touch button

// ---- Variables
float distancia;
int
  brillo,
  potValue;
bool accionada;

Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(1, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(trigPin, OUTPUT);  // Establece el puerto de salida
  pinMode(echoPin, INPUT);   // Establece el puerto de entrada
  pinMode(ledPin , OUTPUT);  // Establece el puerto de salida
  pinMode(touchPin, INPUT);  // Establece el puerto de entrada

  accionada = false;
  
  neoPixel.begin();          // Inicializa el NeoPixel
  Serial.begin(9600);        // Inicia la comunicación serial
}  // setup

void loop() {

  if (!accionada) {
    distancia = leaDistancia();
    accionada = (distancia < 30);
    // Azul
    neoPixel.setPixelColor(
      0, neoPixel.Color(0, 0, brillo)
    ); 
    neoPixel.show();
  } else if (digitalRead(touchPin) == LOW) {
    accionada = false;
  } else {
    alarma();
  }
    
  // Lee el potenciometro para fijar el brillo
  potValue = analogRead(potPin);
  brillo = map(potValue, 0, 1023, 0, 255);
}  // loop

void alarma(){
  // Rojo
  neoPixel.setPixelColor(
    0, neoPixel.Color(0, brillo, 0)
  );
  neoPixel.show();
  tocaTono(750, 150);
  // Rojo
  neoPixel.setPixelColor(
    0, neoPixel.Color(0, 0, 0)
  );
  neoPixel.show();
  delay(150);
}  // alarma

void tocaTono(
  int tono,
  int tiempo  
){
  tone(buzzerPin, tono, tiempo);
  delay(tiempo);
  noTone(buzzerPin);  
}

float leaDistancia() {
float
  duracion,                  // Tiempo de vuelo
  distancia;                 // Distancia en cm

  //  Limpia el puerto de envío
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Pone el puerto de envío en HIGH por 5 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Lee la señal de regreso de la onda de sonido en microsegundos
  duracion = pulseIn(echoPin, HIGH);
  
  // Calcula la distancia
  return ((duracion / 2.0) / 29.4118);
}  // leaDistancia
