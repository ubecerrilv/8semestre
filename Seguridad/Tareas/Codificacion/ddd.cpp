#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<openssl/evp.h>
#include "Entradas.cpp"

using namespace std;
using namespace obtener;
using namespace archivos;

//FUNCIONES PROTOTIPO
void menu(void);
void obtenerArch(ifstream&, ofstream&);
void codifica (bool);

int main(){
    menu();

    return 1;
}

void menu(void){
    mostrarMensaje("*************************************************");
    mostrarMensaje("PROGRAMA PARA CODIFICACIÓN TRIPLE-DES CON OPENSSL");
    mostrarMensaje("*************************************************");
    mostrarMensaje("Opciones: \n1. Encriptar archivo.\n2. Desencriptar archivo. \n3. Salir.\nElige una opción: ");
    string opcion;

    getline(cin, opcion);
    int op = atoi(opcion.c_str());
    
    while(op!=1 && op!=2 && op!=3){
        mostrarMensaje("Opción no válida, elige una opción:");
        getline(cin, opcion);
        op = atoi(opcion.c_str());
    }

    switch (op)
    {
    case 1:
        //Codificar
        codifica(true);
        menu();
        break;
    
    case 2:
        //Decodificar
        codifica(false);
        menu();
        break;

    case 3:
        break;
    }
}

void obtenerArch(ifstream& entrada, ofstream& salida){
    //Obtener archivo de entrada
    entrada = abrirLecturaBin();

    //Obtener archivo de salida
    salida = abrirEscrituraBin();
}
void codifica (bool encripta){

    //Obtener la llave
    string llaveS;
    mostrarMensaje("Ingresa la llave para cifrar/decifrar el archivo: ");
    getline(cin, llaveS);
    while (llaveS.length()!=8){
        mostrarMensaje("La llave debe tener una longitud de 8 bytes, ingresa una llave válida: ");
        getline(cin, llaveS);
    }
    vector<unsigned char> llaveV(llaveS.begin(), llaveS.end());
    unsigned char* llave = llaveV.data();

    //Inicializar el contexto de la encriptacion
    EVP_CIPHER_CTX *contexto;
    contexto = EVP_CIPHER_CTX_new();


    //Inicializar encriptacion
    EVP_EncryptInit_ex(contexto, EVP_des_ecb(),NULL, llave, NULL);

    //Obtener los archivos de entrada/salida
    ifstream entrada;
    ofstream salida;
    obtenerArch(entrada, salida);

    string mensajeS;
    getline(entrada, mensajeS);
    entrada.close();
    vector<unsigned char> mensajeV(mensajeS.begin(), mensajeS.end());
    unsigned char* mensaje = mensajeV.data();

    unsigned char mensajeSalida[sizeof(mensaje)];
    int longSal;

    if(encripta){//Encriptar
        EVP_EncryptUpdate(contexto, mensajeSalida, &longSal, mensaje, sizeof(mensaje));
    }else{//Desencriptar
        EVP_DecryptUpdate(contexto, mensajeSalida, &longSal, mensaje, sizeof(mensaje));
    }

    //Guardar el resultado en un archivo
    //salida.write(reinterpret_cast<const char*>(&bloqueOUT), sizeof(const_DES_cblock));
    salida<<mensajeSalida;
    salida.close();
    mostrarMensaje("Proceso realizado correctamente.");

}//Fin codifica