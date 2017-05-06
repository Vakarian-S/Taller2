/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainMenu.cpp
 * Author: Sebastian
 * 
 * Created on May 3, 2017, 10:48 PM
 */

#include "MainMenu.h"

MainMenu::MainMenu() {
}

MainMenu::MainMenu(const MainMenu& orig) {
}

MainMenu::~MainMenu() {
}

void MainMenu::start() {
    bool end = false;
    while (end != true) {
        cout << ".: Manejo de Matrices :." << "\n\n"
                << "Eliga una opcion:\n" << "[1] Desplegar Matrices.\n[2] Estadisticas.\n[3] Sumar Matrices.\n[4] Restar Matrices\n"
                << "[5] Correr valores de una matriz.\n[6] Salir." << endl;
        char seleccion = 'x';
        string lectura;
        cin >> lectura;
        if (lectura.length() == 1) seleccion = lectura[0];
        switch (seleccion) {
            case '1':
            {
                break;
            }
            case '2':
            {

                break;
            }
            case '3':
            {

                break;
            }
            case '4':
            {

                break;
            }
            case '5':
            {
                end = true;
                break;
            }
            default:
            {
                cout << "Valor ingresado no es valido" << endl;
                break;
            }
        }
    }
}


