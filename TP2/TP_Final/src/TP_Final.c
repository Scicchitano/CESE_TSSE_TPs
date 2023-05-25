#include "TP_Final.h"
#include <string.h>
#include <stdio.h>

#define HORA_ENTRADA 7
#define HORA_SALIDA 18
#define MAXIMA_LONGITUD_BBDD 12


extern MAX_TIME_OPEN_DOOR_SEG;

char BBDD[][MAXIMA_LONGITUD_BBDD] = {"TAG_VALIDO", "TAG_VALIDO2", "TAG_VALIDO3", "TAG_VALIDO4", "TAG_VALIDO5", "TAG_VALIDO6"};


uint8_t Check_Puerta(uint8_t state, time_t last_open_door){
	printf("Last is %s", ctime(&last_open_door));
	time_t now;
	time(&now);
	printf("Now is %s", ctime(&now));
	uint8_t disparar_alarma;
	time_t diff = now - last_open_door;
    
	printf("Difference is %ld", diff);

	if (state && ( diff >= MAX_TIME_OPEN_DOOR_SEG))
	{
   	 
    	disparar_alarma = 1;
	}else{
    	disparar_alarma = 0;
	}
	return disparar_alarma;
}






uint8_t Check_Reset_Modem(struct tm *now){
    uint8_t hours, resetModem;
    
    hours = now->tm_hour;

    printf("hora : %d",hours);
	
	if ((hours>HORA_SALIDA) || (hours<HORA_ENTRADA))
	{
   	 
    	resetModem = 1;
	}else{
    	resetModem = 0;
	}
	return resetModem;
}



uint8_t Check_TAG(char *readTAG){
    uint8_t TAGValido = 0;
	printf(readTAG);
    uint8_t longitudBBDD = sizeof(BBDD) / sizeof(BBDD[0]);
    for(int x = 0; x < longitudBBDD; x++){
        /*printf(BBDD[x]);
        printf("\n");*/
        if (strcmp(BBDD[x],readTAG) == 0)
        {
            printf(BBDD[x]);
            printf(" - if\n");
            TAGValido = 1;
            return TAGValido;
        }else{
            printf(BBDD[x]);
            printf(" - else\n");
            TAGValido = 0;
        }

    }
	return TAGValido;
}





