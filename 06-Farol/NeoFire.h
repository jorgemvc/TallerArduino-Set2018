/** @file    NeoFire.h
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    06.Set.2018  
 *  @version 1.0 
 *  
 *  @brief   Simulación de fuego con Circuit Playground
 *
 *  @licence  MIT License
 */
#include <Adafruit_CircuitPlayground.h>
#include <Arduino.h>
#include "Notes.h"
#ifndef NEOFIRE_H
#define NEOFIRE_H
class NeoFire {
  #define COUNT 10    // Cantidad de leds

  public:
    // ---- Constructor
    NeoFire();

    // ---- Variables públicas
    uint8_t  factor = 2;

    // ---- Métodos Públicos
    void begin();
    void draw();
    void clear();
    void addColor(uint8_t position, uint32_t color);
    void subColor(uint8_t position, uint32_t color);
    void setColor(uint8_t position, uint32_t color);
    uint32_t blend(uint32_t color1, uint32_t color);
    uint32_t substract(uint32_t color1, uint32_t color2);
    uint32_t color(uint8_t r, uint8_t g, uint8_t b);
    void playSong();
    
  private:
    // ---- Constantes privadas
    const static uint32_t FIRECOLOR = 0x502300;
    const static uint8_t  OFFCOLOR  = 0x000000;
    const static uint8_t  MUSICLEN  = 22;  // Cantidad de notas de la música
    
    // ---- Variables privadas
    uint32_t colors[COUNT];

    int music[MUSICLEN][2] = {
      {a3 , 1500}, {gS3, 500 }, {b3 , 1000}, {a3 , 1500}, 
      {a3 , 500 }, {d4 , 1000}, {cS4, 1500}, {b3 , 500},
      {cS4, 1000}, {b3 , 2000}, {0  , 1000}, {cS4, 1500}, 
      {d4 , 500 }, {e4 , 1000}, {cS4, 1500}, {a3 , 500},
      {b3 , 1000}, {a3 , 1500}, {gS3, 500 }, {b3 , 1000},
      {a3 , 2000}, {0  , 5000}
    };

    // ---- Métodos privados
};
#endif
