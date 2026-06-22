#include "Menu.h"
#include "Colores.h"
#include <iostream>
#include <cstdlib>

void Menu::display(){
        std::cout << BOLD << CYAN << "\n\tGestión de Servicios\n" << RESET;
        std::cout << GREEN << "1." << RESET << " Inicializar prueba con subscriber y publisher\n";
        std::cout << GREEN  << "2." << RESET << " Ver los logs del mosquitto\n";
        std::cout << GREEN  << "3." << RESET << " Parsear los logs del mosquitto a un .txt\n";
        std::cout << GREEN<< "4." << RESET << " Hablar con una IA local\n";
        std::cout << RED   << "0." << RESET << " Salir\n";
        std::cout<<"\nTeclee la opcion deseada: ";
}

int Menu::getOption(){
    int opcion;
    if(!(std::cin >> opcion)){ //Intenta leer un int
        std::cin.clear(); //Reseteamos el cin para que no se quede en estado "roto"
        std::cin.ignore(1000, '\n');
        return -1;  //numero invalido, el default del switch lo captura
    }
    std::cin.ignore(1000, '\n');
    return opcion;
}