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
void secuencia0_1(void);
void secuencia0_2(void);
void secuencia0_3(void);
void secuencia0_4(void);
void secuencia1_1(void);
void secuencia1_2(void);
void secuencia1_3(void);
void secuencia1_4(void);
void secuencia2_1(void);
void secuencia2_2(void);
void secuencia2_3(void);
void secuencia2_4(void);
void secuencia3_1(void);
void secuencia3_2(void);
void secuencia3_3(void);
void secuencia3_4(void);

//VARIABLES
unsigned const long DELAY1=150;
unsigned const long DELAY2=250;
unsigned const long DELAY3=350;
unsigned const long DELAY4=600;

void main(void) 
{
    TRISA = 0x0F; //Puerto A en modo entrada
    ANSELA = 0x00; //Puerto A en modo de entrada digital
    
    TRISB = 0x00; //Puerto B en modo salida
    
    while(1)
    {
        //SWITCH PARA LAS SECUENCIAS
        switch (PORTA)
        {
            //SECUENCIA0
            case 0x00:
                secuencia0_1();
                break;
                
            case 0x04:
                secuencia0_2();
                break;
                
            case 0x08:
                secuencia0_3();
                break;
                
            case 0x0C:
                secuencia0_4();
                break;
            
            //SECUENCIA1
            case 0x01:
                secuencia1_1();
                break;
                
            case 0x05:
                secuencia1_2();
                break;
            
            case 0x09:
                secuencia1_3();
                break;
            
            case 0x0D:
                secuencia1_4();
                break;
                
            //SECUENCIA2
            case 0x02:
                secuencia2_1();
                break;
                
             case 0x06:
                secuencia2_2();
                break;
            
             case 0x0A:
                secuencia2_3();
                break;
                
             case 0x0E:
                secuencia2_4();
                break;
                
            //SECUENCIA 3
            case 0x03:
                secuencia3_1();
                break;
                
            case 0x07:
                secuencia3_2();
                break;
                
            case 0x0B:
                secuencia3_3();
                break;
                
            case 0x0F:
                secuencia3_4();
                break;
        }
    }//FIN WHILE
    return;
}//FIN MAIN

/*
 *  FUNCIONES DE LAS SECUENCIAS
 */
void secuencia0_1()
{
    LATB=0x00;
    __delay_ms(DELAY1);
    LATB=0xFF;
    __delay_ms(DELAY1);
}
void secuencia0_2()
{
    LATB=0x00;
    __delay_ms(DELAY2);
    LATB=0xFF;
    __delay_ms(DELAY2);
}
void secuencia0_3()
{
    LATB=0x00;
    __delay_ms(DELAY3);
    LATB=0xFF;
    __delay_ms(DELAY3);
}
void secuencia0_4()
{
    LATB=0x00;
    __delay_ms(DELAY4);
    LATB=0xFF;
    __delay_ms(DELAY4);
}









void secuencia1_1()
{
    unsigned char i =0x80;
    while(i>=0x01)
    {
        LATB=i;
        __delay_ms(DELAY1);
        i/=0x02;
    }
}
void secuencia1_2()
{
    unsigned char i =0x80;
    while(i>=0x01)
    {
        LATB=i;
        __delay_ms(DELAY2);
        i/=0x02;
    }
}
void secuencia1_3()
{
    unsigned char i =0x80;
    while(i>=0x01)
    {
        LATB=i;
        __delay_ms(DELAY3);
        i/=0x02;
    }
}
void secuencia1_4()
{
    unsigned char i =0x80;
    while(i>=0x01)
    {
        LATB=i;
        __delay_ms(DELAY4);
        i/=0x02;
    }
}






void secuencia2_1()
{
    unsigned char i =0x01;
    while(i!=0x00)
    {
        LATB=i;
        __delay_ms(DELAY1);
        i*=0x02;
    }
}
void secuencia2_2()
{
    unsigned char i =0x01;
    while(i!=0x00)
    {
        LATB=i;
        __delay_ms(DELAY2);
        i*=0x02;
    }
}
void secuencia2_3()
{
    unsigned char i =0x01;
    while(i!=0x00)
    {
        LATB=i;
        __delay_ms(DELAY3);
        i*=0x02;
    }
}
void secuencia2_4()
{
    unsigned char i =0x01;
    while(i!=0x00)
    {
        LATB=i;
        __delay_ms(DELAY4);
        i*=0x02;
    }
}








void secuencia3_1()
{
    LATB=0xF0;
    __delay_ms(DELAY1);
    LATB = 0x0F;
    __delay_ms(DELAY1);
}
void secuencia3_2()
{
    LATB=0xF0;
    __delay_ms(DELAY2);
    LATB = 0x0F;
    __delay_ms(DELAY2);
}
void secuencia3_3()
{
    LATB=0xF0;
    __delay_ms(DELAY3);
    LATB = 0x0F;
    __delay_ms(DELAY3);
}
void secuencia3_4()
{
    LATB=0xF0;
    __delay_ms(DELAY4);
    LATB = 0x0F;
    __delay_ms(DELAY4);
}