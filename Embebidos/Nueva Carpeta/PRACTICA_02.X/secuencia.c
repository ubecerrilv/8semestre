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
    TRISA = 0xFF; //Puerto A en modo entrada
    TRISB = 0x00; //Puerto B en modo salida
    ANSELA = 0x00;
    while(1)
    {
        if (PORTA==0b00000000)//00000000
        {
            LATB=0x00;
            __delay_ms(500);
            LATB=0xFF;
            __delay_ms(500);
        }
        
        if (PORTA==0b00000001)//00000001
        {
            LATB=0x80;
            __delay_ms(300);
            LATB=0x40;
            __delay_ms(300);
            LATB=0x20;
            __delay_ms(300);
            LATB=0x10;
            __delay_ms(300);
            LATB=0x08;
            __delay_ms(300);
            LATB=0x04;
            __delay_ms(300);
            LATB=0x02;
            __delay_ms(300);
            LATB=0x01;
            __delay_ms(300);
        }
        
        if (PORTA==0b00000010)//00000010
        {
            LATB=0x01;
            __delay_ms(300);
            LATB=0x02;
            __delay_ms(300);
            LATB=0x04;
            __delay_ms(300);
            LATB=0x08;
            __delay_ms(300);
            LATB=0x10;
            __delay_ms(300);
            LATB=0x20;
            __delay_ms(300);
            LATB=0x40;
            __delay_ms(300);
            LATB=0x80;
            __delay_ms(300);
        }
        if (PORTA==0b00000011)//00000011
        {
            LATB=0xF0;
            __delay_ms(500);
            LATB = 0x0F;
            __delay_ms(500);
        }//FIN IFS
    }//FIN WHILE
    
    return;
}//FIN MAIN


