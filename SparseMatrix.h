/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SparseMatrix.cpp
 * Author: Sebastian
 * 
 * Created on May 3, 2017, 6:53 PM
 */

#include <stack>
#include <queue>

#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(string name,int n) {
    this->construct(n,n);
    this->name = name;
}


SparseMatrix::SparseMatrix(string name,int m, int n) {
    this->construct(m,n);
    this->name = name;
}




void SparseMatrix::construct(int rows, int columns) {
    this->maxColumn = columns;
    this->maxRow = rows;
    //Creamos vectores para los limites  y los rellenamos
    this->AROW = new MatrixTerm*[rows+1];
    this->ACOL = new MatrixTerm*[columns+1];
    for(int i = 0; i<=rows;i++){
        MatrixTerm* n = new MatrixTerm();
        n->row = i;
        n->left = n;
        AROW[i] = n;
    }
    for(int i = 0; i<=columns;i++){
        MatrixTerm* n = new MatrixTerm();
        n->column = i;
        n->up = n;
        ACOL[i] = n;
    }
    
}

bool SparseMatrix::exists(int m, int n) {
    MatrixTerm* aux = AROW[m]->left;
    //Recorremos la matriz hasta encontrar algun valor en la posicion dada
    while(aux->column != 0 || aux->column != n){
        aux = aux->left;
    }
    if(aux->column == 0) return 0;
    return 1;
}

void SparseMatrix::add(MatrixTerm* nodo) {
    //Si esa fila esta vacia
    int m = nodo->row;
    int n = nodo->column;
    if(AROW[m]->left == AROW[m]){
        AROW[m]->left = nodo;
        nodo->left = AROW[m];
    }else{
        //La fila no esta vacia y se tiene que recorrer
        MatrixTerm* aux = AROW[m];
        //Buscamos hasta que encontremos el objeto en una columna que no sea inferior a la que buscamos
        //osea tenemos que dejar el nuevo nodo a la derecha de algun valor que este en una columna menor
        while (aux->left->column > nodo->column) {
            aux = aux->left;
        }
        //Meteremos el nodo entre 2 variables, aux y el izquierdo de aux, asi que guardaremos el izquierdo del aux actual
        MatrixTerm* aux2 = aux->left;
        //Ahora insertamos el dato entre medio
        aux->left = nodo;
        nodo->left = aux2;


    }//Fin if agregar en fila
    
    //Si la columna esta vacia
    if (ACOL[n]->up == ACOL[n]){
        ACOL[n]->up = nodo;
        nodo->up = ACOL[n];
    }else{
        //La Columna no esta vacia y se tiene recorrer
          MatrixTerm* aux = ACOL[n];
        //Buscamos hasta que encontremos el objeto en una fila que no sea inferior a la que buscamos
        //osea tenemos que dejar el nuevo nodo abajo de algun valor que este en una filamenor
        while (aux->up->row > nodo->row) {
            aux = aux->up;
        }
        //Meteremos el nodo entre 2 variables, aux y el superior de aux, asi que guardaremos el superior del aux actual
        MatrixTerm* aux2 = aux->up;
        //Ahora insertamos el dato entre medio
        aux->up = nodo;
        nodo->up = aux2;
    }//Fin if insertar en columna
      
}

void SparseMatrix::display()    {
    // Como recorremos las filas de atras para adelante, el display quedara inverso al recorrer, por lo que cada impresion
    // la guardaremos en un stack para que las filas tengan su orden correcto
    
    for(int i = 1; i <= this->maxRow; i++){
        //Vamos a crear un arreglo que guarde las casillas a imprimir, ya que estas se guardaran en orden inverso debido
        //al formato de recorrido de las matrices poco pobladas
            string impresion[this->maxColumn];
            //tamaño de este arreglo
            int impresionSize = 0;
            MatrixTerm* aux = AROW[i]->left;
            // Contamos la diferencia entre el maximo de columnas y el nodo a la izquierda del AROW para rellenar con 0
            int diferencia =  this->maxColumn - aux->column;
            for (int i = 0;i<diferencia;i++){
                impresion[impresionSize] = "[0]";
                impresionSize++;
        }
        //Si esa fila esta vacia no debemos de imprimir el aux porque quedara en el AROW
        if (aux->column != 0) {
            stringstream ss;
            ss << "[" << aux->dato << "]";
            impresion[impresionSize] = ss.str();
            impresionSize++;
        }
        //ahora contaremos la diferencia entre las columnas de los nodos para rellenar con 0
        while (aux->column != 0) {
            diferencia = aux->column - aux->left->column-1;
            for (int i = 0; i < diferencia; i++) {
                 impresion[impresionSize] = "[0]";
                 impresionSize++;
            }
            if (aux->left->column != 0) {
                stringstream ss;
                ss << "[" << aux->left->dato << "]";
                impresion[impresionSize] = ss.str();
                impresionSize++;
            }
            aux = aux->left;
        }
         // ahora imprimimos todo lo guardado por el arreglo de manera inversa
        for(int j = impresionSize-1; j >= 0; j--){
            cout << impresion[j];

        }
            cout << endl;
    }// fin for de filas
}



    
    




SparseMatrix::SparseMatrix(const SparseMatrix& orig) {
}

SparseMatrix::~SparseMatrix() {
    delete ACOL;
    delete AROW;
}

