#include "Logger.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

void Logger::show(){
    std::cout<<"\nMostrando los logs del mosquitto...\n";
    #ifdef __APPLE__
    system("sudo cat /usr/local/var/log/mosquitto.log\n");
    #else
    system("sudo cat /var/log/mosquitto/mosquitto.log\n");
    #endif

}

void Logger::exportToFile(){
    std::ofstream archivo("logs_mosquitto.txt");
    #ifdef __APPLE__
    FILE* pipe=popen("sudo cat /usr/local/var/log/mosquitto.log", "r");
    #else
    FILE* pipe=popen("sudo cat /var/log/mosquitto/mosquitto.log", "r");
    #endif
    if(!pipe) return;

    char buf[256];
    while(fgets(buf,sizeof(buf),pipe)!=nullptr){
        archivo << buf; // escribe cada línea en el archivo
    }

    pclose(pipe);
    archivo.close();
    std::cout << "Logs exportados a logs_mosquitto.txt\n";

}