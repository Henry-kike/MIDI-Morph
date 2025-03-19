#include "config.h"


unsigned long sustain_calcule(unsigned long blck){
  unsigned long m;
  m=(0.8*blck)/4095;//0.8 -> 80%
  return (m*analogRead(GATE_PIN) + blck*GATE_MIN);
}

uint8_t velocity_calcule(){
  int vel = analogRead(VELOCITY_PIN);
  return map(vel, 0, 4096, 10, 127);
}