#pragma once //incluye 1 sola vez el archivo

class MQTTManager{
public:
    void start();
    void stop();
    bool isRunning();
};