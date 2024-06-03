#include "Config.h"  // Incluye el archivo de configuración del microcontrolador
#include <xc.h>      // Incluye la biblioteca del compilador XC8
#include <stdint.h>  // Incluye la biblioteca para los tipos de datos estándar

// Definiciones y macros
#define MIN 0                 // Valor mínimo del contador
#define MAX 24                // Valor máximo del contador
#define DEC 1                 // Identificador para el display de decenas
#define UNI 0                 // Identificador para el display de unidades
#define T_DISP 20             // Tiempo de visualización de cada dígito en milisegundos
#define T_CUENTA 500          // Tiempo total de cuenta en milisegundos
#define N_ITERACIONES (T_CUENTA/T_DISP)  // Número de iteraciones por cada cuenta
#define _XTAL_FREQ 4000000UL  // Frecuencia del oscilador del microcontrolador

// Declaración de la función para mostrar el valor en el display
void MostrarCuentaDisplay(uint8_t id, uint8_t cont);

void main(void) {
    // Variables locales
    uint8_t Cont = MIN;      // Inicializa el contador en el valor mínimo
    uint8_t IdDisp = DEC;    // Inicializa con el display de decenas
    uint8_t ContDisp = N_ITERACIONES;  // Inicializa el contador de iteraciones

    // Configuración del oscilador interno del microcontrolador
    OSCCON &= ~0b01110000;   // Limpia los bits 4, 5 y 6 de OSCCON
    OSCCON |= 0b01100000;    // Configura Fosc a 4 MHz

    // Configuración de los puertos
    TRISD = 0x00;            // Configura el puerto D como salida (Display 7 segmentos)
    TRISC &= ~0b00110000;    // Configura RC5 y RC4 como salidas para habilitar displays de decenas y unidades

    while(1) {
        // Muestra el valor actual del contador en el display correspondiente
        MostrarCuentaDisplay(IdDisp, Cont);
        
        // Retardo para mantener el dígito mostrado
        __delay_ms(T_DISP);

        // Alterna entre el display de decenas y unidades
        if (IdDisp == DEC) IdDisp = UNI;
        else              IdDisp = DEC;

        // Decrementa el contador de iteraciones
        ContDisp--;
        if (ContDisp == 0) {
            ContDisp = N_ITERACIONES;  // Reinicia el contador de iteraciones

            // Incrementa el contador principal, reiniciándolo si alcanza el valor máximo
            if (Cont == MAX) Cont = MIN;
            else             Cont++;
        }
    }
}

void MostrarCuentaDisplay(uint8_t id, uint8_t cont) {
    uint8_t dig;  // Variable para almacenar el dígito a mostrar
    uint8_t D7Seg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};  // Tabla de conversión para los dígitos del display de 7 segmentos

    LATC &= ~0b00110000;  // Apaga ambos displays

    // Selecciona el dígito a mostrar según el identificador
    switch (id) {
        case DEC:
            dig = cont / 10;         // Obtiene las decenas del contador
            LATD = D7Seg[dig];       // Envía el valor del dígito al puerto D
            LATC |= 0b00100000;      // Enciende el display de decenas
            break;
        case UNI:
            dig = cont % 10;         // Obtiene las unidades del contador
            LATD = D7Seg[dig];       // Envía el valor del dígito al puerto D
            LATC |= 0b00010000;      // Enciende el display de unidades
            break;
    }
}
