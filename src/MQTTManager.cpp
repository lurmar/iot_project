#include "MQTTManager.h"
#include <iostream>
#include <cstdlib>

bool MQTTManager::isRunning(){
    FILE* pipe=popen("pgrep -x subscriber", "r"); //abrimos un pipe ejecuta el comando y luego lo lee "r", pgrep nos da el PID del proceso, "-x" coincidencia exacta debe ser
    if(!pipe) return false;

    char buf[256];
    bool found = fgets(buf,sizeof(buf),pipe)!=nullptr; //intenta leer algo del buf, si leyó algo found es true si no es false (!=nullptr)
    pclose(pipe);

    return found;
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