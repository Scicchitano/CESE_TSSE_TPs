#include "src/TP_Final.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








uint8_t MAX_TIME_OPEN_DOOR_SEG = 2;

uint8_t FICHADAS_PENDIENTES = 0;

void test_disparar_alarma(void){

    time_t last_open_door;

    time(&last_open_door);

    printf("Today is %s", ctime(&last_open_door));

    sleep(MAX_TIME_OPEN_DOOR_SEG + 1);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Check_Puerta(1,last_open_door))), (

   ((void *)0)

   ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_INT);

}











void test_no_disparar_alarma(void){

    time_t last_open_door;

    time(&last_open_door);

    printf("Today is %s", ctime(&last_open_door));

    sleep(MAX_TIME_OPEN_DOOR_SEG - 1);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Check_Puerta(0,last_open_door))), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT);

}











void test_TAG_valido(void){

    char readTAG[11] = "TAG_INVALIDO";

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Check_TAG(readTAG))), (

   ((void *)0)

   ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT);

}







void test_TAG_invalido(void){

    char readTAG[11] = "TAG_VALIDO2";

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Check_TAG(&readTAG))), (

   ((void *)0)

   ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);

}
