#include <iostream>
#include <mosquittopp.h>
#include <set>
#include <string>
#include <csignal>
#include <chrono>
#include <thread>

class MQTTClient : public mosqpp::mosquittopp {
private:
    struct TopicData{
        std::string topic;
        std::string payload;
    }t;

    std::set<std::string> empleadosVistos;
public:
    MQTTClient(const char* id, const char* host, int port)
        : mosquittopp(id)
    {
        connect(host, port, 60);
    }

    void on_connect(int rc) override {
        if (rc == 0) {
            std::cout << "Conectado al broker\n";
            subscribe(nullptr, "empresa/#");
        } else {
            std::cout << "Error de conexion rc=" << rc << ": " << mosquitto_connack_string(rc) << "\n";
        }
    }

    void on_message(const struct mosquitto_message* msg) override {
        TopicData t;
        t.topic   = msg->topic;
        t.payload = std::string((char*)msg->payload, msg->payloadlen);

        if (t.topic == "empresa/empleados") {

            auto resultado = empleadosVistos.insert(t.payload);

            if (resultado.second) {
                std::cout << "{\n";
                std::cout << "  \"topic\":   \"" << t.topic   << "\",\n";
                std::cout << "  \"payload\": \"" << t.payload << "\"\n";
                std::cout << "}\n";
            } else {
                std::cout << "Nombre repetido en /empleados: " << t.payload << " (descartado)\n";
            }
        } else {
            std::cout << "{\n";
            std::cout << "  \"topic\":   \"" << t.topic   << "\",\n";
            std::cout << "  \"payload\": \"" << t.payload << "\"\n";
            std::cout << "}\n";
        }
    }   

    void on_subscribe(int mid, int qos_count, const int* granted_qos) override {
        std::cout << "Suscrito correctamente\n";
    }

};

MQTTClient* clienteGlobal = nullptr; //Puntero que apunta a objetos de tipo MQTTClient, nullptr=vacio no apunta a nada aun

void alSalir(int signal) {            
    std::cout<<"Cerrando sesion..."<<"\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    mosqpp::lib_cleanup();
    exit(0);
}

int main() {
    mosqpp::lib_init();
    MQTTClient client("subscriber-01", "localhost", 1883);
    clienteGlobal = &client; //apuntamos al objeto client

    signal(SIGINT, alSalir);

    while (true) {
        client.loop();
    }
}


//const->solo lectura //override->estas diciendo, reemplazo la funcion de la madre con la mia, ademas te avisa si la estas reemplazando bien