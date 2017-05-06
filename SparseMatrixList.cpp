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



string SparseMatrixList::countUsed() {
  //Primero necesitaremos un arreglo para almacenar todos los numeros de las matrices, para no sobredimensionar
  // calcularemos el maximo tamaño posible que puede tomar, esto es, en un caso que todas las matrices esten llenas de
  //numeros distintos
  int maxSize = 0;
  for( int i = 0; i < this->size; i++){
      maxSize += (this->array[i]->maxColumn * this->array[i]->maxRow);
  }// Fin for de las matrices de la lista   
  
  /* Ahora crearemos una matriz con este diseño
  
        [0][4][6][8][12][20]  ----- > Numero encontrado en las matrices 
        [1][1][2][3][1][10]  ------> Numero de veces que se repite en las matrices
  */
  int valueArray[2][maxSize];
  int sizeCount = 0;
  
  //realizamos la operacion para cada una de las matrices en la lista
    
  //for para cada matriz de la lista
  for( int j = 0; j<this->size; j++){
      
  //for para cada fila de la matriz
    for (int i = 1; i <= this->array[j]->maxRow; i++) {
          MatrixTerm* aux = this->array[j]->AROW[i]->left;
            //Recorremos la fila para guardar los valores
            while (aux->column != 0) {
                //agregamos el dato a nuestro vector
                //primero comprobamos si el valor ya existe
                bool found = false;
                for(int z = 0; z<sizeCount;z++){
                    if(valueArray[0][z] == aux->dato){
                    // se encontro el dato por lo que se suma su contador
                    found = true;
                    valueArray[1][z]++;
                    break;
                    }
                }
                //Si el valor no se encontro, se agrega
                valueArray[0][sizeCount] = aux->dato;
                sizeCount++;
                aux = aux->left;
            }//fin while de la fila
    }//fin for filas
  }//fin for matrices 
 
    
  //Revisamos si se encontraron valores, si no los hay se retorna el mensaje correspondiente
    
  if(sizeCount==0) return "No hay ningun valor distinto de 0 en la matriz para desplegar los valores mas y menos repetidos";
    
  //Con nuestro array hecho, buscaremos los numeros que mas y menos se usan en las matrices
  int mostUsed = 0;
  int mostUsedPos = -1;
  int leastUsed = 0;
  int leastUsedPos = -1;
  
  //Recomerros la matriz que creamos
  for(int i = 0; i<sizeCount;i++){
    //Revisamos si es el menor o el mayor usado
    if(valueArray[1][i] > mostUsed){
        mostUsed = valueArray[1][i];
        mostUsedPos = i;
    }
    if(valueArray[1][i] < leastUsed){
        leastUsed = valueArray[1][i];
        leastUsedPos = i;
    }
  }//fin for buscador mas y menos usado
  
  //retornamos los 2 valores pedidos
  stringstream ss;
  ss << "El valor mas repetido en todas las matrices es: " << valueArray[0][mostUsedPos] << ", que se repite "
     << mostUsed << " veces.\n" << "El valor menos repetido en todas las matrices es: "
     << valueArray[0][leastUsedPos] << ", que se repite" << leastUsed << " veces." << endl;
  return ss.str();
    
}//fin metodo
