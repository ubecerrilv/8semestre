/*
 * File:   proyecto.c
 * Author: equipo 2
 *
 * Created on June 1, 2024, 8:30 PM
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
#include <stdbool.h>
#define _XTAL_FREQ 8000000
/*DESCRIPCIÓN DE LA LIBRERÍA
 * Esta librería fue desarrollada para el manejo de una pantalla LCD 2x16.
 * En concreto está desarrollada para poder ser utilizada por el 
 * PIC18F46K22, aunque puede ser utilizada por cualquier otro PIC
 * simplemente cambiando los pines de salida.
 * 
 * Esta libreía esta implementada usando el canal de 4 bits entre el PIC y la 
 * pantalla LCD (D4:D7), además de los pines RW, RS y E.
 */

/*ESPECIFICACIÓN DE LOS PINES DE SALIDA
 Estos pines pueden ser modificados deacuerdo a las necesidades del usuario
 o a las capacidades del PIC.*/
#define D4 LATDbits.LATD0
#define D5 LATDbits.LATD1
#define D6 LATDbits.LATD2
#define D7 LATDbits.LATD3

#define RS LATDbits.LATD4
#define RW LATDbits.LATD5
#define E LATDbits.LATD6

unsigned char linea = 0xC0;

/*PROTOTIPOS DE FUNCIONES
 Estas son las firmas de los métodos que se encuentran dentro de esta librería
 disponibles para su uso.*/
void start_LCD4b(void);
void clrs_LCD4b(void);
void wchar_LCD4b(unsigned char);
void wstring_LCD4b(char*);
void gotoxy_LCD4b(int, int);
void shift_L_LCD4b(int);
void shift_R_LCD4b(int);
void blinkc_LCD4b(bool);
void showc_LCD4b(bool);
void enviarNibble(unsigned char);
void enviarByte (unsigned char);

void main(void) 
{
    
    return;
}//FIN MAIN

/*Función start_LCD4b
 * Esta función realiza el proceso de inicialización de la pantalla LCD
 * las configuraciones por defecto son las siguientes:
 * Canal de comunicación de 4 bits
 * Pantalla con 2 líneas y 16 caractéres
 * Cursor encendido y parpadeando
 * 
 * Estas configuraciones se realizan por medio del puerto D
 */
void start_LCD4b(){
    //CONFIGURACION DE PUERTOS
    TRISD = 0x00;   //PUERTO D SALIDA
    ANSELD = 0X00;  //PUERTO D SALIDA DIGITAL

    //COMANDOS PARA ENCENDER PANTALLA
    RS = 0;
    RW = 0;
    __delay_ms(20);
    enviarNibble(0x03);
    enviarNibble(0x03);
    enviarNibble(0x03);
    
    //SETEAR A 4BITS (SECUENCIA DE INICIALIZACION)  
    enviarNibble(0x02); //4bits
    enviarByte(0x16);   //2 lineas y caracteres
    enviarByte(0x08);   //Apagar
    enviarByte(0x01);   //Limpiar
    enviarByte(0x06);   //Shift
    enviarByte(0x02);   //Return home
    
    //ENCENDER
    enviarByte(0x0F);
}//Fin start_LCD4b

/*Función clrs_LCD4b
 Esta función realiza una limpieza de los caracteres de la pantalla,
 además de regresar el cursor a la posición inicial.*/
void clrs_LCD4b(){
    RS = 0;
    RW = 0;
    enviarByte(0x01);
}//Fin clrs_LCD4b

/*Función wchar_LCD4b
 Esta función imprime directamente un caracter en la pantalla en la posición
 actual del cursor.*/

void wchar_LCD4b(unsigned char c){
    RS = 1;
    RW = 0;
    enviarByte(c);
}//Fin wchar_LCD4b

/*Función wchar_LCD4b
 Esta función imprime directamente una cadena de caracteres
 en la pantalla en la posición actual del cursor.*/
void wstring_LCD4b(char *cadena){
    for(int i = 0; cadena[i] != '\0'; i++){
        wchar_LCD4b(cadena[i]);
    }
}//Fin wstring_LCD4b

/*Función gotoxy_LCD4b
 Esta función recibe como parametros el valor x y el valor y al cual se
 transportará en cursor.
 Estos valores van de 1 a 2 para x y de 1 a 16 para y*/
void gotoxy_LCD4b(int x, int y){
    RS = 0;
    RW = 0;
    
    if(x == 1){
        enviarByte(0x80 + (0x00 + (y-1)));
    }else if(x == 2){
        enviarByte(0x80 + (0x40 + (y-1)));
    }
}//Fin gotoxy_LCD4b

/*Función shift_L_LCD4b
 Esta función realiza un desplazamiento a la izquierda del texto actual en la
 pantalla, recibe de parámetro el valor de los deslazamientos*/
void shift_L_LCD4b(int l){
    RS = 0;
    RW = 0;

    for(int i = 0; i<l; i++){
        enviarByte(0x18);
        __delay_ms(250);
    }
}//Fin shift_L_LCD4b

/*Función shift_L_LCD4b
 Esta función realiza un desplazamiento a la derecha del texto actual en la
 pantalla, recibe de parámetro el valor de los deslazamientos*/
void shift_R_LCD4b(int r){
    RS = 0;
    RW = 0;
    
    for(int i = 0; i<r; i++){
        enviarByte(0x1C);
        __delay_ms(250);
    }
}//Fin shift_R_LCD4b

/*Función blink_LCD4b
 Esta función recibe un parámetro booleano, el cual determina si el cursor 
 de la pantalla parpadea o no.
 False =  No parpadea
 True = Parpadea*/
void blinkc_LCD4b(bool b){
    RS = 0;
    RW = 0;
    if(b){
        enviarByte(0x0F);
    }else{
        enviarByte(0x0E);
    }
    
}//Fin blinkc_LCD4b

/*Función showc_LCD4b
 Esta función recibe un parámetro booleano, el cual determina si el cursor
 se la pantalla se muestra o no.
 False = No se muestra cursor
 True = Se muestra cursor*/
void showc_LCD4b(bool b){
    RS = 0;
    RW = 0;
    if(b){
        enviarByte(0x0F);
    }else{
        enviarByte(0x0C);
    }
}//Fin showc_LCD4b


/*Función enviarNibble
 Esta función fue creada para poder realizar la comunicación con la pantalla
 LCD, envía medio byte (Nibble) mediante los pines definidos para la
 comunicación con la pantalla. Se realiza con un respectivo delay para poder
 permitir que la pantalla realice la operación.
 Es importante tomar en cuenta que esta función no realiza la modificación 
 de los pines RS 0 RW por lo que hay que tomarlo en cuenta antes de realizar
 una llamada a esta función o a enviarByte*/
void enviarNibble (unsigned char dato){
    D4 = (dato >> 0) & 0x01;
    D5 = (dato >> 1) & 0x01;
    D6 = (dato >> 2) & 0x01;
    D7 = (dato >> 3) & 0x01;
    
    E = 1;
    __delay_ms(30);
    E = 0;
    __delay_ms(30);
}//FIN ENVIAR NIBBLE

/*Función enviarByte
 Recibe un byte completo para poder enviarlo en dos partes mendiante el uso de
 la función enviarNibble, no es necesario agregar delay ya que la función
 enviarNibble ya contiene esta característica*/
void enviarByte (unsigned char dato){
    enviarNibble(dato >> 4);
    enviarNibble(dato & 0x0F);
}//FIN ENVIAR BYTE
