#include<iostream>
#include<string>
#include<fstream>

using namespace std;

/*El nombre de espacios obtener obtiene todos los datos como strings, los valida
*si son correctos los regresa.*/
namespace obtener{
    //Variables globales
    string cadena;

    //Funciones prototipo usadas por las funciones que obtienen los valores
    bool esIntValido(string&);
    bool esCharValido(string&);
    bool esDoubleValido(string&);

    void mostrarMensaje(string);

    /******************************************************************
     *      FUNCIONES PARA OBTENER DATOS DE LA ENTRADA ESTÁNDAR
    ******************************************************************/
    
    /*Función para recuperar una cadena desde la entrada estándar*/
    string obtenerCad(void){
        string res;
        getline (cin, res);
        return res;
    }

    /* Función para recuperar un int desde la entrada estándar
     * no recibe parámetros y regresa un int cuando es válido
     * mientras el valor ingresado por el usuario no sea un int
     * muestra mensaje de error y pide que se ingrese de nuevo.*/
    int obtenerInt(void){
        //Variables auxiliares para la obtención del int
        bool noInt=true;

        //Ciclo para la obtención del int
        while (noInt){
            //Recupera el valor como cadena para validarlo
            try{
                getline(cin, cadena);
                if (!esIntValido(cadena)) throw cadena;
            }catch(string e){
                cout<<"\""<<e<<"\""<<" No es un valor entero váldo, introduce un valor entero."<<endl;
                continue;
            }

            //Si no ha saltado la excepción es un int válido y podemos transformarlo para regresarlo
            noInt = false;                  //Romper el ciclo
        }
        return atoi(cadena.c_str());    //Es necesario pasar a cadena c para la conversión
    }//Fin obtenerInt

    /*Función para recuperar un caracter desde la entrada estándar
     * no recibe parámtros y regresa un caracter cuando es válido
     * mientras el valor ingresado por el usuario no sea un caracter
     * muestra mensaje de error y pide que se ingrese de nuevo.*/
    char obtenerChar (void){
        //Variables auxiliares para a obtención del char
        bool noChar = true;

        //Ciclo para la obtención del char
        while(noChar){
            try{
                getline(cin, cadena);
                if(!esCharValido(cadena)) throw cadena;
            }catch(string e){
                cout<<"\""<<e<<"\" No es un caracter válido, introduce un caracter válido."<<endl;
                continue;
            }
            noChar=false;
        }
        return cadena.at(0);
    }

    /*Función para recuperar un punto flotante desde la entrada estándar
     * no recibe parámtros y regresa un punto flotante cuando es válido
     * mientras el valor ingresado por el usuario no sea un punto flotante
     * muestra mensaje de error y pide que se ingrese de nuevo.*/
    double obtenerDouble (void){
        //Variables auxiliares para la validación
        bool noDouble = true;

        while(noDouble){
            try{
                getline(cin, cadena);
                if (!esDoubleValido(cadena)) throw cadena;
            }catch(string e){
                cout << "\""<<e<<"\" No es un valor foltante válido, ingresa un valor válido."<<endl;
                continue;
            }
            noDouble = false;
        }
        return double(atof(cadena.c_str()));
    }

    /******************************************************************
     *      FUNCIONES PARA VALIDAR DATOS DE LA ENTRADA ESTÁNDAR
    ******************************************************************/
    
    /*Funcion para validar si un valor introucido es un int valido
    *recibe un string y retorna un valor verdadero si es un int válido
    *retorna falso en caso contrario.*/
    bool esIntValido(string& cadena){
        //Si la cadena está vacía se regresa falso
        if (int(cadena.length())==0) return false;

        //Variables auxiliares para la validación
        bool signo = false;
        int inicio = 0;

        //Comprobar si se ha ingresado algún signo
        if (cadena.at(0)=='+' || cadena.at(0)=='-'){
            signo = true;
            inicio = 1;
        }

        //Por lo menos un caracter después del signo
        if(signo && int(cadena.length()==1)) return false;

        //Comprobar que el resto de caracteres son dígitos
        for(int i = inicio; i<cadena.length();i++){
            if(!isdigit(cadena.at(i))) return false;
        }

        //Si se han pasado todas las pruebas anteriores, es int válido
        return true;
    }//Fin esIntValido

    /*Funcion para validar si un valor introucido es un caracter valido
    *recibe un string y retorna un valor verdadero si es un caracter
    *(un solo caraceter) retorna falso en caso contrario.*/
    bool esCharValido(string& cadena){
        return cadena.length() == 1;
    }//Fin esCharValido

    /*Funcion para validar si un valor introucido es un punto flotante valido
    *recibe un string y retorna un valor verdadero si es un punto flotante válido
    *retorna falso en caso contrario.*/
    bool esDoubleValido(string& cadena){
        //Si la cadena está vacía regresar falso
        if(cadena.length()==0) return false;
        
        //Variables auxiliares para la validación
        bool signo = false;
        int inicio = 0;
        int punto = 0;

        //Validar si existe signo
        if(cadena.at(0)=='+' || cadena.at(0)=='-'){
            signo = true;
            inicio = 1;
        }
        
        //Por lo menos un caracter después del signo
        if(signo && cadena.length()==1) return false;

        //Validar punto
        for(int i = inicio; i<cadena.length(); i++){
            if(cadena.at(i)=='.') punto++;
            if((!isdigit(cadena.at(i)) && !cadena.at(i)=='.') || punto>1)return false;
        }
        
        //Si ha pasado todas las pruebas se retorna verdadero
        return true;
    }//Fin esDoubleValido

    /******************************************************************
     *      FUNCIONES PARA MANDAR DATOS A LA SALIDA ESTÁNDAR
    ******************************************************************/

    /*Función para mostrar el mansaje pasado como parámetro junto con un salto
    *de línea.*/
    void mostrarMensaje(string mensaje){
        cout<<mensaje<<endl;
    }//Fin mostrarMensaje
}//Fin nombre de espacios validar

//Espacio de nombres para recuperar archivos
namespace archivos{
    using namespace obtener;

    /*Función para poder abrir un archivo en modo lectura, mientras el archivo no pueda ser abierto
    *pide un nuevo nombre

    *@return objeto con la conexión al archivo en modo lectura*/
    
    ifstream abrirLectura(void){
        ifstream res;
        bool noAbierto = true;
        string archivoNom;
        
        //Abrir archivo de entrada
        while(noAbierto){
            try{
                mostrarMensaje("Ingresa el nombre del archivo a codificar (ruta completa): ");
                getline(cin, archivoNom);

                res.open(archivoNom);
                if (res.fail()) throw archivoNom;
            }catch(string e)    
            {
                mostrarMensaje("Archivo con el nombre \""+e+"\" no pudo ser abierto, verifica su nombre o existencia: ");
                continue;
            }
            //Archivo abierto
            noAbierto = false;
        }

        return res;
    }

    /*Función para poder abrir un archivo para escritura
    *si hay un archivo existente con ese nombre advierte al usuario de la 
    *sobrescritura

    *@return objeto con la conexión al archivo en modo escritura*/
    
    ofstream abrirEscritura(void){
        ifstream aux;
        ofstream res;

        string salidaNom;

        //Verificar su existencia para podfer advertir al usuario de su sobrescritura.
        bool noExiste = true;
        while (noExiste){
            mostrarMensaje("Ingresa el nombre del archivo de salida, este será almacenado en el directoio actual: ");
            getline(cin, salidaNom);

            aux.open(salidaNom);

            //Preguntar si se sobrescribe
            if(!aux.fail()){
                mostrarMensaje("El archivo ya existe. ¿Sobrescribirlo? (s/n)");
                char respuesta = obtenerChar();

                switch (respuesta){
                    case 'n':
                        aux.close();
                        continue;

                    default:
                        aux.close();
                        noExiste = false;
                        break;
                }
            }

            //Si no existe no es necesario preguntar por sobrescritura
            noExiste = false;
    }//Fin while sobrescritura

    //Abrir archivo para escritura
    res.open(salidaNom);

    //Regresar el objeto
    return res;
    }
}