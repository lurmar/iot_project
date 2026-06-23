#include <iostream>
#include <unistd.h>
#include "MQTTManager.h"
#include "Logger.h"
#include "Menu.h"
#include "Watcher.h"
#include "Colores.h"

int main(){
    MQTTManager mqtt;
    Logger log;
    Menu menu;

    pid_t pid = fork();
    if(pid == 0){
        Watcher watcher;
        watcher.start();
        exit(0);
    }

    while(true){
        menu.display();
        int opcion = menu.getOption();
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
            case 4:{
                std::string modelo;
                std::cout << "\nQue modelo de IA tienes en local?: ";
                std::cin >> modelo;
                std::string comando = "ollama run " + modelo;
                system(comando.c_str());
                break;
            }
            case 0: exit(0);
            default:
                std::cout << RED << "Opción no válida.\n" << RESET;
                break;
        }
    }
}