#include "unity.h"
#include "leds.h"
#include <stdint.h>

#define ALL_LEDS_OFF 0x0000
#define ALL_LEDS_ON 0xFFFF

// La funcion que prende todos, no deberia recibir argumentos ni deberia tener mascaras
// Para saber el estado del led, usar isTurnedON() y definir si la logica es ON=1 y OFF=0 o al reves para
// saber que tiene que devolver la funcion

static uint16_t *puerto_virtual;

void setUp(void)
{
    ledsInit(&puerto_virtual);
}
// Al iniciar la biblioteta todos los leds inician apagados
void test_todos_los_leds_inicial_apagados(void)
{
    puerto_virtual = ALL_LEDS_ON;
    ledsInit(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(ALL_LEDS_OFF, puerto_virtual);
}

// Con el led 2 prendido, apago el led 2, verifico que se enciende el bit 1 vale 0
void test_prender_un_led(void)
{
    ledsTurnOnSingle(2);
    ledsTurnOffSingle(2);
    TEST_ASSERT_EQUAL_HEX16(ALL_LEDS_OFF, puerto_virtual);
}

// Con todos los leds apagados, prende el led 2, verifico que el bit 1 vale 1
void test_prender_y_apagar_un_led(void)
{
    ledsTurnOnSingle(2);
    TEST_ASSERT_EQUAL_HEX16(0x0002, puerto_virtual);
}

// Con todos los leds apagados, prende el led 3, prendo el 5,apago el 3 y apago el 7, deberian quedar el bit 4 en 1 y el resto en 0
void test_prender_y_apagar_varios_leds(void)
{
    ledsTurnOnSingle(3);
    ledsTurnOnSingle(5);
    ledsTurnOffSingle(3);
    ledsTurnOffSingle(7);
    TEST_ASSERT_EQUAL_HEX16(0x0010, puerto_virtual);
}

// Prendo un led, consulto el estado y tiene que estar prendido
void test_leer_un_led_prendido(void)
{
    ledsTurnOnSingle(3);
    TEST_ASSERT_EQUAL(1, isTurnedOn(3));
}

// Apago un led, consulto el estado y tiene que estar apagado
void test_leer_un_led_apagado(void)
{
    ledsTurnOnSingle(3);
    ledsTurnOffSingle(3);
    TEST_ASSERT_EQUAL(0, isTurnedOn(3));
}

// Enciendo todos los leds
void test_encender_todos_los_leds(void)
{
    ledsTurnOnAll();
    TEST_ASSERT_EQUAL(ALL_LEDS_ON, puerto_virtual);
}

// Apago todos los leds
void test_apagar_todos_los_leds(void)
{
    ledsTurnOnAll();
    ledsTurnOffAll();
    TEST_ASSERT_EQUAL(ALL_LEDS_OFF, puerto_virtual);
}

// paso un valor valido de led a la funcion de encender led y debe devolver 1
void test_ok_prender_led(void)
{
    TEST_ASSERT_EQUAL(1, ledsTurnOnSingle(3));
}

// paso un valor erroneo de led a la funcion de encender led y debe devolver 0
void test_error_prender_led(void)
{
    TEST_ASSERT_EQUAL(0, ledsTurnOnSingle(18));
}

// paso un valor valido de led a la funcion de encender led y debe devolver 1
void test_ok_apagar_led(void)
{
    TEST_ASSERT_EQUAL(1, ledsTurnOffSingle(3));
}

// paso un valor erroneo de led a la funcion de encender led y debe devolver 0
void test_error_apagar_led(void)
{
    TEST_ASSERT_EQUAL(0, ledsTurnOffSingle(-7));
}