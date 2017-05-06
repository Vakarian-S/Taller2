/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SparseMatrixList.cpp
 * Author: Sebastian
 * 
 * Created on May 3, 2017, 11:05 PM
 */

#include "SparseMatrixList.h"

SparseMatrixList::SparseMatrixList() {
    this->size = 0;
}

SparseMatrixList::SparseMatrixList(const SparseMatrixList& orig) {
}

SparseMatrixList::~SparseMatrixList() {
}

void SparseMatrixList::push(SparseMatrix* data) {
    this->array[size] = data;
    this->size++;
}

void SparseMatrixList::createMatrix() {
    cout << ".: Creación de matrices :.-" << endl;
    bool fin = false;
    do {
        cout << "Desea crear matrices a mano?\n[1]Si\n[2]No" << endl;
        char selection = 'x';
        string read;
        cin >> read;
        if (read.length() == 1) selection = read[0];
        switch(selection){
            case '1':
            {
                
            }
            case '2':
            {
                
            }
            default:
            {
                cout << "El valor ingresado no es valido, intente nuevamente" << endl;
                fin = false;
                break;
            }
        }//fin switch
        
    }while(fin==false);
    
}

SparseMatrix* SparseMatrixList::displace(SparseMatrix* target) {
    // Como editar todos los punteros es un trabajo engorroso, utilizaremos el codigo ya implementado para añadir nodos y simplemente
    // crearemos una nueva matriz ingresando todos los valores de la antigua matriz nuevamente pero con las filas y columnas editadas
    // por lo tanto guardaremos todos los datos de la matriz original en un vector, borramos la antigua matriz, y creamos una nueva
    // matriz con el mismo nombre e ingresamos todos los datos almacenados en el vector.

    //La maxima cantidad de datos que puede almacenar el vector sera la maxima cantidad de nodos que puede tener la matriz
    MatrixTerm * termBox[target->maxRow * target->maxColumn];
    int boxSize = 0;
    //Ahora tomaremos cada nodo, le editamos su fila y columna y lo insertamos en nuestra "caja"

    for (int i = 1; i <= target->maxRow; i++) {
        MatrixTerm* aux = target->AROW[i]->left;
        //Recorremos la fila para guardar los valores
        while (aux->column != 0) {
            // Ahora editaremos la columna del dato para que sea 1 mas a la derecha,
            //comprobamos si es la esquina inferior derecha
            if (aux->column == target->maxColumn && aux->row == target->maxRow) {
                aux->row = 1;
                aux->column = 1;
            } else {
                //revisamos si es un extremo derecho
                if (aux->column == target->maxColumn) {
                    aux->column = 1;
                    aux->row = aux->row + 1;
                } else {
                    //si ninguno de los casos anteriores se cumple significa que es un nodo que no esta en ningun extremo derecho
                    aux->column = aux->column + 1;
                }
            }//fin if
            //agregamos el dato a nuestro vector
            termBox[boxSize] = aux;
            boxSize++;
            aux = aux->left;
        }//fin while de la fila

    }//fin for filas

    //Una vez agregados todos los datos, construimos una nueva matriz con los datos con posiciones cambiadas
    SparseMatrix* newMatrix = new SparseMatrix(target->name,target->maxRow,target->maxColumn);
    for(int x = 0; x<boxSize;x++){
        newMatrix->add(termBox[x]);
    }
    // Con la matriz nueva creada retornamos la nueva matriz y eliminamos la vieja matriz
    delete target;
    return newMatrix;
}
