#include<iostream>
#include<math.h>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

void ini_sub_pub(){
    std::cout<<"\nInicializando el pub y el sub...";
    system("make all"); //system() ejecuta comandos en el terminal
    system("./subscriber &"); //Si quisieramos abrir una terminal indep. delante pondriamos "xterm -e"; &= para que el subscriber no bloquee
    system("./publisher > /dev/null 2>&1 &"); //> /dev/null — oculta la salida normal, 2>&1 — oculta también los errores, & — en segundo plano

    char tecla;
    std::cout<<"(Pulsa 'Q' para volver al menu)\n";
    while(std::cin>>tecla){
    if(tecla == 'Q' || tecla == 'q') {
        system("pkill -f subscriber");
        break;  //sale del while y vuelve al menú
        }
    }
}

int main (){

    while(true){
        int opcion;
        std::cout << BOLD << CYAN << "\n\tEvSare — Gestión de Servicios\n" << RESET;
        std::cout << GREEN << "1." << RESET << " Inicializar prueba con subscriber y publisher\n";
        std::cout << CYAN  << "2." << RESET << " Ver los logs del mosquitto\n";
        std::cout << YELLOW<< "3." << RESET << " Hablar con una IA local\n";
        std::cout << RED   << "0." << RESET << " Salir\n";
        std::cout<<"\nTeclee la opcion deseada: ";
        std::cin>>opcion;

        switch(opcion){
            
            case 1:
            ini_sub_pub();
            break;

            case 2:
            std::cout<<"\nLos logs del mosquitto son los siguientes->\n";
            #ifdef __APPLE__
            system("sudo cat /usr/local/var/log/mosquitto.log\n");
            #else
            system("sudo cat /var/log/mosquitto/mosquitto.log\n");
            #endif
            break;
            
            case 0: exit(0);

        }
    }
}