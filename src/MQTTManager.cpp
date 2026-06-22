#include "MQTTManager.h"
#include <iostream>
#include <cstdlib>

bool MQTTManager::isRunning(){
    std::cout<<"\nComprobando que el mosquitto y el suscriptor funcionan correctamente...\n";
    
    FILE* pipe = popen("pgrep -x subscriber", "r");
    if(!pipe) return false;
    char buf[256];
    bool subscriber_ok = fgets(buf, sizeof(buf), pipe) != nullptr; //Condicion, de que no sea un puntero libre, es decir, que haya algo que leer.
    pclose(pipe);

    FILE* pipe_M = popen("pgrep -x mosquitto", "r");
    if(!pipe_M) return false;
    bool mosquitto_ok = fgets(buf, sizeof(buf), pipe_M) != nullptr;
    pclose(pipe_M);

    if(!mosquitto_ok) {
        std::cout << "Mosquitto no está corriendo. Arráncalo primero.\n";
        return false;
    }

    return subscriber_ok && mosquitto_ok;
}

void MQTTManager::stop() {
    system("pkill -f subscriber");
    std::cout << "Subscriber detenido.\n";
}

void MQTTManager::start() {
    if (isRunning()) { // comprobamos a traves del PID
        std::cout << "Ya hay una instancia corriendo.\n";
        return;
    }

    std::cout << "\nInicializando publisher y subscriber...\n";
    system("make all");
    system("./subscriber &");
    system("./publisher > /dev/null 2>&1 &");

    char tecla;
    std::cout << "(Pulsa 'Q' para volver al menu)\n";
    while (std::cin >> tecla) {
        if (tecla == 'Q' || tecla == 'q') {
            stop();
            break;
        }
    }
}