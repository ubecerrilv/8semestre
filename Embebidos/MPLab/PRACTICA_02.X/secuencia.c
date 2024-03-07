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
//FUNCIONES PROTOTIPO
void secuencia0(void);
void secuencia1(void);
void secuencia2(void);
void secuencia3(void);

void main(void) 
{
    TRISA = 0x03; //Puerto A en modo entrada
    TRISB = 0x00; //Puerto B en modo salida
    ANSELA = 0x00; //Puerto A en modo de entrada digital
    while(1)
    {
        switch (PORTA)
        {
            case 0x00:
                secuencia0();
                break;
            
            case 0x01:
                secuencia1();
                break;
                
            case 0x02:
                secuencia2();
                break;
                
            case 0x03:
                secuencia3();
                break;
        }
    }//FIN WHILE
    return;
}//FIN MAIN

/*
 *  FUNCIONES DE LAS SECUENCIAS
 */
void secuencia0()
{
    LATB=0x00;
    __delay_ms(500);
    LATB=0xFF;
    __delay_ms(500);
}

void secuencia1()
{
    unsigned char i =0x80;
    while(i>=0x01)
    {
        LATB=i;
        __delay_ms(300);
        i/=0x02;
    }
}

void secuencia2()
{
    unsigned char i =0x01;
    while(i!=0x00)
    {
        LATB=i;
        __delay_ms(300);
        i*=0x02;
    }
}

void secuencia3()
{
    LATB=0xF0;
    __delay_ms(500);
    LATB = 0x0F;
    __delay_ms(500);
}