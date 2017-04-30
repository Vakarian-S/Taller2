#include "SparseMatrix.h"

using namespace std;

SparseMatrix::SparseMatrix(int n){
    this->construct(n,n);
}

SparseMatrix::construct(int row, int column){

    if( row < 1 || columns < 1){
        throw InvalidDimensionsException("Las dimensiones de la matriz no pueden ser cero o negativo.");
    }
    
    this->m = row;
    this->n = column;
    
    
    
    


}
