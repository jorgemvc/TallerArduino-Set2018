/** @file    08-UltrasonicoNeopixelPot.ino
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    04.Ago.2018  
 *  @version 1.0 
 *  
 *  @brief   Lectura de un sensor ultrasonico, combinado
 *           con un NeoPixel y un potenciometro.
 *
 *  @licence  MIT License
 */
#include <Adafruit_NeoPixel.h>

// ---- Constantes
const int   trigPin = 9;     // Puerto de envío
const int   echoPin = 10;    // Puerto de recepción
const float factor  = 1.0;   // Factor de ajuste
const int   ledPin  = 11;    // Puerto del led (PWM)
const int   potPin  = A0;    // Puerto del potenciometro

// ---- Variables
float
  duration,                  // Tiempo de vuelo
  distance;                  // Distancia en cm
int brillo;
int potValue;
Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(1, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(trigPin, OUTPUT);  // Establece el puerto como de salida
  pinMode(echoPin, INPUT);   // Establece el puerto como de entrada
  pinMode(ledPin , OUTPUT);  // Establece el puerto como de salida

  neoPixel.begin();          // Inicializa el NeoPixel
  Serial.begin(9600);        // Inicia la comunicación serial
}  // void setup

void loop() {
  //  Limpia el puerto de envío
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Pone el puerto de envío en HIGH por 5 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Lee la señal de regreso de la onda de sonido en microsegundos
  duration = pulseIn(echoPin, HIGH);
  
  // Calcula la distancia
  distance = ((duration / 2.0) / (29.4118*factor));
  distance = constrain(distance, 3, 300);

  // Lee el potenciometro para fijar el brillo
//  potValue = analogRead(potPin);
//  brillo = map(potValue, 0, 1023, 0, 255);
brillo = 200;

  // GRB
  if (distance >= 20) {
    // Verde
    neoPixel.setPixelColor(
      0, neoPixel.Color(brillo, 0, 0)
    );
  } else if (distance >= 10) {
    // Amarillo
    neoPixel.setPixelColor(
      0, neoPixel.Color(brillo, brillo, 0)
    );
  } else {
    // Rojo
    neoPixel.setPixelColor(
      0, neoPixel.Color(0, brillo, 0)
    );
  }
  neoPixel.show();
  
  // Muestra el resultado en el monitor serial
  Serial.print("Distancia en cm: ");
  Serial.print(distance);
  Serial.print(" - potValue: ");
  Serial.println(potValue);

  // Muestra el resultado para el Serial Plotter
//  Serial.print(distance);
//  Serial.print(",");
//  Serial.println(brillo);
} // void loop
