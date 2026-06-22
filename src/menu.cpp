#include<iostream>
#include<math.h>
#include "MQTTManager.h"
#include "Logger.h"
#include "Menu.h"
#include "Colores.h"


int main (){

MQTTManager mqtt;
Logger log;
Menu menu;

    while(true){
        menu.display();
        int opcion=menu.getOption();
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