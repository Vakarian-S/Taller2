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


SparseMatrix* SparseMatrix::sum(SparseMatrix* matrix1, SparseMatrix* matrix2 , string name){

    //Para la suma de matrices, comenzareos creando la nueva matriz vacia con el tamaño de las matrices sumadas,
    //luego recorreremos la primera matriz, para cada nodo que encontremos en la primera matriz, buscaremos en esa misma fila en la 
    //2da matriz un nodo con la misma columna, si se encuentra, se suman sus datos y se crea un nuevo nodo con este dato, la fila
    //y la columna de los nodos sumados, si no encuentra un nodo igual, lo asume como 0 y el nodo creado sera simplemente un clon
    //del primer nodo,
    
    // una vez hecho esto existe la posibildad que hayan nodos en la 2da matriz que no esten en la primera por lo tanto
    // recorremos todos los nodos de la 2da matriz y por cada nodo buscamos un nodo igual en la primera matriz, como los de la primera
    // matriz ya fueron recorridos buscaremos si el 2do nodo NO tiene un nodo con la misma ubicacion en la primera matriz, 
    // porque sino seria un duplicado, una vez nos aseguremos que no tenga ningun nodo
    // en la misma posicion añadiremos un clon del nodo de la 2da matriz a la nueva matriz creada
    SparseMatrix* matrix3 = new SparseMatrix(name,matrix1->maxRow,matrix2->maxColumn);
    for(int i = 1; i <=matrix1->maxRow ; i++){
        MatrixTerm* aux = matrix1->AROW[i]->left;
        while(aux->column != 0){
            //ahora buscamos su equivalente en la 2da matriz
            MatrixTerm* aux2 = matrix2->AROW[i]->left
            while(aux2->column!=0){
                if(aux2->columna == aux->columna){
                   MatrixTerm* newTerm = new MatrixTerm(aux->dato+aux2->dato,aux->row,aux->column);
                   break;
                }
                aux2 = aux2->left
            }
                //si se recorrio toda la matriz y no se encontro un nodo con la misma posicion se crea un clon de nodo de la 
                //1ra matriz
            if(aux2->column == 0 ){
                 MatrixTerm* newTerm = new MatrixTerm(aux);   
            }
            matrix3->add(newTerm);
            aux = aux->left;
        }//fin while para cada nodo de la 1ra matriz
    }//fin for para cada fila de la primera matriz 
    //Una vez añadidos todos los nodos de la 1ra matriz pasaremos a sumar todos los nodos de la 2da matriz que no tiene un equivalente
    // en la primera matriz
    
    for(int i = 1; i<= matriz2->maxRow;i++){
        MatrixTerm* aux = matrix2->AROW[i]->left;
        while(aux->column != 0){
            //buscamos su equivalente en la primera matriz
            MatrixTerm* aux2 = matrix1->AROW[i]->left;
            while(aux2->column != 0){
                if(aux2->column == aux->column) break;
                aux2 = aux2->left;
            }
            //si se recorrio toda la primera matriz sin encontrar valor equivalente se agrega este nodo a la 3ra matriz
            if(aux2->column == 0){
             MatrixTerm* newTerm = new MatrixTerm(aux);    
             matrix3->add(newTerm);
            }
            aux = aux->left; 
        }//fin while 2da matriz
    }//fin for
    
    return matrix3;
   
}

SparseMatrix* SparseMatrix::substract(SparseMatrix* matrix1, SparseMatrix* matrix2 , string name){

    // Para la resta de matrices haremos un proceso casi identico a la suma solamente que debemos añadir
    // una condicion extra que revise si despues de una resta un nodo queda en 0 por lo que no debera ser creado, como tambien
    // etndremos que tranasformar todos los numeros de la 2da matriz sin equivalente en la primera matriz a negativos
    SparseMatrix* matrix3 = new SparseMatrix(name,matrix1->maxRow,matrix2->maxColumn);
    for(int i = 1; i <=matrix1->maxRow ; i++){
        MatrixTerm* aux = matrix1->AROW[i]->left;
        while(aux->column != 0){
            //ahora buscamos su equivalente en la 2da matriz
            MatrixTerm* aux2 = matrix2->AROW[i]->left
            int difference;
            while(aux2->column!=0){
                
                if(aux2->columna == aux->columna){
                   int difference = aux->dato - aux2->dato
                   if(difference == 0) break;
                   MatrixTerm* newTerm = new MatrixTerm(aux->dato+aux2->dato,aux->row,aux->column);
                   break;
                }
                aux2 = aux2->left
            }//fin while 2
                //si se recorrio toda la matriz y no se encontro un nodo con la misma posicion se crea un clon de nodo de la 
                //1ra matriz
            if(aux2->column == 0 ){
                 MatrixTerm* newTerm = new MatrixTerm(aux);   
            }
            //solo se crea lamatriz si la diferencia de la resta no es 0
            if(difference != 0) matrix3->add(newTerm);
            aux = aux->left;
        }//fin while para cada nodo de la 1ra matriz
    }//fin for para cada fila de la primera matriz 
    //Una vez añadidos todos los nodos de la 1ra matriz pasaremos a sumar todos los nodos de la 2da matriz que no tiene un equivalente
    // en la primera matriz, como son parte de la resta, estos valores seran negativos
    
    for(int i = 1; i<= matriz2->maxRow;i++){
        MatrixTerm* aux = matrix2->AROW[i]->left;
        while(aux->column != 0){
            //buscamos su equivalente en la primera matriz
            MatrixTerm* aux2 = matrix1->AROW[i]->left;
            while(aux2->column != 0){
                if(aux2->column == aux->column) break;
                aux2 = aux2->left;
            }
            //si se recorrio toda la primera matriz sin encontrar valor equivalente se agrega este nodo a la 3ra matriz
            if(aux2->column == 0){
             MatrixTerm* newTerm = new MatrixTerm(0-aux->dato,aux->row,aux->column);    
             matrix3->add(newTerm);
            }
            aux = aux->left; 
        }//fin while 2da matriz
    }//fin for
    
    return matrix3;
   
}
