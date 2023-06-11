#include "TP_Final.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HORA_ENTRADA 7
#define HORA_SALIDA 18
#define MAXIMA_LONGITUD_BBDD 12
#define SHIFT_4_BITS 4
#define START_MSG_MASK 0x0D
#define END_MSG_MASK 0x09
#define CMD_MASK 0xf0
#define WD_MASK 0xF
#define BITS_IN_BYTES 8


extern MAXIMA_LONGITUD_INTRUSOS;
extern MAX_TIME_OPEN_DOOR_SEG;

char BBDD[][MAXIMA_LONGITUD_BBDD] = {"TAG_VALIDO", "TAG_VALIDO2", "TAG_VALIDO3", "TAG_VALIDO4", "TAG_VALIDO5", "TAG_VALIDO6"};


uint8_t Check_Puerta(uint8_t state, time_t last_open_door){
	time_t now;
	time(&now);
	uint8_t disparar_alarma;
	time_t diff = now - last_open_door;

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
    uint8_t longitudBBDD = sizeof(BBDD) / sizeof(BBDD[0]);
    for(int x = 0; x < longitudBBDD; x++){
        if (strcmp(BBDD[x],readTAG) == 0)
        {
            TAGValido = 1;
            return TAGValido;
        }else{
            TAGValido = 0;
        }

    }
	return TAGValido;
}


void send(uint32_t intruso){
	printf("Se envio el intruso %d \n",intruso);
}


uint8_t send_intruso(uint32_t intrusos[]){
	uint8_t cantidad = 0;
	for (uint8_t i = 0; i < MAXIMA_LONGITUD_INTRUSOS; i++)
	{
		if (intrusos[i])
		{
			send(intrusos[i]);
			intrusos[i] = 0;
			cantidad++;
		}else{
			break;
		}
		
	}
	return cantidad;
	
}


void add_intruso(uint32_t intrusos[], uint8_t cantidad){
	if (cantidad > MAXIMA_LONGITUD_INTRUSOS)
	{
		cantidad = MAXIMA_LONGITUD_INTRUSOS;
	}
	
	for(int x = 0; x < cantidad; x++){
        intrusos[x] = time(NULL);
    }


}






/*Esta funcion recibe un vector de mediciones y le aplica 
un filtro notch de 50hz (b1) y un filtro promediador (b2).

Devulve el resultado de las mediciones con el filtro aplicado.*/
int Filtro(float data[6]){
	float b[]={1.0000,-1.6180,1.0000,1.0000,-1.6130,0.9937}; //Filtro 50hz
	float b2[]={0.167,0.167,0.167,0.167,0.167,0.167};// filtro promediador
	int M=6;
	float y=0;
	float y2=0;
	float x;

	for (int i = 0; i <= M-1; i++) {
		x=*(data+i);
		y=y+x*b[i];
	}


	for (int i = 0; i < M-1; i++) {
		data[i]=data[i+1];
	}
	data[M-1]=y;
	for (int i = 0; i <= M-1; i++) {
			x=*(data+i);
			y2=y2+x*b2[i];
	}
	return y2;
}



/*La comunicacion del display LCD es por I2C. Al mismo se le envian codigos hexadecimales.
El display LCD recibe los comandos de a 4 bits, por eso cuando se quiere enviar un char, es
necesario separar el mensaje en dos partes, parte alta (upper) y parte baja (lower) y se envia 
el mensaje en dos partes, a las cuales se les aplica una mascar que indica que el enable se pone
en 1 cuando empieza el mensaje y un 0 cuando termina*/
void lcd_char2cmd (char data, uint8_t data_t[4])
{
	char data_u, data_l;
	data_u = (data&CMD_MASK); //se aplica mascara a primeros 4 bits de data
	data_l = ((data<<SHIFT_4_BITS)&CMD_MASK); //se desplazan los ultimos 4 bits y se aplica la misma mascara
	data_t[0] = data_u|START_MSG_MASK;  //en=1, rs=0
	data_t[1] = data_u|END_MSG_MASK;  //en=0, rs=0
	data_t[2] = data_l|START_MSG_MASK;  //en=1, rs=0
	data_t[3] = data_l|END_MSG_MASK;  //en=0, rs=0
}








void hexToString(int data, char hexString[]){
  switch(data){
            case 0:
              strcat(hexString,"0");
              break;
            case 1:
              strcat(hexString,"1");
              break;
            case 2:
              strcat(hexString,"2");
              break;
            case 3:
              strcat(hexString,"3");
              break;
            case 4:
              strcat(hexString,"4");
              break;
            case 5:
              strcat(hexString,"5");
              break;
            case 6:
              strcat(hexString,"6");
              break;
            case 7:
              strcat(hexString,"7");
              break;
            case 8:
              strcat(hexString,"8");
              break;
            case 9:
              strcat(hexString,"9");
              break;
            case 10:
              strcat(hexString,"A");
              break;
            case 11:
              strcat(hexString,"B");
              break;
            case 12:
              strcat(hexString,"C");
              break;
            case 13:
              strcat(hexString,"D");
              break;
            case 14:
              strcat(hexString,"E");
              break;
            case 15:
              strcat(hexString,"F");
              break;
         
        }
}







/*Para que las personas puedan ingresar, deben validarse con su huella digital en un reloj biometrico.
Cuando eso sucede, el reloj envia el id de la persona a traves de un protocolo de comunicacion llamado 
wiegand. El protocolo consiste en dos cables de datos que cuando uno se pone en estado alto significa un
1 logico y el otro cable representa un 0 logico. La funcion a testear receivedData, recibe los pulsos y los 
decodifica para obtener el ID de la persona.*/
void receivedData(uint8_t* data, uint8_t bits,char hexString[16]) {
   
    //de bits a bytes
    uint8_t bytes = (bits+BITS_IN_BYTES)/BITS_IN_BYTES;
    
    for (int i=0; i<bytes; i++) {
        hexToString(data[i] >> SHIFT_4_BITS, hexString);
        hexToString(data[i] & WD_MASK, hexString);      
    }
}


