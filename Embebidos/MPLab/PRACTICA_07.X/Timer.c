/*
 * File:   Timer.c
 * Author: ubecerril
 *
 * Created on May 6, 2024, 9:45 PM
 */
// CONFIG1H
#pragma config FOSC = HSHP        // Oscillator Selection bits (HS oscillator (HS))

// CONFIG2L
#pragma config PWRTEN = ON        // Power-up Timer Enable bit (PWRT enabled)

// CONFIG2H
#pragma config WDTEN = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))

// CONFIG3H
#pragma config MCLRE = INTMCLR  // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)
#define _XTAL_FREQ 8000000

#include <xc.h>

void main(void) {
   //Port config
    TRISA = 0x00;   //Port A0 for output
    TRISB = 0x01;   //Port B0 for input
    ANSELA = 0x00;  //Port A digital output
    ANSELB = 0x00;  //Port B digital input
    
    //Interrupt config
    INTCONbits.GIE = 1;     //General switch
    INTCONbits.INT0IE = 1;  //Enable int0
    
    //Timer config
    T0CON = 0x07;           //Prescaler 1:256
    T0CONbits.T08BIT = 0;   // 16 bit timer
    TMR0 = 0;               //Reset timer
    INTCONbits.TMR0IE = 1;  //Timer int enable
    T0CONbits.TMR0ON = 0;   //Timer switch off
    
    
    while(1){}
    return;
}

void __interrupt() isr (void){
    //Disable ints
    INTCONbits.GIE = 0;     //General switch
    
    //if int0
    if(INTCONbits.INT0IF){
        INTCONbits.INT0IE = 0;  //Disable int0
        LATA = 0x01;            //LED on
        T0CONbits.TMR0ON = 1;  // Timer0 on
        INTCONbits.INT0IF = 0; // Clean flag int0
        TMR0 = 0x85ED;               //Timer init count
        INTCONbits.INT0IE = 1;  //enable int0
    }
    //if timer is out
    if (INTCONbits.TMR0IF) {
        LATA0 = 0;             //LED off
        T0CONbits.TMR0ON = 0;  // Timer0 off
        INTCONbits.TMR0IF = 0; // Clean Timer0 off
        TMR0 = 0;               //Reset timer
    }
    
    //enable ints
    INTCONbits.GIE = 1;     //General switch
    
    
    
}