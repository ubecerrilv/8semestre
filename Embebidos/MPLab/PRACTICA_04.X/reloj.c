/*
 * File:   reloj.c
 * Author: ubecerril
 *
 * Created on 1 de abril de 2024, 10:02 AM
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

unsigned char CEROP = 0xBF;
unsigned char UNOP = 0x86;
unsigned char DOSP = 0xDB;
unsigned char TRESP = 0xCF;
unsigned char CUATROP = 0xE6;
unsigned char CINCOP = 0xED;
unsigned char SEISP = 0xFD;
unsigned char SIETEP = 0x87;
unsigned char OCHOP = 0xFF;
unsigned char NUEVEP = 0xEF;

//VARIABLES PARA LOS DISPLAY
unsigned char D3 = 0x7F;
unsigned char D2 = 0xBF;
unsigned char D1 = 0xDF;
unsigned char D0 = 0xEF;

//FUNCIONES PROTOTIPO
void display0(int);
void display1(int);
void display2(int);
void display3(int);

//VARIABLES MINUTOS Y SEGUNDOS
static int minutos, segundos, vueltas;

void main(void) {
    TRISB = 0x00; //PUERTOB EN MODO SALIDA
    TRISD = 0x0F; //PUERTOD EN MODO SALIDA
    
    while (1)
    {
        display0(segundos);
        
        display1(segundos);
        
        display2(minutos);
        
        display3(minutos);
        
        vueltas++;
        if(vueltas ==48)
        {
            segundos ++;
            vueltas = 0;
        }
        if (segundos ==60)
        {
            minutos++;
            segundos =0;
            vueltas=0;
        }
        if(minutos==60)
        {
            vueltas=0;
            segundos=0;
            minutos=0;
        }
    }
    
    return;
}

void display0 (int s)
{
    s %= 10;
    LATD = D0;
    switch (s)
    {
        case 0:
            LATB=CERO;
        break;
        
        case 1:
            LATB=UNO;
        break;
        
        case 2:
            LATB=DOS;
        break;
        
        case 3:
            LATB=TRES;
        break;
        
        case 4:
            LATB=CUATRO;
        break;
        
        case 5:
            LATB=CINCO;
        break;
        
        case 6:
            LATB=SEIS;
        break;
        
        case 7:
            LATB=SIETE;
        break;
        
        case 8:
            LATB=OCHO;
        break;
        
        case 9:
            LATB=NUEVE;
        break;
    }
    __delay_ms(5);
}

void display1 (int s)
{
    s /= 10;
    LATD = D1;
    switch (s)
    {
        case 0:
            LATB=CERO;
        break;
        
        case 1:
            LATB=UNO;
        break;
        
        case 2:
            LATB=DOS;
        break;
        
        case 3:
            LATB=TRES;
        break;
        
        case 4:
            LATB=CUATRO;
        break;
        
        case 5:
            LATB=CINCO;
        break;
        
        case 6:
            LATB=SEIS;
        break;
    }
    __delay_ms(5);
}
void display2 (int m)
{
    m %= 10;
    LATD = D2;
    switch (m)
    {
        case 0:
            LATB=CEROP;
        break;
        
        case 1:
            LATB=UNOP;
        break;
        
        case 2:
            LATB=DOSP;
        break;
        
        case 3:
            LATB=TRESP;
        break;
        
        case 4:
            LATB=CUATROP;
        break;
        
        case 5:
            LATB=CINCOP;
        break;
        
        case 6:
            LATB=SEISP;
        break;
        
        case 7:
            LATB=SIETEP;
        break;
        
        case 8:
            LATB=OCHOP;
        break;
        
        case 9:
            LATB=NUEVEP;
        break;
    }
    __delay_ms(5);
}

void display3 (int m)
{
    m /= 10;
    LATD = D3;
    switch (m)
    {
        case 0:
            LATB=CERO;
        break;
        
        case 1:
            LATB=UNO;
        break;
        
        case 2:
            LATB=DOS;
        break;
        
        case 3:
            LATB=TRES;
        break;
        
        case 4:
            LATB=CUATRO;
        break;
        
        case 5:
            LATB=CINCO;
        break;
        
        case 6:
            LATB=SEIS;
        break;
    }
    __delay_ms(5);
}