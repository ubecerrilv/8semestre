/*
 * File:   InterrupcionM.c
 * Author: ubecerril
 *
 * Created on April 24, 2024, 2:59 PM
 */


#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config PWRTEN = ON      // Power-up Timer Enable bit (Power up timer enabled)
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)

#include <xc.h>
#define _XTAL_FREQ 8000
int dato;
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
unsigned char D3 = 0x7F;
unsigned char D2 = 0xBF;
unsigned char D1 = 0xDF;
unsigned char D0 = 0xEF;

//FUNCIONES PROTOTIPO
void cambia(int);

void main(void) 
{
    //CONFIGURACIÓN DE PUERTOS
    TRISB = 0x01;//PIN0 EN ENTRADA
    TRISC = 0X0F;
    ANSELB = 0x00;
    //CONFIGURACIÓN DE PUERTOS
    TRISD=0X00;     //define al puerto D como salida
    TRISB=0XFF;     //define al puerto B como entrada
    ANSELB=0X00;    //habilita al puerto B como entrada/salida digital
      
  //CONFIGURACIÓN DE INTERRUPCIONES
    IOCB=0XF0;              //habilita los pines del puerto B<4:7> para usarse en
                            //la interrupción del puerto B
    INTCONbits.RBIE=1;     //habilita las interrupción externa 0
    INTCONbits.RBIF=0;     //borra la bandera de la interrupción externa 0
    INTCONbits.GIE=1;      //habilita de forma global las interrupciones
    
    
    while(1)
    {
        
    }
       
    return;
}

void __interrupt () isr_general () 
{
    IOCB=0X00;
    dato=PORTB;
    INTCONbits.RBIF=0;
    INTCONbits.RBIE=0;
    
    //__delay_ms(600);
    
    cambia(dato);
    //contador=contador+1;
    //LATD=contador;
    //LATD=dato;
    INTCONbits.RBIE=1;
    IOCB=0XF0;
   }
/**
 * @Brief Función para mostrar en los displays en cambio de un pulsador
 * @param dato
 */
void cambia (int dato){
    switch (dato){
        case 1:
            break;
            
        case 2:
            break;
            
        case 3:
            break;
            
        case 4: 
            break;
    }
}
