#include "Config.h"
#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000UL  // Frecuencia del oscilador (4 MHz)
#define LED_PIN LATBbits.LATB0  // Definir el pin del LED

void main(void) {
    // Configurar el oscilador
    OSCCON &= ~0b01110000; // Limpiar los bits del oscilador
    OSCCON |= 0b01100000;  // Fosc = 4MHz

    // Configurar el pin RB0 como salida
    TRISBbits.TRISB0 = 0;  // Configurar RB0 como salida
    LED_PIN = 0;           // Inicialmente apagar el LED

    while(1) {
        LED_PIN = !LED_PIN;  // Alternar el estado del LED
        __delay_ms(500);     // Retardo de 500 ms
    }
}