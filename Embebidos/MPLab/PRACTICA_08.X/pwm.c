/*
 * File:   pwm.c
 * Author: ubecerril
 *
 * Created on May 15, 2024, 12:58 PM
 */

#pragma config FOSC = HSHP       // Oscillator Selection bits (XT oscillator)
#pragma config PWRTEN = ON      // Power-up Timer Enable bit (Power up timer enabled)
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config MCLRE = INTMCLR  // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

#define _XTAL_FREQ 8000000
#include <xc.h>

//FUNCIONES PROTOTIPO

void main(void) 
{
    //CONFIGURACIÓN DE PUERTOS
    TRISB=0xF0;     //Control de interrupciones (Entrada B4:B7)
    ANSELB=0x0F;    //Puerto B como entrada digital (B4:B7)
    TRISDbits.TRISD1=0;     //Pin 1 del puerto D como salida
    ANSELD=0x00;           //Puerto D como salida digital
      
    //CONFIGURACIÓN DE INTERRUPCIONES
    INTCON=0x88;    //Interrupciones en general
    IOCB=0xF0;      //habilita los pines del puerto B<4:7> para usarse en la interrupción del puerto B
    
    //CONFIGURACIÓN DEL PWM
    PR4=249;        //Periodo de PWM
    //Inicialmente 0 grados
    CCPR4L=0b00011001;
    CCP4CONbits.DC4B=0b00;
    
    T4CONbits.T4CKPS = 0b10; // Prescaler de 16 para el temporizador 4
    T4CONbits.TMR4ON = 1; // Encender el temporizador 4
    CCP4CONbits.CCP4M=0b1100;   //Modo PWM
    
    
    
    
   
    while(1)
    {
    }
       
    return;
}

void __interrupt () isr_general () 
{
    //INTCONbits.RBIE=0;
    
    __delay_ms(200);
        unsigned char actual = PORTB;
        switch (actual){
            case 0x80://180
                CCPR4L=0b00001100;
                CCP4CONbits.DC4B=0b10;
                __delay_ms(2000);
                break;
            
            case 0x40://120
                CCPR4L=0b00010000;
                CCP4CONbits.DC4B=0b10;
                __delay_ms(2000);
                break;
                
            case 0x20://60
                CCPR4L=0b00010100;
                CCP4CONbits.DC4B=0b11;
                __delay_ms(2000);
                break;
                
            case 0x10://0
                CCPR4L=0b00011001;
                CCP4CONbits.DC4B=0b00;
                __delay_ms(2000);
                break;
        }
  
    __delay_ms(100);
    INTCONbits.RBIF=0;
    //INTCONbits.RBIE=1;
   }