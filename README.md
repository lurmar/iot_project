# mqtt_project 
 
Herramienta de gestión interactiva para servicios MQTT/OCPP. Permite lanzar pruebas de comunicación, consultar logs del broker y (próximamente) interactuar con una IA local.
 
---
 
## Estructura del repositorio
 
```
mqtt_project/
├── src/                # Carpeta con todos los codigos
    ├── menu.cpp        # Menú interactivo principal
    ├── subscriber.cpp  # Cliente MQTT subscriber
    ├── publisher.cpp   # Cliente MQTT publisher
    ├── Makefile        # Compilación del proyecto
├── certificados/       # Certificados TLS (ver README interno)
└── mi-mosquitto.tar    # Mi contenedor de mosquitto
```
 
---
 
## Requisitos
 
- `g++` con soporte C++17
- `libmosquitto-dev` y `libmosquittopp-dev`
- Mosquitto instalado y activo en el sistema
```bash
sudo apt install g++ libmosquitto-dev libmosquittopp-dev mosquitto mosquitto-clients
```
 
---
 
## Compilación
 
```bash
make all
```
 
O individualmente:
 
```bash
g++ -std=c++17 -o menu menu.cpp
g++ -std=c++17 -o subscriber subscriber.cpp -lmosquitto
g++ -std=c++17 -o publisher publisher.cpp -lmosquitto
```
 
---
 
## Uso
 
```bash
./menu
```
 
### Opciones del menú
 
| Opción | Descripción |
|--------|-------------|
| `1` | Compila y lanza subscriber y publisher (segundo plano)  |
| `2` | Muestra los logs de Mosquitto |
| `3` | Chat con IA local — *próximamente* |
.
.
.
| `0` | Salir |
 
**Para detener el subscriber:** pulsa `Q` desde el menú.
 
---
 
## Mosquitto
 
Actualmente Mosquitto corre instalado directamente en el sistema. Los logs se encuentran en:
 
- **Linux:** `/var/log/mosquitto/mosquitto.log`
- **macOS:** `/usr/local/var/log/mosquitto.log`
### Containerización (pendiente)
 
Se containerizará Mosquitto con la configuración personalizada. La imagen base ya existe (`mi-mosquitto.tar`) pero requiere ser reconstruida para arquitectura `amd64`. (Pendiente de reconstruccion, solo sirve para arm)
 
---
 
## Próximas funcionalidades
 
- [ ] Chat con IA local mediante Ollama con contexto de EvSare
- [ ] Containerización de Mosquitto (Docker)
- [ ] Visualización de logs del proxy-OCPP
- [ ] Gestión de sesiones OCPP desde el menú
---
 
## Certificados
 
Ver `certificados/README.md` para la configuración TLS.