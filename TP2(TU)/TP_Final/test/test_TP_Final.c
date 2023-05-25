#include "unity.h"
#include "TP_Final.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define HORA_DENTRO_HORARIO_LABORAL 15
#define HORA_FUERA_HORARIO_LABORAL 3

uint8_t MAXIMA_LONGITUD_INTRUSOS = 20;
uint8_t MAX_TIME_OPEN_DOOR_SEG = 2;
uint8_t FICHADAS_PENDIENTES = 0;

/*Se setea la ultima vez que se abrio la puerta y se espera un tiempo mayor al permitido de puerta
abierta. Entonces se llama a la funcion Chech_Puerta que va a validar si se debe encender la alarma o no.
La respuesta esperada es que si se encienda la alarma porque se supero el tiempo permitido.*/

void test_disparar_alarma(void){
    time_t last_open_door; //Variable que indica la ultima vez que se abrio la puerta
    time(&last_open_door);
    printf("Today is %s", ctime(&last_open_door));
    sleep(MAX_TIME_OPEN_DOOR_SEG + 1);
    TEST_ASSERT_EQUAL(1,Check_Puerta(1,last_open_door));
}


/*Se setea la ultima vez que se abrio la puerta y se espera un tiempo menor al permitido de puerta
abierta. Entonces se llama a la funcion Chech_Puerta que va a validar si se debe encender la alarma o no.
La respuesta esperada es que no se encienda la alarma porque no se supero el tiempo permitido.*/
void test_no_disparar_alarma(void){
    time_t last_open_door;
    time(&last_open_door);
    printf("Today is %s", ctime(&last_open_door));
    sleep(MAX_TIME_OPEN_DOOR_SEG - 1);
    TEST_ASSERT_EQUAL(0,Check_Puerta(0,last_open_door));
}




/*Se setea un valor invalido de TAG. Entonces se llama a la funcion Check_TAG que va a validar si el TAG leido esta habilitado para salir. La respuesta esperada es que no este habilitado.*/
void test_TAG_valido(void){
    char readTAG[11] = "TAG_INVALIDO";
    TEST_ASSERT_EQUAL(0,Check_TAG(readTAG));
}


/*Se setea un valor invalido de TAG. Entonces se llama a la funcion Check_TAG que va a validar si el TAG leido esta habilitado para salir. La respuesta esperada es que no este habilitado.*/
void test_TAG_invalido(void){
    char readTAG[11] = "TAG_VALIDO2";
    TEST_ASSERT_EQUAL(1,Check_TAG(&readTAG));
}



/*Se valida si nos encontramos fuera o dentro del horario laboral para resetear el modem. En este caso se setea un horario fuera de horario laboral por lo cual se aprovecha para reiniciar el modem*/
void test_reset_modem(void){
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    local->tm_hour = HORA_FUERA_HORARIO_LABORAL;

    TEST_ASSERT_EQUAL(1,Check_Reset_Modem(local));
}




/*Se valida si nos encontramos fuera o dentro del horario laboral para resetear el modem. En este caso se setea un horario dentro del horario laboral por lo cual no es conveniente reiniciar el modem*/
void test_no_reset_modem(void){
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    local->tm_hour = HORA_DENTRO_HORARIO_LABORAL;

    TEST_ASSERT_EQUAL(0,Check_Reset_Modem(local));
}


/*Cada nodo reporta los intrusos al servidor. Para esto es necesrio tener conexion a internet. Es por esto que es necesario guardar el horario en el que se detectan los intrusos. El horario se guarda en el formato timestamp que consiste en contar la cantidad de segundos desde una determinada fecha. La funcion send_intrusos envia los horarios de intrusos detectados que estan guardados en vector_intrusos y lo resetea.*/
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

    TEST_ASSERT_EQUAL(3,cantidad);
}



/*Cada nodo reporta los intrusos al servidor. Para esto es necesrio tener conexion a internet. Es por esto que es necesario guardar el horario en el que se detectan los intrusos. El horario se guarda en el formato timestamp que consiste en contar la cantidad de segundos desde una determinada fecha.*/
void test_agregar_intruso_pendiente(void){
    uint8_t cantidad_intrusos_llamados = 5;
    uint8_t cantidad = 0;
    uint32_t vector_intrusos[MAXIMA_LONGITUD_INTRUSOS];
    for (uint8_t i = 0; i < MAXIMA_LONGITUD_INTRUSOS; i++){
        vector_intrusos[i] = 0;
    }
    add_intruso(vector_intrusos,cantidad_intrusos_llamados);

    cantidad = send_intruso(vector_intrusos);

    TEST_ASSERT_EQUAL(cantidad_intrusos_llamados,cantidad);
}



