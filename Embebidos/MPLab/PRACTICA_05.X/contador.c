/*
 * File:   contador.c
 * Author: ubecerril
 *
 * Created on April 15, 2024, 1:22 PM
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
#define _XTAL_FREQ 8000000

//VARIABLES PARA LOS NUMEROS
unsigned char CERO = 0x3F;
unsigned char UNO = 0x06;
unsigned char DOS = 0x5B;
unsigned char TRES= 0x4F;
unsigned char CUATRO = 0x66;
unsigned char CINCO = 0x6D;
unsigned char SEIS = 0x7D;
unsigned char SIETE = 0x07;
unsigned char OCHO = 0x7F;
unsigned char NUEVE = 0x6F;
//VARIABLES PARA LOS DISPLAY
unsigned char D3 = 0x7F;
unsigned char D2 = 0xBF;
unsigned char D1 = 0xDF;
unsigned char D0 = 0xEF;

//Prototipos
void display0 (void);
void display1 (void);

int static contador, decenas, unidades;

void main(void) {
    //CONFIGURACIÓN DE PUERTOS
    TRISD = 0x00;
    TRISB = 0x01;//PIN0 EN ENTRADA
    TRISC = 0X0F;
    ANSELB = 0x00;
    
    //CONFIGURACIÓN DE INTERRUPCIONES
    INTCONbits.INT0E=1;     //Habilita la interrupción0
    INTCONbits.INT0F=0;    //No ha ocurrido la interrupción
    
    INTCON2bits.INTEDG0=0; //Flanco de bajada
    INTCONbits.GIE=1;       //Habilitador global
    
    while(1){
        display0();
        
        display1();
    }
    return;
}

void __interrupt () isr_general()
{
    INTCONbits.INT0E=0;
    INTCONbits.INT0F=0;
    if (contador==95) contador =0;
    else contador+=5;
    
    unidades = contador%10;
    decenas = contador/10;
    __delay_ms(200);
    
    INTCONbits.INT0E=1;
}

void display0 ()
{
    LATC = D0;
    switch (unidades)
    {
        case 0:
            LATD=CERO;
        break;
        
        case 1:
            LATD=UNO;
        break;
        
        case 2:
            LATD=DOS;
        break;
        
        case 3:
            LATD=TRES;
        break;
        
        case 4:
            LATD=CUATRO;
        break;
        
        case 5:
            LATD=CINCO;
        break;
        
        case 6:
            LATD=SEIS;
        break;
        
        case 7:
            LATD=SIETE;
        break;
        
        case 8:
            LATD=OCHO;
        break;
        
        case 9:
            LATD=NUEVE;
        break;
    }
    __delay_ms(5);
}

void display1 (void)
{
    LATC = D1;
    switch (decenas)
    {
        case 0:
            LATD=CERO;
        break;
        
        case 1:
            LATD=UNO;
        break;
        
        case 2:
            LATD=DOS;
        break;
        
        case 3:
            LATD=TRES;
        break;
        
        case 4:
            LATD=CUATRO;
        break;
        
        case 5:
            LATD=CINCO;
        break;
        
        case 6:
            LATD=SEIS;
        break;
        
        case 7:
            LATD=SIETE;
        break;
        
        case 8:
            LATD=OCHO;
        break;
        
        case 9:
            LATD=NUEVE;
        break;
        
    }
    __delay_ms(5);
}