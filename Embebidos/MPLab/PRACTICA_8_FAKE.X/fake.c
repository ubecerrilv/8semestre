/*
 * File:   fake.c
 * Author: ubecerril
 *
 * Created on May 16, 2024, 4:45 PM
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
    
    TRISD=0x00;
    ANSELD=0X00;
    
    while(1){
        
        //0 grados
        for(int i =0; i<250; i++){
            LATD=0x02;
            __delay_us(1000);
            LATD=0x00;
            __delay_us(190000);
            
        }
        
        //60grados
        for(int i =0; i<250; i++){
            LATD=0x02;
            __delay_us(1333);
            LATD=0x00;
            __delay_us(18667);
            
        }
        
        //120grados
        for(int i =0; i<250; i++){
            LATD=0x02;
            __delay_us(1666);
            LATD=0x00;
            __delay_us(18334);
            
        }
        
        //180grados
        for(int i =0; i<250; i++){
            LATD=0x02;
            __delay_us(2000);
            LATD=0x00;
            __delay_us(18000);
            
        }
        
      //0 grados
        /*for(int i =0; i<150; i++){
            LATD=0x02;
            __delay_us(700);
            LATD=0x00;
            __delay_us(19300);
            
        }
        
        //60grados
        for(int i =0; i<150; i++){
            LATD=0x02;
            __delay_us(1326);
            LATD=0x00;
            __delay_us(18674);
            
        }
        
        //120grados
        for(int i =0; i<150; i++){
            LATD=0x02;
            __delay_us(1953);
            LATD=0x00;
            __delay_us(18047);
            
        }
        
        //180grados
        for(int i =0; i<150; i++){
            LATD=0x02;
            __delay_us(2580);
            LATD=0x00;
            __delay_us(17420);
            
        }*/
    } 
    return;
}

