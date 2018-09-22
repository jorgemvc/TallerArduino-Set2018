/** @file    NeoFire.cpp
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    06.Set.2018  
 *  @version 1.0 
 *  
 *  @brief   Simulación de fuego con Circuit Playground
 *
 *  @licence  MIT License
 */
#include "NeoFire.h"

NeoFire::NeoFire() {
}

void NeoFire::begin(){
  CircuitPlayground.begin();
  this->clear();
}  // begin

void NeoFire::clear(){
  CircuitPlayground.clearPixels();
  for (int i = 0 ; i < COUNT ; i++) {
    colors[i] = OFFCOLOR;    
  }
}  // clear

void NeoFire::draw(){
  this->clear();

  for (int i = 0 ; i < COUNT ; i++){
    addColor(i, FIRECOLOR);
    int r = random(80);
    uint32_t diff_color = color(r, r/2, r/2);
    subColor(i, diff_color);
  }
  delay(random(50,150));
}  // draw

void NeoFire::addColor(
  uint8_t  position,
  uint32_t color  // GRB
){
  uint32_t blended_color = blend(colors[position], color);
  setColor(position, blended_color);
}  // addColor

void NeoFire::subColor(
  uint8_t position,
  uint32_t color
){
  uint32_t blended_color = substract(colors[position], color);
  setColor(position, blended_color);  
}  // subColor

uint32_t NeoFire::blend(
  uint32_t color1,
  uint32_t color2
) {
  uint8_t rc1, gc1, bc1;
  uint8_t rc2, gc2, bc2;
  uint8_t rc , gc , bc ;

  rc1 = (uint8_t)(color1 >> 16),
  gc1 = (uint8_t)(color1 >>  8),
  bc1 = (uint8_t)(color1 >>  0);

  rc2 = (uint8_t)(color2 >> 16),
  gc2 = (uint8_t)(color2 >>  8),
  bc2 = (uint8_t)(color2 >>  0);

  rc = constrain(rc1 + rc2, 0, 255);
  gc = constrain(gc1 + gc2, 0, 255);
  bc = constrain(bc1 + bc2, 0, 255);

  return color(rc, gc, bc);
}  // blend

void NeoFire::setColor(
  uint8_t position,
  uint32_t color  // GRB
) {
  CircuitPlayground.setPixelColor(position, color);
  colors[position] = color;
}  // setColor

uint32_t NeoFire::substract(
  uint32_t color1, 
  uint32_t color2
) {
  uint8_t rc1, gc1, bc1;  // Colores RGB del color1
  uint8_t rc2, gc2, bc2;  // Colores RGB del color1
  int16_t rc , gc , bc;   // Colores RGB del resultado
  
  rc1 = (uint8_t)(color1 >> 16),
  gc1 = (uint8_t)(color1 >>  8),
  bc1 = (uint8_t)(color1 >>  0);
  
  rc2 = (uint8_t)(color2 >> 16),
  gc2 = (uint8_t)(color2 >>  8),
  bc2 = (uint8_t)(color2 >>  0);
  
  rc = (int16_t)rc1 - (int16_t)rc2;
  gc = (int16_t)gc1 - (int16_t)gc2;
  bc = (int16_t)bc1 - (int16_t)bc2;

  if (rc < 0) rc = 0;
  if (gc < 0) gc = 0;
  if (bc < 0) bc = 0;
  
  return color(rc, gc, bc);
}  // substract

uint32_t NeoFire::color(
  uint8_t rc, 
  uint8_t gc, 
  uint8_t bc
) {
  return ((uint32_t)rc << 16) | ((uint32_t)gc <<  8) | bc;
}  // color

void NeoFire::playSong(){
  for (int i = 0 ; i < MUSICLEN ; i++) {
    CircuitPlayground.playTone(
      music[i][0], 
      music[i][1]/factor
    );
  } 
}  // playSong
