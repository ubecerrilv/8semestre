/*
 * File:   InterrupcionM.c
 * Author: ubecerril
 *
 * Created on April 24, 2024, 2:59 PM
 */


#pragma config FOSC = HSHP       // Oscillator Selection bits (XT oscillator)
#pragma config PWRTEN = ON      // Power-up Timer Enable bit (Power up timer enabled)
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config MCLRE = INTMCLR  // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

#define _XTAL_FREQ 8000000
int dato=0, n0=0, n1=0, n2=0, n3=0;
volatile unsigned char anterior = 0;
volatile unsigned char cambios = 0;
#include <xc.h>
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
unsigned char D3 = 0xF7;
unsigned char D2 = 0xFB;
unsigned char D1 = 0xFD;
unsigned char D0 = 0xFE;

//FUNCIONES PROTOTIPO
void cambia(int);
void display0(void);
void display1(void);
void display2(void);
void display3(void);

void main(void) 
{
    //CONFIGURACIÓN DE PUERTOS
    TRISC = 0xF0;   //Control de los transistores (Salida C0:C3)
    TRISD=0x00;     //Control de pantallas (Salida D0:D7)
    TRISB=0xF0;     //Control de interrupciones (Entrada B4:B7)
    ANSELB=0x0F;    //Puerto B como entrada digital (B4:B7)
      
    //CONFIGURACIÓN DE INTERRUPCIONES
    INTCON=0x88;    //Interrupciones en general
    //__delay_ms(1000);
    IOCB=0xF0;      //habilita los pines del puerto B<4:7> para usarse en
                            //la interrupción del puerto B
    /*INTCONbits.RBIE=1;     //habilita las interrupción externa 0
    INTCONbits.RBIF=0;     //borra la bandera de la interrupción externa 0
    INTCONbits.GIE=1;      //habilita de forma global las interrupciones*/
    
    while(1)
    {
        display0();
        display1();
        display2();
        display3();
    }
       
    return;
}

void __interrupt () isr_general () 
{
    INTCONbits.RBIE=0;
    
    __delay_ms(200);
        unsigned char actual = PORTB;
        switch (actual){
            case 0x80:
                n0=0;
                n1=0;
                n2=0;
                n3=1;
                break;
            
            case 0x40:
                n0=0;
                n1=0;
                n2=1;
                n3=0;
                break;
                
            case 0x20:
                n0=0;
                n1=1;
                n2=0;
                n3=0;
                break;
                
            case 0x10:
                n0=1;
                n1=0;
                n2=0;
                n3=0;
                break;
                
            case 0x00:
                n0=0;
                n1=0;
                n2=0;
                n3=0;
                break;
        }
  
    __delay_ms(100);
    INTCONbits.RBIF=0;
    INTCONbits.RBIE=1;
   }

void display0 ()
{

    LATC = D0;
    switch (n0)
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
    __delay_ms(35);
}

void display1 ()
{
    LATC = D1;
    switch (n1)
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
    }
    __delay_ms(35);
}
void display2 ()
{
    LATC = D2;
    switch (n2)
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
    __delay_ms(35);
}

void display3 ()
{
    LATC = D3;
    switch (n3)
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
    }
    __delay_ms(35);
}