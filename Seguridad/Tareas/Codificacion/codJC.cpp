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
    salida.close();

}

string codifica (string& cad, int desplazamiento){
    string nueva = cad;
    int limiteU = int('Z');
    int limiteL = int('z');
    int actual=0;
    
    desplazamiento %= 25;

    //Verificar desplazamiento para decodificar
    if (desplazamiento<0){
        desplazamiento += 26;
    } 

    for(int i = 0; i<cad.length();i++){
        //Variable auxiliar para realizar desplazamiento
        actual = int(cad[i]);

        if(cad[i]!=' ' && !ispunct(cad[i]) && cad[i]!='\n' && cad[i]!='\t'){
            //Dividir en mayúsculas y minúsculas
            if(islower(cad[i])){
                if(actual+desplazamiento > limiteL) nueva[i]= char(actual-26+desplazamiento);
                else nueva[i] = char(actual+desplazamiento);
            }else if (isupper(cad[i])){
                if(actual+desplazamiento > limiteU) nueva[i]= char(actual-26+desplazamiento);
                else nueva[i] = char(actual+desplazamiento);
            }
        }
    }

    return nueva;
}//Fin codifica