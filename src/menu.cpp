#include<iostream>
#include<math.h>
#include "MQTTManager.h"
#include "Logger.h"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

int main (){

MQTTManager mqtt;
Logger log;

    while(true){
        int opcion;
        std::cout << BOLD << CYAN << "\n\tGestión de Servicios\n" << RESET;
        std::cout << GREEN << "1." << RESET << " Inicializar prueba con subscriber y publisher\n";
        std::cout << GREEN  << "2." << RESET << " Ver los logs del mosquitto\n";
        std::cout << GREEN  << "3." << RESET << " Parsear los logs del mosquitto a un .txt\n";
        std::cout << GREEN<< "4." << RESET << " Hablar con una IA local\n";
        std::cout << RED   << "0." << RESET << " Salir\n";
        std::cout<<"\nTeclee la opcion deseada: ";
        std::cin>>opcion;

        switch(opcion){
            
            case 1:
            mqtt.start();
            break;

            case 2:
            log.show();
            break;

            case 3:
            log.exportToFile();
            break;

            case 4:{ //las lllaves necesarias para que las variables solo sean de esta case
            std::string modelo;
            std::cout<<"\nQue modelo de IA tienes en local?:";
            std::cin>>modelo;
            std::string comando="ollama run "+modelo;
            system(comando.c_str()); //sytem necesita un char*, c_str hace esa conversion
            break;
            }

            default: //pa numeros incorrectos
            std::cout << RED << "Opción no válida.\n" << RESET;
            break;
            
            case 0: exit(0);

        }
    }
}