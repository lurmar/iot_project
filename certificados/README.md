# TLS/SSL con Mosquitto MQTT

## Requisitos

```bash
sudo apt install openssl mosquitto libmosquitto-dev libmosquittopp-dev
```

---

## 1. Generar certificados

```bash
mkdir certificados && cd certificados

# CA (Autoridad Certificadora)
openssl genrsa -out ca.key 2048
openssl req -new -x509 -days 365 -key ca.key -out ca.crt -subj "/CN=MiCA"

# Broker
openssl genrsa -out broker.key 2048
openssl req -new -key broker.key -out broker.csr -subj "/CN=localhost"
openssl x509 -req -days 365 -in broker.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out broker.crt

# Cliente
openssl genrsa -out cliente.key 2048
openssl req -new -key cliente.key -out cliente.csr -subj "/CN=cliente"
openssl x509 -req -days 365 -in cliente.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out cliente.crt
```

Archivos generados:

| Archivo | Descripcion | Secreto |
|---|---|---|
| `ca.key` | Clave privada CA | Si |
| `ca.crt` | Certificado CA | No |
| `broker.key` | Clave privada broker | Si |
| `broker.crt` | Certificado broker | No |
| `cliente.key` | Clave privada cliente | Si |
| `cliente.crt` | Certificado cliente | No |

---

## 2. Configurar Mosquitto

Editar `/etc/mosquitto/mosquitto.conf`:

```conf
listener 1883

listener 8883
cafile   /ruta/certificados/ca.crt
certfile /ruta/certificados/broker.crt
keyfile  /ruta/certificados/broker.key
require_certificate true
```

Reiniciar el broker:

```bash
sudo systemctl restart mosquitto
```
