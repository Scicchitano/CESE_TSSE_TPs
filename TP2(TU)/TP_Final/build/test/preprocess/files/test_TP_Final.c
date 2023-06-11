#include "src/TP_Final.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"














uint8_t MAXIMA_LONGITUD_INTRUSOS = 20;

uint8_t MAX_TIME_OPEN_DOOR_SEG = 2;

uint8_t FICHADAS_PENDIENTES = 0;











int compareVectors(uint8_t vector1[4], uint8_t vector2[4]) {

    for (int i = 0; i < 4; i++) {

        if (vector1[i] != vector2[i]) {

            return 0;

        }

    }

    return 1;

}

void test_disparar_alarma(void){

    time_t last_open_door;

    time(&last_open_door);

    sleep(MAX_TIME_OPEN_DOOR_SEG + 1);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Check_Puerta(1,last_open_door))), (

   ((void *)0)

   ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);

}











void test_no_disparar_alarma(void){

    time_t last_open_door;

    time(&last_open_door);

    sleep(MAX_TIME_OPEN_DOOR_SEG - 1);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Check_Puerta(0,last_open_door))), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_INT);

}











void test_TAG_valido(void){

    char readTAG[11] = "TAG_INVALIDO";

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Check_TAG(readTAG))), (

   ((void *)0)

   ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_INT);

}







void test_TAG_invalido(void){

    char readTAG[11] = "TAG_VALIDO2";

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Check_TAG(&readTAG))), (

   ((void *)0)

   ), (UNITY_UINT)(66), UNITY_DISPLAY_STYLE_INT);

}









void test_reset_modem(void){

    time_t now;

    time(&now);

    struct tm *local = localtime(&now);

    local->tm_hour = 3;



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Check_Reset_Modem(local))), (

   ((void *)0)

   ), (UNITY_UINT)(78), UNITY_DISPLAY_STYLE_INT);

}











void test_no_reset_modem(void){

    time_t now;

    time(&now);

    struct tm *local = localtime(&now);

    local->tm_hour = 15;



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Check_Reset_Modem(local))), (

   ((void *)0)

   ), (UNITY_UINT)(91), UNITY_DISPLAY_STYLE_INT);

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

   ), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_INT);

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

   ), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_INT);

}

void test_filtro_sensores(void){

    int testNumber = 3;



    if (testNumber == 1)

    {

        float dataTest[6] = {1.21,2.25,4.34,8.84,7.97,4.47};

        UnityAssertEqualNumber((UNITY_INT)((5)), (UNITY_INT)((Filtro(dataTest))), (

       ((void *)0)

       ), (UNITY_UINT)(144), UNITY_DISPLAY_STYLE_INT);

    }



    if (testNumber == 2)

    {

        float dataTest[6] = {10.34,21.89,54.85,28.54,7.97,98.47};

        UnityAssertEqualNumber((UNITY_INT)((59)), (UNITY_INT)((Filtro(dataTest))), (

       ((void *)0)

       ), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_INT);

    }





    if (testNumber == 3)

    {

        float dataTest[6] = {0.21,2.25,0.34,16.07,32.76,32.29};

        UnityAssertEqualNumber((UNITY_INT)((12)), (UNITY_INT)((Filtro(dataTest))), (

       ((void *)0)

       ), (UNITY_UINT)(157), UNITY_DISPLAY_STYLE_INT);

    }

}

void test_comparador_vectores(void){

    int testNumber = 2;

    if (testNumber == 1)

    {

        uint8_t vector1[4] = {109,105,29,25};

        uint8_t vector2[4] = {109,105,29,25};

        UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((compareVectors(vector1,vector2))), (

       ((void *)0)

       ), (UNITY_UINT)(176), UNITY_DISPLAY_STYLE_INT);

    }else{

        if (testNumber == 2)

        {

            uint8_t vector1[4] = {109,105,29,25};

            uint8_t vector2[4] = {888,105,29,25};

            UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((compareVectors(vector1,vector2))), (

           ((void *)0)

           ), (UNITY_UINT)(182), UNITY_DISPLAY_STYLE_INT);

        }

    }

}

void test_write_char_display(void){

    int testNumber = 2;



    if (testNumber == 1)

    {

        char charTest = 'a';

        uint8_t expectedCMD[4] = {109,105,29,25};

        uint8_t trueCMD[4];

        lcd_char2cmd(charTest,trueCMD);





        UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((compareVectors(trueCMD,expectedCMD))), (

       ((void *)0)

       ), (UNITY_UINT)(209), UNITY_DISPLAY_STYLE_INT);

    }else{

        if (testNumber == 2)

        {

            char charTest = 'g';

            uint8_t expectedCMD[4] = {109,105,125,121};

            uint8_t trueCMD[4];

            lcd_char2cmd(charTest,trueCMD);





            UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((compareVectors(trueCMD,expectedCMD))), (

           ((void *)0)

           ), (UNITY_UINT)(219), UNITY_DISPLAY_STYLE_INT);

        }

    }

}

void test_read_wiegand(void){

    int testNumber = 2;



    if (testNumber == 1)

    {

        uint8_t dataTest = 0010011100001101110111111110;

        char idExpected [10] = "48010000";

        char idTest [10] = "";



        receivedData(&dataTest,27,idTest);

        UnityAssertEqualString((const char*)((idExpected)), (const char*)((idTest)), (

       ((void *)0)

       ), (UNITY_UINT)(248));



    }else{

        if (testNumber == 2)

        {

            uint8_t dataTest = 0010111100001101110111100010;

            char idExpected [10] = "08020000";

            char idTest [10] = "";



            receivedData(&dataTest,27,idTest);

            UnityAssertEqualString((const char*)((idExpected)), (const char*)((idTest)), (

           ((void *)0)

           ), (UNITY_UINT)(258));

        }

    }

}
