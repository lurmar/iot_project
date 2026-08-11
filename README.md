# iot_project

![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus)
![MQTT](https://img.shields.io/badge/MQTT-Mosquitto-orange)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-lightgrey)
![Status](https://img.shields.io/badge/Estado-En%20desarrollo-yellow)

Herramienta de gestión interactiva por terminal para servicios MQTT/OCPP. Permite lanzar pruebas de comunicación entre publisher y subscriber, consultar y exportar logs del broker Mosquitto, e interactuar con una IA local mediante Ollama.

---

## Estructura del repositorio

```
mqtt_project/
├── src/
│   ├── menu.cpp            # Punto de entrada, bucle principal
│   ├── Menu.cpp / Menu.h   # Clase: menú interactivo
│   ├── MQTTManager.cpp / MQTTManager.h  # Clase: gestión de publisher/subscriber
│   ├── Logger.cpp / Logger.h            # Clase: logs de Mosquitto
│   ├── Colores.h           # Defines de colores ANSI para la terminal
│   ├── subscriber.cpp      # Cliente MQTT subscriber
│   ├── publisher.cpp       # Cliente MQTT publisher
│   ├── Watcher.cpp / Watcher.h  # Vigilante de cambios en mosquitto.conf (mientras el menu esta en uso)
│   ├── watcher_main.cpp         # Vigilante de cambios en mosquitto.conf (en segundo plano, se necesita modificar el systemd para hacer un archivo que corra 24/7)
│   └── Makefile            # Compilación del proyecto
├── certificados/           # Certificados TLS (ver README interno)
└── mi-mosquitto.tar        # Imagen del contenedor Mosquitto (arm64)
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
cd src/
make all
```

---

## Uso

Asegúrate de que Mosquitto está activo antes de ejecutar:

```bash
sudo systemctl start mosquitto
./menu
```

### Opciones del menú

| Opción | Descripción |
|--------|-------------|
| `1` | Comprueba que Mosquitto está activo, compila y lanza subscriber y publisher en segundo plano |
| `2` | Muestra los logs del broker Mosquitto en tiempo real |
| `3` | Exporta los logs de Mosquitto a `logs_mosquitto.txt` |
| `4` | Abre un chat con una IA local mediante Ollama |
| `0` | Salir |

**Para detener el subscriber:** pulsa `Q` desde dentro de la opción 1.

---

## Arquitectura del proyecto

```
menu (C++)
  ├── MQTTManager → lanza/detiene publisher y subscriber
  │                → comprueba estado de Mosquitto y subscriber via pgrep
  ├── Logger      → muestra y exporta logs de Mosquitto
  └── Menu        → gestiona la entrada del usuario con validación
```

---

## Watcher — Vigilancia de mosquitto.conf

Proceso independiente que monitoriza `/etc/mosquitto/mosquitto.conf` en tiempo real mediante `inotify`. Cuando detecta un cambio manda un email automáticamente con la fecha y el contenido del fichero.

### Requisitos
- `msmtp` instalado y configurado con una cuenta de email

```bash
sudo apt install msmtp
```

### Configurar como servicio del sistema

```bash
sudo nano /etc/systemd/system/iot-watcher.service
```

```ini
[Unit]
Description=IoT Watcher - Vigilancia mosquitto.conf

[Service]
User=TU_USUARIO
ExecStart=/ruta/a/iot_project/src/watcher
Restart=always

[Install]
WantedBy=multi-user.target
```

```bash
sudo systemctl daemon-reload
sudo systemctl enable iot-watcher
sudo systemctl start iot-watcher
```

---

## Mosquitto

Los logs se encuentran en:

- **Linux:** `/var/log/mosquitto/mosquitto.log`
- **macOS:** `/usr/local/var/log/mosquitto.log`

### Containerización (pendiente)

Se containerizará Mosquitto con configuración personalizada. La imagen base ya existe (`mi-mosquitto.tar`) pero está compilada para `arm64` y requiere reconstrucción para `amd64`.

---

## Próximas funcionalidades

- Containerización de Mosquitto con Docker
- Visualización de logs del proxy OCPP
- Gestión de sesiones OCPP desde el menú
- Fichero de configuración externo (broker, puerto, topic)

---

## Certificados TLS

Ver `certificados/README.md` para la configuración TLS.

---

## Autor

**Unai Rodríguez Lozano | lurmar** — [LinkedIn](https://www.linkedin.com/in/unai-rodr%C3%ADguez-lozano-7a1b94404/) | [GitHub](https://github.com/lurmar)
