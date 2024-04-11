#include<iostream>
#include<string>
#include<fstream>
#include "Entradas.cpp"

using namespace std;
using namespace obtener;
using namespace archivos;

//FUNCION PROTOTIPO
string codifica (string&, int);

int main(){
    string archivoNom, cadena, salidaNom;
    int des;
    char c;
    double si;
    //Objetos de manipulación de los archivos
    ifstream entrada, salidaAux;
    ofstream salida;

    //Obtener datos de entrada
    entrada = abrirLectura();
    getline(entrada, cadena, char(0x00));
    entrada.close();

    mostrarMensaje("Introduce el desplazamiento: ");
    des = obtenerInt();

    salida = abrirEscritura();

    //Codificar y desplegar en la salida
    salida<<codifica(cadena, des);

}

string codifica (string& cad, int desplazamiento){
    string nueva = cad;
    int base = int('A');
    int limite = int('z');
    int actual=0;

    for(int i = 0; i<cad.length();i++){
        //Variable auxiliar para realizar desplazamiento
        actual = int(cad[i]);

        if(cad[i]!=' ' && !ispunct(cad[i])){
            if((actual+desplazamiento)>limite){
                nueva[i] = char(actual-26+desplazamiento);
            }else{
                nueva[i] = char(actual+desplazamiento);
            }
        }
    }
    return nueva;
}//Fin codifica