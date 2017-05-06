/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MatrixTerm.h
 * Author: Sebastian
 *
 * Created on May 3, 2017, 6:50 PM
 */

#ifndef MATRIXTERM_H
#define MATRIXTERM_H

using namespace std;
class MatrixTerm {
public:
    int dato, row, column;
    MatrixTerm* left = nullptr;
    MatrixTerm* up = nullptr;
    MatrixTerm();
    MatrixTerm(int dato, int row, int column);
    MatrixTerm(const MatrixTerm& orig);
    virtual ~MatrixTerm();
private:

};

#endif /* MATRIXTERM_H */

