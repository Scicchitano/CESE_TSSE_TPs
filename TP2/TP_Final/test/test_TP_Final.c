#include "unity.h"
#include "TP_Final.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>


uint8_t MAX_TIME_OPEN_DOOR_SEG = 2;
uint8_t FICHADAS_PENDIENTES = 0;
//La funcion que prende todos, no deberia recibir argumentos ni deberia tener mascaras
//Para saber el estado del led, usar isTurnedON() y definir si la logica es ON=1 y OFF=0 o al reves para
//saber que tiene que devolver la funcion

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


/*Se aumenta la cantidad de fichadas pendientes para habilitar el acceso.*/
/*void test_acceso_habilitado(void){
    FICHADAS_PENDIENTES = 0;
    FICHADAS_PENDIENTES++;
    //TEST_ASSERT_EQUAL(0,Check_Acceso(FICHADAS_PENDIENTES));
}*/


/*Se mantiene en cero las fichadas pendientes para denegar el acceso*/
/*void test_acceso_denegado(void){
    FICHADAS_PENDIENTES = 0;
    //TEST_ASSERT_EQUAL(0,Check_Acceso(FICHADAS_PENDIENTES));
}*/



/*Se valida si nos encontramos fuera o dentro del horario laboral para resetear el modem. En este caso se setea un horario fuera de horario laboral por lo cual se aprovecha para reiniciar el modem*/
/*void test_reset_modem(void){
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    TEST_ASSERT_EQUAL(1,Check_Reset_Modem(local));
}*/




/*Se valida si nos encontramos fuera o dentro del horario laboral para resetear el modem. En este caso se setea un horario dentro del horario laboral por lo cual no es conveniente reiniciar el modem*/
/*void test_no_reset_modem(void){
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    local->tm_hour = 1;

    TEST_ASSERT_EQUAL(0,Check_Reset_Modem(local));
}*/




/*Se setea la ultima vez que se abrio la puerta y se espera un tiempo menor al permitido de puerta
abierta. Entonces se llama a la funcion Chech_Puerta que va a validar si se debe encender la alarma o no.
La respuesta esperada es que no se encienda la alarma porque no se supero el tiempo permitido.*/
/*void test_reconexion(void){
    time_t last_open_door;
    time(&last_open_door);
    printf("Today is %s", ctime(&last_open_door));
    sleep(MAX_TIME_OPEN_DOOR_SEG - 1);
    //TEST_ASSERT_EQUAL(0,Check_Puerta(0,last_open_door));
}*/



//Check if hay mail pendientes