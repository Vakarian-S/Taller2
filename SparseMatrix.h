/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SparseMatrix.h
 * Author: Sebastian
 *
 * Created on May 3, 2017, 6:53 PM
 */

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include "MatrixTerm.h"
#include <iostream>
#include <sstream>
#include <string>

class SparseMatrix {
public:
    MatrixTerm** ACOL;
    MatrixTerm** AROW;
    int maxRow, maxColumn;
    string name;
    void construct(int rows, int columns);
    bool exists(int m, int n);
    void add(MatrixTerm* dato);
    void display();
    void displace();
    SparseMatrix(string name,int n);
    SparseMatrix(string name,int m, int n);
    SparseMatrix(const SparseMatrix& orig);
    virtual ~SparseMatrix();
private:

};

#endif /* SPARSEMATRIX_H */

