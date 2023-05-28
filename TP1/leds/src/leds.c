#include "leds.h"
static uint16_t *puerto_virtual;

#define ALL_LEDS_OFF 0x0000
#define ALL_LEDS_ON 0xFFFF
#define MAX_NUMBER_LED 16
#define MIN_NUMBER_LED 0
#define FIRST_BIT 1
#define GPIO_ON 1
#define GPIO_OFF 0
#define NUMBER_TRUE 1
#define NUMBER_FALSE 0

uint16_t IndexToMask(uint8_t led)
{
    return (GPIO_ON << led - FIRST_BIT);
}

uint8_t checkArgLED(uint8_t led)
{
    if (led > MAX_NUMBER_LED)
    {
        return NUMBER_FALSE;
    }
    else
    {
        if (led < MIN_NUMBER_LED)
        {
            return NUMBER_FALSE;
        }
    }
    return 1;
}

void ledsInit(uint16_t *direccion)
{
    puerto_virtual = direccion;
    ledsTurnOffAll();
}

uint8_t ledsTurnOnSingle(uint8_t led)
{
    if (checkArgLED(led))
    {
        *puerto_virtual |= IndexToMask(led);
        return NUMBER_TRUE;
    }
    return NUMBER_FALSE;
}

uint8_t ledsTurnOffSingle(uint8_t led)
{
    if (checkArgLED(led))
    {
        *puerto_virtual &= ~IndexToMask(led);
        return NUMBER_TRUE;
    }
    return NUMBER_FALSE;
}

uint8_t isTurnedOn(uint8_t led)
{
    if ((*puerto_virtual) & (GPIO_ON << led - FIRST_BIT))
    {
        return NUMBER_TRUE;
    }
    return NUMBER_FALSE;
}

void ledsTurnOnAll()
{
    *puerto_virtual = ALL_LEDS_ON;
}

void ledsTurnOffAll()
{
    *puerto_virtual = ALL_LEDS_OFF;
}
