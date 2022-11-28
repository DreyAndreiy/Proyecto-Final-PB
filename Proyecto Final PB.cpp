#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <math.h>
using namespace std;

struct Juegos {
    char numero[4]="";
    char juego[21] = "";
    char anyo[5] = "";
    char clasificacion[21] = "";
    char caracteristicas[31] = "";
    char descripcion[31] = "";
    char genero[21] = "";
    char precio[20] = "";
    float precioUnit;
    char impuestoChar[20]="";
    float impuesto;
    char totalChar[20] = "";
    float total;
};
int a;
int b = 1;
int c;
int x = 0;
int y = 0;


void agregarJuego() {
    ofstream archivo("videopatoli.txt", ios::app);
    Juegos juego;

    cin.ignore();
        
    cout << "\n\t//Ingrese el numero del articulo (no mas de 3 digitos): ";
    cin.getline(juego.numero, 4);

    cout << "\n\t//Ingrese el nombre del juego: ";
    cin.getline(juego.juego, 21);

    cout << "\n\t//Ingrese el anyo de salida del juego: ";
    cin.getline(juego.anyo, 5);

    cout << "\n\t//Ingrese la clasificacion del juego: ";
    cin.getline(juego.clasificacion, 21);

    cout << "\n\t//Ingrese las caracteristicas del titulo: ";
    cin.getline(juego.caracteristicas, 31);

    cout << "\n\t//Ingrese la descripcion del titulo: ";
    cin.getline(juego.descripcion, 31);

    cout << "\n\t//Ingrese el genero del titulo: ";
    cin.getline(juego.genero, 21);

    cout << "\n\t//Ingrese el precio del articulo: ";
    cin.getline(juego.precio, 7);

    juego.precioUnit = atof(juego.precio);

    juego.impuesto = (juego.precioUnit * 0.16);

    juego.total = juego.precioUnit + juego.impuesto;

    sprintf_s(juego.impuestoChar, "%f", juego.impuesto);
    sprintf_s(juego.totalChar, "%f", juego.total);

    archivo.write((char*)&juego, sizeof(juego));
    
    archivo.close();
}

void verLista() {
    struct Juegos juego;
    ifstream archivoLista("videopatoli.txt");

    archivoLista.read((char*)&juego, sizeof(juego));

    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "| Num. |            Nombre            |Anyo de Salida|          Clasificacion          |        Caracteristicas        |         Descripcion         |       Genero       |Precio|  Impuesto  |Precio Total|" << endl << endl;

    while (archivoLista && !archivoLista.eof()) {
        cout << "  " << right << setw(3) << juego.numero << "    " << left << setw(20) << juego.juego << "               " << left << setw(4) << juego.anyo << "       " << left << setw(20) << juego.clasificacion << "             " << left << setw(30) << juego.caracteristicas << "  " << left << setw(30) << juego.descripcion << " " << left << setw(20) << juego.genero << " " << left << setw(6) << juego.precio << "  " << left << setw(5) << juego.impuestoChar << "   " << left << setw(5) << juego.totalChar << endl;
        archivoLista.read((char*)&juego, sizeof(juego));
    }
    cout << "\n\t\t";
    archivoLista.close();
}

int numLocalizado(string numBuscado) {
    struct Juegos juego;
    int counter = 0;
    string bufferNum;
    ifstream archivoMostrar("videopatoli.txt");
    archivoMostrar.read((char*)&juego, sizeof(juego));

    while (archivoMostrar && !archivoMostrar.eof()) {
        counter++;
        bufferNum = juego.numero;
        if (numBuscado == bufferNum) {
            cout << "\n\t\tNumero de articulo encontrado: " << juego.juego << endl;
            cout << "\t\tPresiona cualquier tecla para continuar." << endl;
            return counter;
        }
        archivoMostrar.read((char*)&juego, sizeof(juego));
    }
    archivoMostrar.close();
    return 0;
}



bool cambiadoArticulo(int ubicacion) {
    try {
        struct Juegos juego;
        cin.ignore();
        cout << "\n\t//Ingrese nuevo numero del articulo: ";
        cin.getline(juego.numero, 4);

        cout << "\n\t//Ingrese el nuevo nombre del juego: ";
        cin.getline(juego.juego, 21);

        cout << "\n\t//Ingrese el nuevo anyo de salida del juego: ";
        cin.getline(juego.anyo, 5);

        cout << "\n\t//Ingrese la nueva clasificacion del juego: ";
        cin.getline(juego.clasificacion, 21);

        cout << "\n\t//Ingrese las nuevas caracteristicas del titulo: ";
        cin.getline(juego.caracteristicas, 31);

        cout << "\n\t//Ingrese la nueva descripcion del titulo: ";
        cin.getline(juego.descripcion, 31);

        cout << "\n\t//Ingrese el nuevo genero del titulo: ";
        cin.getline(juego.genero, 21);

        cout << "\n\t//Ingrese el precio del articulo: ";
        cin.getline(juego.precio, 7);

        juego.precioUnit = atof(juego.precio);

        juego.impuesto = (juego.precioUnit * 0.16);

        juego.total = juego.precioUnit + juego.impuesto;

        sprintf_s(juego.impuestoChar, "%f", juego.impuesto);
        sprintf_s(juego.totalChar, "%f", juego.total);

        fstream archivoCambio("videopatoli.txt");

        archivoCambio.seekg((ubicacion - 1) * sizeof(juego), ios::beg);

        archivoCambio.write((char*)&juego, sizeof(juego));

        archivoCambio.close();

        return true;
    }
    catch (exception e) {
        cout << "\t\tHa ocurrido un error." << e.what();
        return false;
    }

}

void modEntrada() {
    char numBuscado[4];
    int ubicacion = 0;
    system("cls");

    verLista();
    cin.ignore();
    cout << "\t\tIngrese el numero del articulo a modificar. \t";
    cin.getline(numBuscado, 4);
    ubicacion = numLocalizado(numBuscado);
    if (ubicacion) {
        if (cambiadoArticulo(ubicacion))
            cout << "\n\t\tEl articulo se ha modificado con exito." << endl;
    } else {
        cout << "\t\tEl articulo no existe en el archivo." << endl;
    }
}

void elimEntrada() {
    struct Juegos juego;
    system("cls");
    verLista();
    char bufferNum[4];
    cin.ignore();
    cout << "Ingrese el numero del articulo a eliminar: ";
    cin.getline(bufferNum, 11);
    if (numLocalizado(bufferNum)) {
        fstream archivoLectura("videopatoli.txt");
        ofstream archivoEscritura("auxiliar.txt");

        archivoLectura.read((char*)&juego, sizeof(juego));
        string numBuscado = bufferNum;
        while (archivoLectura && !archivoLectura.eof()) {
            if (juego.numero == numBuscado) {
                //No se hace nada
            }
            else {
                archivoEscritura.write((char*)&juego, sizeof(juego));
            }
            archivoLectura.read((char*)&juego, sizeof(juego));
        }
        archivoEscritura.close();
        archivoLectura.close();

        remove("videopatoli.txt");
        rename("auxiliar.txt", "videopatoli.txt");
    }
    else {
        cout << "No se ha encontrado un articulo con el numero: " << bufferNum << endl;
    }
}

void manualUsuario() {
    cout << "\n\t\tBienvenido a VideoPatoli, tienda dedicada a la venta de videojuegos." << endl;
    cout << "\n\t\tEn este manual se te explicaran las posibilidades de este programa, de manera sencilla." << endl;
    cout << "\n\t\t";
    system("pause");
    system("cls");
    cout << "\n\t\tPuedes agregar articulos, especificando toda la información." << endl;
    cout << "\n\t\tPero asegurate de no repetir el numero de un articulo, el programa lo rechazara." << endl;
    cout << "\n\t\t";
    system("pause");
    system("cls");
    cout << "\n\t\tUna vez agregados los articulos, podras verlos en la lista." << endl;
    cout << "\n\t\tEn caso de haberte equivocado, tambien puedes modificar los datos desde el menu." << endl;
    cout << "\n\t\t";
    system("pause");
    system("cls");
    cout << "\n\t\tY si te arrepientes de haber agregado una entrada, no te preocupes: " << endl;
    cout << "\n\t\tPuedes eliminar las entradas que desees desde el menu." << endl;
    cout << "\n\t\t";
    system("pause");
    system("cls");
    cout << "\n\t\tEn caso de que te parezca que ya hay demsiada informacion, no dudes en limpiar la pantalla." << endl;
    cout << "\n\t\tY si quieres salir del programa, ubica la opcion en el menu." << endl;
    cout << "\n\t\t";
    system("pause");
    cout << "\n\t\tEsperamos que te sea sencillo utilizar este progama." << endl;
    cout << "\n\t\tNo dudes seleccionar el manual de usuario nuevamente en el menu en caso de dudas." << endl;
}

int main() {

        system("color 02");

        manualUsuario();

        do {
            cout << "\n";
            cout << "\t\t***%%%======================MENU======================%%%***" << endl;
            cout << "\t\t***%               1. Agregar videojuego.               %***" << endl;
            cout << "\t\t***%               2. Ver Lista.                        %***" << endl;
            cout << "\t\t***%               3. Modificar Entrada.                %***" << endl;
            cout << "\t\t***%               4. Eliminar Entrada.                 %***" << endl;
            cout << "\t\t***%               5. Limpiar pantalla.                 %***" << endl;
            cout << "\t\t***%               6. Manual de Usuario.                %***" << endl;
            cout << "\t\t***%               7. Salir del programa.               %***" << endl;
            cout << "\t\t***%%%================================================%%%***" << endl;
            cout << "\n\t\tSeleccione una opcion: ";
            cin >> a;

            switch (a) {

            case 1: {
                cout << "\n\t\tVas a agregar un juego." << endl;
                agregarJuego();
                cout << "\n\t\t";
                system("pause");
            }
            break;

            case 2: {
                ifstream archivo;
                archivo.open("videopatoli.txt");
                if (!archivo) {
                    cout << "\n\t\tNo has agregado nada en el archivo." << endl;
                    cout << "\n\t\t";
                    system("pause");
                    break;
                }
                verLista();
                system("pause");
            }
            break;

            case 3: {
                ifstream archivo;
                archivo.open("videopatoli.txt");
                if (!archivo) {
                    cout << "\n\t\tNo has agregado nada en el archivo." << endl;
                    cout << "\n\t\t";
                    system("pause");
                    break;
                }
                modEntrada();
                cout << "\t\t";
                system("pause");
            }
            break;

            case 4: {
                ifstream archivo;
                archivo.open("videopatoli.txt");
                if (!archivo) {
                    cout << "\n\t\tNo has agregado nada en el archivo." << endl;
                    cout << "\n\t\t";
                    system("pause");
                    break;
                }
                elimEntrada();
                cout << "\t\t";
                system("pause");
            }
            break;

            case 5: {
                system("cls");
            }
            break;

            case 6: {
                manualUsuario();
            }
            break;

            case 7: {
                system("cls");
                cout << "\n\t\tSaliendo del programa..." << endl;
                b = b + 1;
                cout << "\n\t\t";
                system("PAUSE");
            }
            break;

            default: {
                cout << "\n\t\tSu opcion es incorrecta. Intente de nuevo." << endl;
                cout << "\n\t\t";
                system("pause");
            }
            break;
            }
        } while (b == 1);
        return 0;
}

