/*
 * File:   Led_blink.c
 * Author: ubecerril
 *
 * Created on 20 de febrero de 2024, 07:23 PM
 */

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))

// CONFIG3H
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

#include <xc.h>
#define _XTAL_FREQ 8000000

void main(void) 
{
    TRISA=0x00; //Puerto A en modo salida
    while(1)
    {
        LATA=0x00;
        __delay_ms(500);
        LATA = 0x01;
        __delay_ms(500);
    }//FIN WHILE
    
    return;
}//FIN MAIN
