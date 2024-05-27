/*
 * File:   teclado.c
 * Author: ubecerril
 *
 * Created on 22 de mayo de 2024, 01:45 PM
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
#include <pic18f46k22.h>
#define _XTAL_FREQ 8000000

//VARIABLES PARA EL FUNCIONAMIENTO
#define D4 LATDbits.LATD0
#define D5 LATDbits.LATD1
#define D6 LATDbits.LATD2
#define D7 LATDbits.LATD3

#define RS LATDbits.LATD4
#define RW LATDbits.LATD5
#define E LATDbits.LATD6

unsigned char linea = 0xC0;

//FUNCIONES PROTOTIPO
void setup(void);
void enviarNibble(unsigned char);
void enviarByte (unsigned char);

void main(void) 
{
    setup();
    
    while(1)
    {
    }//FIN WHILE
    
    return;
}//FIN MAIN

void __interrupt() isr_general(){
    INTCONbits.INT0E = 0;
    INTCONbits.INT0F = 0;
    
    unsigned char dato = PORTB >> 4;
    switch (dato){
        case 0b1101://0
            enviarByte(0x30);
            break;
        
        case 0b1000://1
            enviarByte(0x31);
            break;
            
        case 0b1001://2
            enviarByte(0x32);
            break;
            
        case 0b1010://3
            enviarByte(0x33);
            break;
            
        case 0b0100://4
            enviarByte(0x34);
            break;
            
        case 0b0101://5
            enviarByte(0x35);
            break;
            
         case 0b0110://6
             enviarByte(0x36);
            break;
            
        case 0b0000://7
            enviarByte(0x37);
            break;
            
        case 0b0001://8
            enviarByte(0x38);
            break;
            
        case 0b0010://9
            enviarByte(0x39);
            break;
            
        case 0b1111://SALTO
            if(linea == 0xC0){
                linea = 0x80;
            }else {
                linea = 0xC0;
            }
            
            RS = 0;
            enviarByte(linea);
            RS = 1;
            
            break;
            
    }//FIN SWITCH CASE
    
    INTCONbits.INT0E = 1;
}//FIN INTERRUPCION

void setup (void){
    //CONFIGURACION DE PUERTOS
    TRISB = 0xFF;   //PUERTO B ENTRADA
    ANSELB = 0x00;  //PUERTO B ENTRADA DIGITAL
    
    TRISD = 0x00;   //PUERTO D SALIDA
    ANSELD = 0X00;  //PUERTO D SALIDA DIGITAL
        //CONFIGURACION DE INTERRUPCIONES
    INTCONbits.INT0E = 1;   //INT 0 HABILITADA
    INTCONbits.INT0F = 0;   //BORRAR INT 0
    INTCONbits.GIE = 1;     //INT GLOBALES HABILITADAS
    
    //COMANDOS PARA ENCENDER PANTALLA
    RS = 0;
    RW = 0;
    __delay_ms(20);
    enviarNibble(0x03);
    enviarNibble(0x03);
    enviarNibble(0x03);
    
    //SETEAR A 4BITS (SECUENCIA DE INICIALIZACION)  
    enviarNibble(0x02); //4bits
    enviarByte(0x20);   //2 lineas y caracteres
    enviarByte(0x08);   //Apagar
    enviarByte(0x01);   //Limpiar
    enviarByte(0x06);   //Shift
    enviarByte(0x02);   //Return home
    
    //ENCENDER
    enviarByte(0x0F);
    
    RS = 1;
}//FIN SETUP

void enviarNibble (unsigned char dato){
    D4 = (dato >> 0) & 0x01;
    D5 = (dato >> 1) & 0x01;
    D6 = (dato >> 2) & 0x01;
    D7 = (dato >> 3) & 0x01;
    
    E = 1;
    __delay_ms(100);
    E = 0;
    __delay_ms(100);
}//FIN ENVIAR NIBBLE

void enviarByte (unsigned char dato){
    enviarNibble(dato >> 4);
    enviarNibble(dato & 0x0F);
}//FIN ENVIAR BYTE
