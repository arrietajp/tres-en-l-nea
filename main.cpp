/* 
 * File:   main.cpp
 * Author: Jean Arrieta
 *
 * Created on October 5, 2021, 4:07 PM
 */

#include<iostream>
#include <stdlib.h>

using namespace std;

/*
    int a=3;
    int b=4;
 
    int **q=NULL;   
    q=new int*[3];
    
    for(int i=0; i<3;i++)
    {
        q[i]=new int[4]; 
    }
    for(int i=0; i<a;i++)
    {
        delete[] q[i]; 
    }
    
    delete[] q;
 */
enum ESTADO {
    INICIALIZADO,
    FINALIZADO
};

ESTADO JUEGO = INICIALIZADO;

//short int cantidadLineasGanadas;
short int filaTablero = 4;
short int columnaTablero = 4;
string **tablero = NULL;
int NCaracteres = 0;
short int numIngreso = 0;
short int ultimaFila = 0;
short int turno = 0;

void creandoTabla() {
    //primera fila del arreglo
    tablero = new string*[filaTablero];

    //segunda fila del arreglo
    for (int i = 0; i < filaTablero; i++) {
        tablero[i] = new string[columnaTablero];
    }

    //Rellenando la matriz
    for (int i = 0; i < filaTablero; i++) {
        for (int j = 0; j < columnaTablero; j++) {
            tablero[i][j] = "  ";
        }
    }
}

char ValidarGanador() {
    //Comprobamos si tiene 4 posiciones consecutivas

    int totalN_horizontal_P1 = 0;
    int totalN_horizontal_P2 = 0;

    int totalN_diagonal_izq_P1 = 0;
    int totalN_diagonal_izq_P2 = 0;

    int totalN_diagonal_der_P1 = 0;
    int totalN_diagonal_der_P2 = 0;

    int totalN_vertical_P1 = 0;
    int totalN_vertical_P2 = 0;

    //cout << endl;
    for (int i = 0; i < NCaracteres; i++) {
        //Ver iteraciones
        //cout << "|| iteración: i >> " << i << " ||" << endl << endl;

        //Cuando NCaracteres es igual a 4
        //int cont1=-3;
        //--------------------------------------
        //     -3 -2 -1  0 +1 +2 +3
        //i=0  (X)(X)(X)[X] 
        //i=1     (X)(X)[X](X) 
        //i=2        (X)[X](X)(X) 
        //i=3           [X](X)(X)(X) 
        //--------------------------------------

        int posicionInicial_Izquierda = i - (NCaracteres - 1);
        if (numIngreso - 1 < columnaTablero - i && numIngreso - 1 >= (NCaracteres - 1) - i) {

            for (int j = posicionInicial_Izquierda; j <= i; j++) {
                //Posiciones evaluadas
                //cout << "pos_horiz_ " << j << endl;
                if (tablero[(ultimaFila)][(numIngreso - 1) + j] == "X ") {
                    totalN_horizontal_P1++;
                    if (totalN_horizontal_P1 == NCaracteres) {

                        //cout << endl;
                        //cout << "X" << endl;

                        JUEGO = FINALIZADO;
                        return 1;

                    }

                }
                if (tablero[(ultimaFila)][(numIngreso - 1) + j] == "O ") {
                    totalN_horizontal_P2++;
                    if (totalN_horizontal_P2 == NCaracteres) {

                        //cout << endl;
                        //cout << "O" << endl;

                        JUEGO = FINALIZADO;
                        return 2;
                    }

                }
            }
            //cout << endl;
            posicionInicial_Izquierda++;

            //cout << "__Caracteres encontrados: " << totalN << endl<<endl;
            totalN_horizontal_P1 = 0;
            totalN_horizontal_P2 = 0;
        }
    }

    //------------------------ //--------------------------//------------------------//------------------------//
    //-3 -2 -1  0 +1 +2 +3     //   -3 -2 -1  0 +1 +2 +3   //-3 -2 -1  0 +1 +2 +3    //-3 -2 -1  0 +1 +2 +3                                                    
    //         [X]             //               (X)        //               (X)      //                  (X)
    //      (X)                //            [X]           //            (X)         //               (X)
    //   (X)                   //         (X)              //         [X]            //            (X)
    //(X)                      //      (X)                 //      (X)               //         [X]

    //---------------------------------------------------------------------------

    for (int i = 0; i < NCaracteres; i++) {
        //cout << "|| iteración: Diag.iz >> " << i << " ||" << endl << endl;

        int posicionInicial_diagonal_izq = i - (NCaracteres - 1);

        if (numIngreso - 1 < columnaTablero - i && numIngreso - 1 >= (NCaracteres - 1) - i && ultimaFila <= filaTablero - (NCaracteres - (i)) && ultimaFila >= (NCaracteres)-(NCaracteres - i)) {

            for (int j = posicionInicial_diagonal_izq; j <= i; j++) {
                //cout << "pos_diag_izq_ " << j << endl;

                if (tablero[ultimaFila - j][(numIngreso - 1) + j] == "X ") {
                    totalN_diagonal_izq_P1++;
                    if (totalN_diagonal_izq_P1 == NCaracteres) {

                        //cout << endl;
                        //cout << "X"<< endl;

                        JUEGO = FINALIZADO;
                        return 1;
                    }

                }
                if (tablero[ultimaFila - j][(numIngreso - 1) + j] == "O ") {
                    totalN_diagonal_izq_P2++;
                    if (totalN_diagonal_izq_P2 == NCaracteres) {

                        //cout << endl;
                        //cout << "O" << endl;

                        JUEGO = FINALIZADO;
                        return 2;
                    }

                }

            }
            posicionInicial_diagonal_izq++;
            totalN_diagonal_izq_P1 = 0;
            totalN_diagonal_izq_P2 = 0;
        }
    }
    //cout<<endl;
    //------------------------ //--------------------------//------------------------//------------------------//
    //-3 -2 -1  0 +1 +2 +3     //   -3 -2 -1  0 +1 +2 +3   //-3 -2 -1  0 +1 +2 +3    //-3 -2 -1  0 +1 +2 +3                                                    
    //(X)                      //      (X)                 //      (X)               //         [X]
    //   (X)                   //         (X)              //         [X]            //            (X)
    //      (X)                //            [X]           //            (X)         //               (X)
    //         [X]             //               (X)        //               (X)      //                  (X)

    //-----------------------------------------------------------------------------------------------------------

    for (int i = 0; i < NCaracteres; i++) {

        //cout << "|| iteración: Diag.der >> " << i << " ||" << endl << endl;

        int posicionInicial_diagonal_der = i - (NCaracteres - 1);

        if (numIngreso - 1 < columnaTablero - i && numIngreso - 1 >= (NCaracteres - 1) - i && ultimaFila < (filaTablero) - i && ultimaFila > (NCaracteres) - i) {


            for (int j = posicionInicial_diagonal_der; j <= i; j++) {
                //cout << "pos_diag_der_ " << j << endl;


                if (tablero[ultimaFila + j][(numIngreso - 1) + j] == "X ") {
                    totalN_diagonal_der_P1++;
                    if (totalN_diagonal_der_P1 == NCaracteres) {

                        //cout << endl;
                        //cout << "X" << endl;

                        JUEGO = FINALIZADO;
                        return 1;
                    }
                }
                if (tablero[ultimaFila + j][(numIngreso - 1) + j] == "O ") {
                    totalN_diagonal_der_P2++;
                    if (totalN_diagonal_der_P2 == NCaracteres) {

                        //cout << endl;
                        //cout << "O" << endl;

                        JUEGO = FINALIZADO;
                        return 2;
                    }

                }

            }
            posicionInicial_diagonal_der++;
            totalN_diagonal_der_P1 = 0;
            totalN_diagonal_der_P2 = 0;
        }
    }


    //--------------------------------------
    // [X]
    // (X)
    // (X)
    // (X)

    for (int i = 0; i < NCaracteres; i++) {
        if (ultimaFila - 1 < filaTablero - NCaracteres) {

            //cout << endl;
            //cout << "___ Vertical";

            if (tablero[(ultimaFila + i)][(numIngreso - 1)] == "X ") {
                totalN_vertical_P1++;
                if (totalN_vertical_P1 == NCaracteres) {

                    //cout << endl;
                    //cout << "X" << endl;

                    JUEGO = FINALIZADO;
                    return 1;
                }
            }
            if (tablero[(ultimaFila + i)][(numIngreso - 1)] == "O ") {
                totalN_vertical_P2++;
                if (totalN_vertical_P2 == NCaracteres) {

                    //cout << endl;
                    //cout << "O" << endl;

                    JUEGO = FINALIZADO;
                    return 2;
                }
            }
        }
    }
    return 0;
}

void configurarTabla() {
    cout << "\t\033[0;33m*************************\033[0m" << endl;
    cout << "\t\033[0;33m------CONFIGURACIÓN------\033[0m" << endl;
    cout << "\t\033[0;33m*************************\033[0m" << endl;
    cout << "\t\033[0;33m------\\ N EN RAYA //------\033[0m" << endl;
    cout << "\t\033[0;33m*************************\033[0m" << endl;
    cout << endl;
    cout << "\033[0;36m-----CANTIDAD DE CARACTERES N°-----\033[0m" << endl;
    cout << endl;
    cout << "\033[0;36m << Ingrese Cantidad N°>>" << endl;
    cin>>NCaracteres;
    cout << "\033[0;36m----------TAMAÑO DE TABLA----------" << endl;
    cout << endl;
    cout << " << Ingrese N° FILAS>>" << endl;
    cout << " >> ";
    cin>>filaTablero;
    cout << " << Ingrese N° COLUMNAS>>" << endl;
    cout << " >> \033[0m";
    cin>>columnaTablero;

    ultimaFila = filaTablero - 1;
    system("clear");
}

void pintadoTabla() {
    system("clear");
    cout << "\t\033[0;33m*************************\033[0m" << endl;
    cout << "\t\033[0;33m------\\ " << NCaracteres << " EN RAYA //------\033[0m" << endl;
    cout << "\t\033[0;33m*************************\033[0m" << endl;
    cout << endl;

    //cout << "\033[0;36mbold red text\033[0m";
    if (turno == 0) {
        cout << "\t\033[0;36m---TURNO 1° JUGADOR (X)---\033[0m";
    } else {
        cout << "\t\033[0;36m---TURNO 2° JUGADOR (O)---\033[0m";
    }
    cout << endl;
    cout << endl;


    cout << "\033[0;33mBUSCANDO " << NCaracteres << " CARÁCTERES IGUALES\033[0m" << endl;
    if (numIngreso == 0) {
        cout << "\033[0;33mPOSICIÓN ELEGIDA ...\033[0m" << endl;
    } else {
        cout << "\033[0;33mPOSICIÓN ELEGIDA [" << ultimaFila + 1 << " , " << numIngreso << "]\033[0m" << endl;
    }

    cout << endl;

    cout << "  \033[0;35m|\033[0m";

    //Cabecera del recuadro
    for (int i = 1; i < columnaTablero + 1; i++) {

        if (i < 10) {
            cout << "\033[0;35m0" << i;
            cout << "|\033[0m";

        } else {
            cout << "\033[0;35m" << i;
            cout << "|\033[0m";
        }

    }
    cout << endl;

    //Mostramos la matriz
    for (int i = 0; i < filaTablero; i++) {

        if (i + 1 < 10) {
            cout << "\033[0;35m0" << i + 1 << "\033[0m";
            cout << "|";

        } else {
            cout << "\033[0;35m" << i + 1 << "\033[0m";
            cout << "|";
        }


        for (int j = 0; j < columnaTablero; j++) {
            if (tablero[i][j] == "X ") {
                cout << "\033[0;36m" << tablero[i][j] << "\033[0m" << "|";
            } else if (tablero[i][j] == "O ") {
                cout << "\033[0;32m" << tablero[i][j] << "\033[0m" << "|";
            } else {
                cout << "  |";
            }

        }
        cout << "\n";
    }

    cout << endl;
}

void MostrarGanardor(char ganador) {

    if (ganador == 1) {
        cout << endl;
        cout << "\t\033[0;33m***************************\033[0m" << endl;
        cout << "\t\033[0;33m------GANADOR JUGADOR------\033[0m" << endl;
        cout << "\t\033[0;33m------------[X]------------\033[0m" << endl;
        cout << "\t\033[0;33m***************************\033[0m" << endl;
    }
    if (ganador == 2) {
        cout << endl;
        cout << "\t\033[0;32m***************************\033[0m" << endl;
        cout << "\t\033[0;32m------GANADOR JUGADOR------\033[0m" << endl;
        cout << "\t\033[0;32m------------[O]------------\033[0m" << endl;
        cout << "\t\033[0;32m***************************\033[0m" << endl;
    }
}

void insertarValor() {

    if (turno == 0) {
        tablero[ultimaFila][numIngreso - 1] = "X ";
        turno = 1;

    } else {
        tablero[ultimaFila][numIngreso - 1] = "O ";
        turno = 0;
    };

    pintadoTabla();
    MostrarGanardor(ValidarGanador());

    cout << endl;
}

void verificarLugarVacio() {
    //Verifica si se encuentra ocupado
    ultimaFila = filaTablero - 1;

    while (true) {

        if (ultimaFila < 0) {
            pintadoTabla();
            cout << " \033[0;31m<< ¡COLUMNA LLENA... ELIJA OTRA! >>\033[0m" << endl;
            break;
        } else {
            if (tablero[ultimaFila][numIngreso - 1] == "X " || tablero[ultimaFila][numIngreso - 1] == "O ") {
                //Sube una fila si encuentra lleno el sitio
                ultimaFila--;

            } else {
                insertarValor();
                break;
            }
        }
    }
}

void iniciarJuego() {
    //Se ejecuta el juego hasta que cambie a estado uno
    while (JUEGO == INICIALIZADO) {

        cout << " \033[0;36m<< INGRESE UN NÚMERO DE COLUMNA >>\033[0m" << endl;
        cout << endl;
        cin>>numIngreso;

        if (numIngreso - 1 < columnaTablero && numIngreso - 1 >= 0) {
            verificarLugarVacio();
        } else {
            pintadoTabla();
            cout << " \033[0;31m<< ¡NÚMERO FUERA DE RANGO! >>\033[0m" << endl;
            JUEGO = INICIALIZADO;

        }
    }
}

int main() {

    configurarTabla();
    creandoTabla();
    pintadoTabla();
    iniciarJuego();

    return 0;

}

