#include <iostream>
#include <mosquittopp.h>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>

struct empleado{
    std::string nombre;
    std::string apellido;
    std::string departamento;
    std::string lugar_grado;
};

struct equipos{
    std::string marca;
    int ram;
};

class MQTTPublisher : public mosqpp::mosquittopp {
public:
    std::atomic<bool> conectado {false}; //Alzamos un Semaforo atomico para que no leamos en el main un dato corrupto
    // dado que lo editamos en on_conect(), de esta manera, nos aseguramos que main leera una vez que on_conect() termine de escribir.

    MQTTPublisher(const char* id, const char* host, int port)
        : mosquittopp(id)
     {
        connect(host, port, 60);
    }

    void on_connect(int rc) override {
        if (rc == 0) {
            std::cout << "Conectado al broker\n";
            conectado = true;  
        } else {
            std::cout << "Error de conexion: " << rc << "\n";
        }
    }

    void on_publish(int mid) override {
        std::cout << "Mensaje publicado (mid=" << mid << ")\n";
    }
};

int main() {
    mosqpp::lib_init();

    MQTTPublisher pub("publisher-01", "localhost", 1883);
    pub.loop_start(); 

    int intentos=0;
    while(!pub.conectado && intentos < 10){
        std::this_thread::sleep_for(std::chrono::seconds(5));
        intentos++;
    }

    if(!pub.conectado){
        std::cout<< "No se pudo conectar al Broker con\n";
        pub.loop_stop();
        mosqpp::lib_cleanup();
        return 1;
    }

    //vector->array que se expande solo
    std::vector<empleado>empleados={
        {"Mikel","Zamalloa","Tecnologia","EHU/UPV"},
        {"Mikel","Zamalloa","Tecnologia","EHU/UPV"},
        {"Pedro","Romayor","Tecnologia","EHU/UPV"},
        {"Aitor","Basterretxea","Tecnologia","Deusto"},
        {"Markel","Fernandez","Tecnologia","EHU/UPV"},
        {"Unai","Rodriguez","Tecnologia","EHU/UPV"}
    };

    std::vector<equipos>equipo={
        {"Lenovo", 32},
        {"Dell", 64},
        {"Lenovo", 32},
        {"Lenovo", 64},
        {"Lenovo", 16}
    };

    for(const empleado& i:empleados){ //como solo vamos a leer, const//& es mas rapido que sin el, de esa maner no copiamos el elemento
        std::string payload = i.nombre+" "+i.apellido+", "+i.departamento+", "+i.lugar_grado;
        pub.publish(nullptr,"empresa/empleados",payload.size(),payload.c_str());
        std::cout << "Publicando: " << payload << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 1s entre cada uno
    }

    for(const equipos& i:equipo){
        std::string payload=i.marca+", "+std::to_string(i.ram)+"GB Ram";
        pub.publish(nullptr,"empresa/empleados/equipos", payload.size(),payload.c_str());
        std::cout<<"Publicando: "<< payload << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    pub.loop_stop();
    mosqpp::lib_cleanup();
    return 0;
}