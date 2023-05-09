#include "leds.h"
static uint16_t * puerto_virtual;

#define ALL_LEDS_OFF 1
#define FIRST_BIT 1
#define GPIO_ON 1
#define GPIO_OFF 0

uint16_t IndexToMask(uint8_t led){
    return (ALL_LEDS_OFF << led-FIRST_BIT);
}

uint8_t checkArgLED(uint8_t led){
    if (led>=17){
        return 0;
    }else{
        if (led<=0){
            return 0;
        }
    }
    return 1;
}

void ledsInit(uint16_t *direccion){
    puerto_virtual=direccion;
    *puerto_virtual=0;
}

uint8_t ledsTurnOnSingle(uint8_t led){
    if (checkArgLED(led)){
        *puerto_virtual |= IndexToMask(led);
        return 1;
    }
    return 0;    
}

uint8_t ledsTurnOffSingle(uint8_t led){
    if (checkArgLED(led)){
        *puerto_virtual &= ~IndexToMask(led);
        return 1;
    }
    return 0;
    
}

uint8_t isTurnedOn(uint8_t led){
    if ((*puerto_virtual) & (GPIO_ON<<led-FIRST_BIT))   
    {
        return 1;
    }    
    return 0;
}

void ledsTurnOnAll(){
    *puerto_virtual = 0xFFFF;
}

void ledsTurnOffAll(){
    *puerto_virtual = 0x0000;
}
