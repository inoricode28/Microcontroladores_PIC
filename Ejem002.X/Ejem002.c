#include "Config.h"
#include <xc.h>
#include <stdint.h> // Tipos de datos como uint8_t, int8_t, uint16_t, ...

#define MIN 0          // Valor mínimo del contador
#define MAX 255        // Valor máximo del contador
#define _XTAL_FREQ 1000000UL // Frecuencia del oscilador del microcontrolador (1 MHz)

void main(void) {
    uint8_t Cont = MIN; // Inicializa el contador en el valor mínimo

    TRISD = 0x00; // Configura el puerto D como salida (todos los pines del puerto D son salidas)

    while(1) { // Bucle infinito
        LATD = Cont; // Asigna el valor del contador al puerto D
        __delay_ms(100); // Espera 100 milisegundos

        if (Cont == MAX) { // Si el contador alcanza el valor máximo
            Cont = MIN;    // Reinicia el contador al valor mínimo
        } else {
            Cont++;        // Incrementa el contador
        }
    }
}
