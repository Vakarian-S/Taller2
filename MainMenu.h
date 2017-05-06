/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainMenu.h
 * Author: Sebastian
 *
 * Created on May 3, 2017, 10:48 PM
 */

#ifndef MAINMENU_H
#define MAINMENU_H
#include <iostream>

using namespace std;
class MainMenu {
public:
    MainMenu();
    MainMenu(const MainMenu& orig);
    void start();
    virtual ~MainMenu();
private:

};

#endif /* MAINMENU_H */

