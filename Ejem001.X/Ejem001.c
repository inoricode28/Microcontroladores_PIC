#include "Config.h"
#include <xc.h>
#include <stdint.h> //uint8_t, int8_t,uint16_t,...


void main( void ){
    uint8_t SWs;

    TRISD = 0x0F;
    
    while(1){
        SWs = PORTD;
        SWs = SWs <<4;
        SWs = SWs ^ 0b01010000;
        LATD = SWs;
    }

}