#include <WiFi.h>
#include "ap_functions.h"

// Función para configurar el Modo AP (Punto de Acceso)
void setupAP(const char* ap_ssid, const char* ap_password) {
  WiFi.softAP(ap_ssid, ap_password);
  Serial.print("Punto de acceso iniciado. Dirección IP del AP: ");
  Serial.println(WiFi.softAPIP());
}

// Función para mostrar la cantidad de dispositivos conectados al AP
void showConnectedDevices() {
  Serial.print("Dispositivos conectados: ");
  Serial.println(WiFi.softAPgetStationNum());
}
