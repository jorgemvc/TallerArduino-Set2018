/** @file    FirePlayGround.cpp
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    06.Set.2018  
 *  @version 1.0 
 *  
 *  @brief   Uso de la biblioteca NeoFire
 *
 *  @licence  MIT License
 */
#include "NeoFire.h"

NeoFire ring;  // Objeto para manejar la simulación

void setup() {
  ring.begin();
}  //setup

void loop() {
  ring.draw();

  if (CircuitPlayground.readCap(3) > 10) {
    ring.playSong();
  }
}  // loop
