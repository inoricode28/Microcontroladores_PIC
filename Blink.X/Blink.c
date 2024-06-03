#include "Config.h"   // Incluir archivo de configuración específico del microcontrolador
#include <xc.h>       // Incluir archivo de definiciones para el microcontrolador PIC
#include <stdint.h>   // Incluir archivo de definiciones para tipos de datos enteros

#define _XTAL_FREQ 4000000UL  // Frecuencia del oscilador (4 MHz)
#define LED_PIN LATDbits.LATB0  // Definir el pin del LED como LATB0

void main(void) {
    // Configurar el oscilador
    OSCCON &= ~0b01110000; // Limpiar los bits del oscilador
    OSCCON |= 0b01100000;  // Establecer Fosc = 4MHz

    // Configurar el pin RB0 como salida
    TRISDbits.TRISD0 = 0;  // Configurar RD0 como salida
    LATDbits.LATD0=0;      // Inicialmente apagar el LED

    while(1) {
        LATDbits.LATD0=1;   // Encender el LED
        __delay_ms(500);    // Retardo de 500 ms
        LATDbits.LATD0=0;   // Apagar el LED
        __delay_ms(500);    // Retardo de 500 ms       
    }
}
