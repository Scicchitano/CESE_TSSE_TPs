#include "unity.h"
#include "TP_Final.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define HORA_DENTRO_HORARIO_LABORAL 15
#define HORA_FUERA_HORARIO_LABORAL 3
#define sizeCmdLCD 4

uint8_t MAXIMA_LONGITUD_INTRUSOS = 20;
uint8_t MAX_TIME_OPEN_DOOR_SEG = 2;
uint8_t FICHADAS_PENDIENTES = 0;


/*Esta funcion compara dos vectores con tamano sizeCmdLCD y retorna 1 si son iguales
o 0 si no lo son. Esta funcion se hizo exclusivamente para comparar los vectores de
comando de la funcion test_write_char_display.*/
int compareVectors(uint8_t vector1[sizeCmdLCD], uint8_t vector2[sizeCmdLCD]) {
    for (int i = 0; i < sizeCmdLCD; i++) {
        if (vector1[i] != vector2[i]) {
            return 0;  
        }
    }
    return 1;  
}




/*Se setea la ultima vez que se abrio la puerta y se espera un tiempo mayor al permitido de puerta
abierta. Entonces se llama a la funcion Chech_Puerta que va a validar si se debe encender la alarma o no.
La respuesta esperada es que si se encienda la alarma porque se supero el tiempo permitido.*/

void test_disparar_alarma(void){
    time_t last_open_door; //Variable que indica la ultima vez que se abrio la puerta
    time(&last_open_door);
    sleep(MAX_TIME_OPEN_DOOR_SEG + 1);
    TEST_ASSERT_EQUAL(1,Check_Puerta(1,last_open_door));
}


/*Se setea la ultima vez que se abrio la puerta y se espera un tiempo menor al permitido de puerta
abierta. Entonces se llama a la funcion Chech_Puerta que va a validar si se debe encender la alarma o no.
La respuesta esperada es que no se encienda la alarma porque no se supero el tiempo permitido.*/
void test_no_disparar_alarma(void){
    time_t last_open_door;
    time(&last_open_door);
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



/*Como toda medicion, la medicion de los sensores IR tienen ruido y falsos disparos.
Para evitarlos, se aplica un filtro promediador que le quita ponderacion a los falsos
disparos y un filtro de 50hz porque asi lo especifica el fabricante, ya que la mayor magnitud
de ruido la tiene en ese fracuencia.

Este test envia un vector de 6 muestras a la funcion Filtro(), la cual devuelve el resultado
de la medicion final luego de pasar por los filtros*/
void test_filtro_sensores(void){
    int testNumber = 3;

    if (testNumber == 1)
    {
        float dataTest[6] = {1.21,2.25,4.34,8.84,7.97,4.47};
        TEST_ASSERT_EQUAL(5,Filtro(dataTest));
    }

    if (testNumber == 2)
    {
        float dataTest[6] = {10.34,21.89,54.85,28.54,7.97,98.47};
        TEST_ASSERT_EQUAL(59,Filtro(dataTest));
    }


    if (testNumber == 3)
    {
        float dataTest[6] = {0.21,2.25,0.34,16.07,32.76,32.29};
        TEST_ASSERT_EQUAL(12,Filtro(dataTest));
    }
}




/* En este test se toman dos vectores iguales, se los compara y se testea que sean
iguales. Luego se hace lo mismo con vectores distintos y se testea que sean distintos

La funcion a testear compara dos vectores con tamano sizeCmdLCD y retorna 1 si son iguales
o 0 si no lo son. Esta funcion se hizo exclusivamente para comparar los vectores de
comando de la funcion test_write_char_display.*/
void test_comparador_vectores(void){
    int testNumber = 2;
    if (testNumber == 1)
    {
        uint8_t vector1[sizeCmdLCD] = {109,105,29,25};
        uint8_t vector2[sizeCmdLCD] = {109,105,29,25};
        TEST_ASSERT_EQUAL(1,compareVectors(vector1,vector2));
    }else{
        if (testNumber == 2)
        {
            uint8_t vector1[sizeCmdLCD] = {109,105,29,25};
            uint8_t vector2[sizeCmdLCD] = {888,105,29,25};
            TEST_ASSERT_EQUAL(0,compareVectors(vector1,vector2));
        }
    }
}



/*La comunicacion del display LCD es por I2C. Al mismo se le envian codigos hexadecimales.
El display LCD recibe los comandos de a 4 bits, por eso cuando se quiere enviar un char, es
necesario separar el mensaje en dos partes, parte alta (upper) y parte baja (lower) y se envia 
el mensaje en dos partes, a las cuales se les aplica una mascar que indica que el enable se pone
en 1 cuando empieza el mensaje y un 0 cuando termina

Este test envia un caracter a la funcion lcd_char2cmd(), la cual escribe en un vector, los comandos
enviados. Entonces, se compara ese vector de comandos enviados, con un vector que tiene los comandos
que se sabe que tiene que enviar (segun datasheet) de acuerdo al caracter enviado*/
void test_write_char_display(void){
    int testNumber = 2;

    if (testNumber == 1)
    {
        char charTest = 'a';
        uint8_t expectedCMD[sizeCmdLCD] = {109,105,29,25};
        uint8_t trueCMD[4];
        lcd_char2cmd(charTest,trueCMD);
        

        TEST_ASSERT_EQUAL(1,compareVectors(trueCMD,expectedCMD));
    }else{
        if (testNumber == 2)
        {
            char charTest = 'g';
            uint8_t expectedCMD[sizeCmdLCD] = {109,105,125,121};
            uint8_t trueCMD[4];
            lcd_char2cmd(charTest,trueCMD);
            

            TEST_ASSERT_EQUAL(1,compareVectors(trueCMD,expectedCMD));
        }
    }
}







/*Para que las personas puedan ingresar, deben validarse con su huella digital en un reloj biometrico.
Cuando eso sucede, el reloj envia el id de la persona a traves de un protocolo de comunicacion llamado 
wiegand. El protocolo consiste en dos cables de datos que cuando uno se pone en estado alto significa un
1 logico y el otro cable representa un 0 logico. La funcion a testear receivedData, recibe los pulsos y los 
decodifica para obtener el ID de la persona.

Este test envia un caracter a la funcion receivedData() los pulsos y se verifica que el id decodificado que 
devuelve sea el esperado segun datasheet.*/
void test_read_wiegand(void){
    int testNumber = 2;

    if (testNumber == 1)
    {
        uint8_t dataTest = 0010011100001101110111111110;
        char idExpected [10] = "48010000";
        char idTest [10] = "";
        
        receivedData(&dataTest,27,idTest);
        TEST_ASSERT_EQUAL_STRING(idExpected, idTest);

    }else{
        if (testNumber == 2)
        {
            uint8_t dataTest = 0010111100001101110111100010;
            char idExpected [10] = "08020000";
            char idTest [10] = "";
            
            receivedData(&dataTest,27,idTest);
            TEST_ASSERT_EQUAL_STRING(idExpected, idTest);
        }
    }
}




