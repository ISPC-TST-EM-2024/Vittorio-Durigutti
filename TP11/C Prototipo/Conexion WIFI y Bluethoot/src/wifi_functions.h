// Este funciona como un archivo de cabecera. Aca se contienen las declaraciones de las funciones, traidas de otros archivos .cpp.
// Este archivo es exportad, y llamado, luego por el main.cpp permitiendo simplificar y ordenar el codigo.

#ifndef WIFI_FUNCTIONS_H
#define WIFI_FUNCTIONS_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <Preferences.h>

// Aquí incluyes los archivos de encabezado que correspondan a cada funcionalidad
#include "ap_functions.h"       // Declaraciones para el modo AP
#include "bluetooth_functions.h" // Declaraciones para Bluetooth (cuando lo agregues)

// Declaración de funciones Wi-Fi (modo estación)
void connectWiFi(String ssid, String password, bool autoConnect);
void listNetworks();
void clearCredentials();
void disconnectWiFi();
void configureStaticIP();
void connectToServer();
void WiFiEvent(WiFiEvent_t event);

// Declaraciones de funciones del Modo AP (estas están definidas en ap_functions.cpp)
void setupAP(const char* ap_ssid, const char* ap_password);
void showConnectedDevices();

// Declaraciones para funciones de Bluetooth (cuando agregues bluetooth.cpp)
// Ejemplo de una función Bluetooth (debes reemplazar con las reales)
void initBluetooth();
void sendDataViaBluetooth(String data);

#endif
