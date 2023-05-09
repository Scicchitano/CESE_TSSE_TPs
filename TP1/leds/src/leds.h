/*#ifndef LEDS_H
#define LEDS_H*/
#include <stdint.h>

void ledsInit(uint16_t *direccion);

uint8_t ledsTurnOnSingle(uint8_t led);

uint8_t ledsTurnOffSingle(uint8_t led);

uint8_t isTurnedOn(uint8_t led);

void ledsTurnOnAll();

void ledsTurnOffAll();

//#endif