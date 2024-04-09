/*
 * File:   newmain.c
 * Author: ubecerril
 *
 * Created on 8 de abril de 2024, 02:21 PM
 */
// CONFIG1H
#pragma config FOSC = HSHP        // Oscillator Selection bits (HS oscillator (HS))

// CONFIG2L
#pragma config PWRTEN = ON        // Power-up Timer Enable bit (PWRT enabled)

// CONFIG2H
#pragma config WDTEN = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))

// CONFIG3H
#pragma config MCLRE = INTMCLR  // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

//CONFIG4L
#pragma config LVP = OFF

#include <xc.h>

int static contador;

void main(void) {
    //CONFIGURACIÓN DE PUERTOS
    TRISD = 0x00;
    TRISB = 0x01;
    ANSELBbits.ANSB0=0;
    
    //CONFIGURACIÓN DE INTERRUPCIONES
    INTCONbits.INT0E=1;     //Habilita la interrupción0
    INTCONTbits.INT0F=0;    //No ha ocurrido la interrupción
    
    INTCONT2bits.INTEDG0=0; //Flanco de bajada
    INTCONbits.GIE=1;       //Habilitador global
    
    while(1){}
    return;
}

void __interrupt (void) isr_general()
{
    INTCONbits.INTOE=0;
    INTCONTbits.INT0F=0;
    
    contador++;
    
    LATD=contador;
    INTCONbits.INTOE=0;
}