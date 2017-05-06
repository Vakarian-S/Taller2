/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MatrixTerm.cpp
 * Author: Sebastian
 * 
 * Created on May 3, 2017, 6:50 PM
 */

#include "MatrixTerm.h"

MatrixTerm::MatrixTerm() {
    this->column = 0;
    this->row = 0;
    this->dato = 0;
}

MatrixTerm::MatrixTerm(int dato, int row, int column) {
    this->dato = dato;
    this->row = row;
    this->column = column;
}


MatrixTerm::MatrixTerm(const MatrixTerm& orig) {
    this->dato = orig.dato;
    this->row = orig.row;
    this->column = orig.column;
}

MatrixTerm::~MatrixTerm() {
}

