/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SparseMatrixList.h
 * Author: Sebastian
 *
 * Created on May 3, 2017, 11:05 PM
 */

#ifndef SPARSEMATRIXLIST_H
#define SPARSEMATRIXLIST_H

#include "SparseMatrix.h"


class SparseMatrixList {
public:
    SparseMatrix* array[100];
    int size;
    void createMatrix();
    void importMatrix();
    void push(SparseMatrix* data);
    SparseMatrix* displace(SparseMatrix* target);
    SparseMatrixList();
    SparseMatrixList(const SparseMatrixList& orig);
    virtual ~SparseMatrixList();
private:

};

#endif /* SPARSEMATRIXLIST_H */

