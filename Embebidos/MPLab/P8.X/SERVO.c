/*
 * File:   SERVO.c
 * Author: ubecerril
 *
 * Created on May 21, 2024, 10:45 PM
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

void main(void) {
     //CONFIGURACI?N DE PUERTOS
    TRISA=0xF0;     //Control de interrupciones (Entrada B4:B7)
    ANSELA=0x00;    //Puerto B como entrada digital (B4:B7)
    
    TRISD=0x00;
    ANSELD=0X00;
 
    while(1){

      //0 grados
            __delay_us(19300);
            CCPR4L=0b00001111;
            CCP4CONbits.DC4B=0b10;
       
        
        //60grados
            __delay_us(18674);
            CCPR4L=0b00001101;
            CCP4CONbits.DC4B=0b00;
        
        
        //120grados
            __delay_us(18047);
            CCPR4L=0b00001010;
            CCP4CONbits.DC4B=0b01;
        
        
        //180grados
            __delay_us(17420);
            CCPR4L=0b00000111;
            CCP4CONbits.DC4B=0b11;
        
    } 
    return;
}
