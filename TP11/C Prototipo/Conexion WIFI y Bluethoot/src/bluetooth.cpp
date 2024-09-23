#include "bluetooth_functions.h"

// Inicializar el Bluetooth
void initBluetooth() {
    Serial.println("Bluetooth iniciado");
    // Configuración específica de Bluetooth aquí
}

// Enviar datos a través de Bluetooth
void sendDataViaBluetooth(String data) {
    Serial.print("Enviando datos via Bluetooth: ");
    Serial.println(data);
    // Lógica para enviar datos via Bluetooth aquí
}
