#include "src/leds.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
static uint16_t *puerto_virtual;



void setUp(void)

{

    ledsInit(&puerto_virtual);

}



void test_todos_los_leds_inicial_apagados(void)

{

    puerto_virtual = 0xFFFF;

    ledsInit(&puerto_virtual);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_un_led(void)

{

    ledsTurnOnSingle(2);

    ledsTurnOffSingle(2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_y_apagar_un_led(void)

{

    ledsTurnOnSingle(2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0002)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_y_apagar_varios_leds(void)

{

    ledsTurnOnSingle(3);

    ledsTurnOnSingle(5);

    ledsTurnOffSingle(3);

    ledsTurnOffSingle(7);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0010)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_HEX16);

}





void test_leer_un_led_prendido(void)

{

    ledsTurnOnSingle(3);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((isTurnedOn(3))), (

   ((void *)0)

   ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_INT);

}





void test_leer_un_led_apagado(void)

{

    ledsTurnOnSingle(3);

    ledsTurnOffSingle(3);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((isTurnedOn(3))), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_INT);

}





void test_encender_todos_los_leds(void)

{

    ledsTurnOnAll();

    UnityAssertEqualNumber((UNITY_INT)((0xFFFF)), (UNITY_INT)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_INT);

}





void test_apagar_todos_los_leds(void)

{

    ledsTurnOnAll();

    ledsTurnOffAll();

    UnityAssertEqualNumber((UNITY_INT)((0x0000)), (UNITY_INT)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(78), UNITY_DISPLAY_STYLE_INT);

}





void test_ok_prender_led(void)

{

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((ledsTurnOnSingle(3))), (

   ((void *)0)

   ), (UNITY_UINT)(84), UNITY_DISPLAY_STYLE_INT);

}





void test_error_prender_led(void)

{

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((ledsTurnOnSingle(18))), (

   ((void *)0)

   ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_INT);

}





void test_ok_apagar_led(void)

{

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((ledsTurnOffSingle(3))), (

   ((void *)0)

   ), (UNITY_UINT)(96), UNITY_DISPLAY_STYLE_INT);

}





void test_error_apagar_led(void)

{

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((ledsTurnOffSingle(-7))), (

   ((void *)0)

   ), (UNITY_UINT)(102), UNITY_DISPLAY_STYLE_INT);

}
