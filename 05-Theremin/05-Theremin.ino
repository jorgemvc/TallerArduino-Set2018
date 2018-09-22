/** @file    05-Theremin.cpp
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    21.Set.2018  
 *  @version 1.0 
 *  
 *  @brief   Uso del sensor de luz para manejar el sonido
 *
 *  @licence  MIT License
 */
#include <Adafruit_CircuitPlayground.h>
#include "Notas.h"

int color[3][3] = {
  {155, 0  , 0  },
  {0  , 155, 0  },
  {0  , 0  , 155}  
};

int notas[3][12] = {
  {c3, cS3, d3, dS3, e3, f3, fS3, g3, gS3, a3, aS3, b3},
  {c4, cS4, d4, dS4, e4, f4, fS4, g4, gS4, a4, aS4, b4},
  {c5, cS5, d5, dS5, e5, f5, fS5, g5, gS5, a5, aS5, b5}
};
int 
  minVal = 100, 
  maxVal = 0, 
  senVal, 
  nota,
  escala = 1,
  capSen = 0;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();  
  PlaySound();
}  // setup

void loop() {
  // Modo de calibración
  if (CircuitPlayground.slideSwitch()) {
    CircuitPlayground.clearPixels();
    Serial.println("Calibrando ...");
    senVal = CircuitPlayground.lightSensor();
    minVal = min(senVal, minVal);
    maxVal = max(senVal, maxVal);
    
    Serial.print("Valor: ");
    Serial.print(senVal);
    Serial.print(" - MinVal: ");
    Serial.print(minVal);
    Serial.print(" - MinVal: ");
    Serial.println(maxVal);
    delay(100);
  } else {
    capSen = CircuitPlayground.readCap(3);
    Serial.print("Capsense #3: "); 
    Serial.println(capSen);
    Serial.println("Jugando ...");
    senVal = CircuitPlayground.lightSensor();
    senVal = constrain(senVal, minVal, maxVal);
    nota = map(senVal, minVal, maxVal, 0, 11);
    Serial.print("Valor: ");
    Serial.print(senVal);
    Serial.print("- MinVal: ");
    Serial.print(minVal);
    Serial.print(" - MinVal: ");
    Serial.print(maxVal);
    Serial.print(" - Escala: ");
    Serial.print(escala);
    Serial.print(" - Nota: ");
    Serial.println(nota);
    CircuitPlayground.clearPixels();
    for (int i = 0 ; i < nota ; i++) {
       CircuitPlayground.setPixelColor(i, 
         color[escala][0], color[escala][1], color[escala][2]);      
    }
    if (capSen > 30) {
      CircuitPlayground.playTone(notas[escala][nota], 100);
      delay(50);
    }
    if (CircuitPlayground.leftButton() && (escala > 0)){
      escala--;
      delay(100);
    }
    if (CircuitPlayground.rightButton() && (escala < 2)){
      escala++;
      delay(100);
    }
  }
}

void PlaySound() {
  for (int i = 0 ; i < 3 ; i++) {
    CircuitPlayground.clearPixels();
    for (int j = 0 ; j < 12 ; j++) {
      if (i < 10) {
       CircuitPlayground.setPixelColor(j, 
         color[i][0], color[i][1], color[i][2]);
      } 
      CircuitPlayground.playTone(notas[i][j], 500);
      delay(50);
  }    
  }
  delay(1000);  
  CircuitPlayground.clearPixels();
}
