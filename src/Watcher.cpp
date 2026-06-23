#include <iostream>
#include <cstdlib>
#include <sys/inotify.h> 
#include <unistd.h>
#include "Watcher.h"

void Watcher::start(){
    int fd = inotify_init();
    if(fd < 0){
        std::cout << "Error al inicializar inotify.\n";
        return;
    }

    int wd = inotify_add_watch(fd, "/etc/mosquitto/mosquitto.conf", IN_MODIFY);
    if(wd < 0){
        std::cout << "Error al vigilar el fichero.\n";
        return;
    }
    std::cout << "Vigilando mosquitto.conf...\n";

    char buffer[1024];
    while(true){
        int n = read(fd, buffer, sizeof(buffer));
        if(n < 0){
            std::cout << "Error al leer evento.\n";
            break;
        }
    std::cout << "Cambio detectado en mosquitto.conf, enviando email...\n";
    system("{ echo 'Subject: Alerta: mosquitto.conf modificado'; echo 'From: lurmarasti@gmail.com'; echo ''; echo 'Fecha:'; date; echo ''; echo 'Contenido actual:'; cat /etc/mosquitto/mosquitto.conf; } | msmtp --file=/home/lurmar/.msmtprc lurmarasti@gmail.com");
    }   
}