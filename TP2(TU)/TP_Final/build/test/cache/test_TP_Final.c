#include "src/TP_Final.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"












uint8_t MAXIMA_LONGITUD_INTRUSOS = 20;

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









void test_reset_modem(void){

    time_t now;

    time(&now);

    struct tm *local = localtime(&now);

    local->tm_hour = 3;



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Check_Reset_Modem(local))), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_INT);

}











void test_no_reset_modem(void){

    time_t now;

    time(&now);

    struct tm *local = localtime(&now);

    local->tm_hour = 15;



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Check_Reset_Modem(local))), (

   ((void *)0)

   ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_INT);

}







void test_contar_intruso_pendiente(void){

    uint8_t cantidad = 0;

    uint32_t vector_intrusos[MAXIMA_LONGITUD_INTRUSOS];

    for (uint8_t i = 0; i < MAXIMA_LONGITUD_INTRUSOS; i++){

        vector_intrusos[i] = 0;

    }



    vector_intrusos[0] = 84;

    vector_intrusos[1] = 184;

    vector_intrusos[2] = 744;



    cantidad = send_intruso(vector_intrusos);



    UnityAssertEqualNumber((UNITY_INT)((3)), (UNITY_INT)((cantidad)), (

   ((void *)0)

   ), (UNITY_UINT)(94), UNITY_DISPLAY_STYLE_INT);

}









void test_agregar_intruso_pendiente(void){

    uint8_t cantidad_intrusos_llamados = 5;

    uint8_t cantidad = 0;

    uint32_t vector_intrusos[MAXIMA_LONGITUD_INTRUSOS];

    for (uint8_t i = 0; i < MAXIMA_LONGITUD_INTRUSOS; i++){

        vector_intrusos[i] = 0;

    }

    add_intruso(vector_intrusos,cantidad_intrusos_llamados);



    cantidad = send_intruso(vector_intrusos);



    UnityAssertEqualNumber((UNITY_INT)((cantidad_intrusos_llamados)), (UNITY_INT)((cantidad)), (

   ((void *)0)

   ), (UNITY_UINT)(111), UNITY_DISPLAY_STYLE_INT);

}
