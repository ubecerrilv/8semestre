/*
 * File:   Secuencia.c
 * Author: ubecerril
 *
 * Created on 28 de febrero de 2024, 07:23 PM
 */

// CONFIG1H
#pragma config FOSC = HSHP        // Oscillator Selection bits (HS oscillator (HS))

// CONFIG2L
#pragma config PWRTEN = ON        // Power-up Timer Enable bit (PWRT enabled)

// CONFIG2H
#pragma config WDTEN = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))

// CONFIG3H
#pragma config MCLRE = INTMCLR  // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

#include <xc.h>
#define _XTAL_FREQ 8000000

void main(void) 
{
    TRISA=0x01; //Puerto A en modo entrada
    TRISD = 0x00; //Puerto D en modo salida
    while(1)
    {
        if (PORTA==0x00)//00000000
        {
            LATA=0xFF;
            __delay_ms(500);
            LATA=0x00;
            __delay_ms(500);
        }else if (PORTA==0x01)//00000001
        {
            LATA=0x80;
            __delay_ms(300);
            LATA=0x40;
            __delay_ms(300);
            LATA=0x20;
            __delay_ms(300);
            LATA=0x10;
            __delay_ms(300);
            LATA=0x08;
            __delay_ms(300);
            LATA=0x04;
            __delay_ms(300);
            LATA=0x02;
            __delay_ms(300);
            LATA=0x01;
            __delay_ms(300);
        }else if (PORTA==0x02)//00000010
        {
            LATA=0x01;
            __delay_ms(300);
            LATA=0x02;
            __delay_ms(300);
            LATA=0x04;
            __delay_ms(300);
            LATA=0x08;
            __delay_ms(300);
            LATA=0x10;
            __delay_ms(300);
            LATA=0x20;
            __delay_ms(300);
            LATA=0x40;
            __delay_ms(300);
            LATA=0x80;
            __delay_ms(300);
        }else if (PORTA==0x03)//00000011
        {
            LATA=0xF0;
            __delay_ms(500);
            LATA = 0x0F;
            __delay_ms(500);
        }//FIN IFS
    }//FIN WHILE
    
    return;
}//FIN MAIN

