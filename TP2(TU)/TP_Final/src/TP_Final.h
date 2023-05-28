
#include <stdint.h>
#include <time.h>

uint8_t Check_Puerta(uint8_t state, time_t last_open_door);

uint8_t Check_Reset_Modem(struct tm *now);

uint8_t Check_TAG(char *readTAG);

void send(uint32_t intruso);

uint8_t send_intruso(uint32_t intrusos[]);

void add_intruso(uint32_t intrusos[], uint8_t cantidad);