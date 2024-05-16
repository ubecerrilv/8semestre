/*
 * File:   pwm.c
 * Author: ubecerril
 *
 * Created on May 15, 2024, 12:58 PM
 */

#pragma config FOSC = INTIO67    // Oscilador interno
#pragma config PLLCFG = OFF     // Oscilador PLL deshabilitado
#pragma config PRICLKEN = OFF   // Reiniciar el reloj primario

#pragma config PWRTEN = ON      // Power-up Timer Enable bit (Power up timer enabled)
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config MCLRE = INTMCLR  // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

#define _XTAL_FREQ 500000
#include <xc.h>

//FUNCIONES PROTOTIPO

void main(void) 
{
    OSCCONbits.IRCF = 0b010;
    //CONFIGURACI?N DE PUERTOS
    TRISB=0xF0;     //Control de interrupciones (Entrada B4:B7)
    ANSELB=0x00;    //Puerto B como entrada digital (B4:B7)
    TRISA=0x00;
    ANSELA=0x00;
    
      
    //CONFIGURACI?N DE INTERRUPCIONES
    INTCON=0x88;    //Interrupciones en general
    IOCB=0xF0;      //habilita los pines del puerto B<4:7> para usarse en la interrupci?n del puerto B
    
   //CONFIGURACI?N DEL PWM
    //PR4=0xF9;        //Periodo de PWM
    PR4=0x9C ;        //Periodo de PWM
    //Inicialmente 0 grados
    //CCPR4L = 0x0F; // Configurar ciclo de trabajo para 0 grados
    /*CCPR4L=0b00001100;
    CCP4CONbits.DC4B=0b10;*/
    CCPR4L=0b00001111;
    CCP4CONbits.DC4B=0b10;
    
    TRISDbits.TRISD1=0;     //Pin 1 del puerto D como salida
    //ANSELD=0x00;           //Puerto D como salida digital
    
    CCPTMRS1bits.C4TSEL=0b00; //Setear el timer2
    T2CONbits.T2CKPS = 0b10; // Prescaler de 16 para el temporizador 2
    T2CONbits.TMR2ON = 1; // Encender el temporizador 2
    CCP4CONbits.CCP4M=0b1100;   //Modo PWM
    
    
    
    
   
    while(1)
    {
    }
       
    return;
}

void __interrupt () isr_general () {
    //INTCONbits.RBIE=0;
    
   __delay_ms(200);
        unsigned char actual = PORTB;
        switch (actual){
            case 0x80://180
                /*CCPR4L=0b00001100;
                CCP4CONbits.DC4B=0b10;*/
                CCPR4L=0b00000111;
                CCP4CONbits.DC4B=0b11;
                
                LATA=0b00001000;
                break;
            
            case 0x40://120
               /*CCPR4L=0b00010000;
               CCP4CONbits.DC4B=0b10;*/
               CCPR4L=0b00001010;
               CCP4CONbits.DC4B=0b01;
                LATA=0b00000100;
                break;
                
            case 0x20://60
               /*CCPR4L=0b00010100;
               CCP4CONbits.DC4B=0b11;*/
               CCPR4L=0b00001101;
               CCP4CONbits.DC4B=0b00;
                LATA=0b00000010;
                break;
                
            case 0x10://0
              /*CCPR4L=0b00011001;
               CCP4CONbits.DC4B=0b00;*/
                CCPR4L=0b00001111;
                CCP4CONbits.DC4B=0b10;
                LATA=0b00000001;
                break;
        }
        __delay_ms(3000);
  
    __delay_ms(100);
    INTCONbits.RBIF=0;
    INTCONbits.RBIE=1;
   }