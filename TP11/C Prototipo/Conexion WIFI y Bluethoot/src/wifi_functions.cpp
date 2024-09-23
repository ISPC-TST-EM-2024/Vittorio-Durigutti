// En este archivo tengo la implementacion de las funciones. Que son luego declaradas en la cafecera, para ser llamadas para el main.

#include "wifi_functions.h"


extern Preferences preferences;
extern WiFiClient client;
const char* host = "192.168.1.100"; 
const int port = 3005;               

// Función para manejar eventos de Wi-Fi
void WiFiEvent(WiFiEvent_t event) {
  switch (event) {
    case SYSTEM_EVENT_STA_CONNECTED:
      Serial.println("Conectado a la red Wi-Fi.");
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("Desconectado de la red Wi-Fi.");
      if (preferences.getBool("autoConnect", false)) {
        Serial.println("Intentando reconectar en 20 segundos...");
        delay(20000);
        connectWiFi(preferences.getString("ssid", ""), preferences.getString("password", ""), true);
      }
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.print("Conexión exitosa. Dirección IP: ");
      Serial.println(WiFi.localIP());
      Serial.println("Usted se encuentra conectado a internet.");
      connectToServer();
      break;
  }
}

// Función para conectar al Wi-Fi
void connectWiFi(String ssid, String password, bool autoConnect) {
  if (ssid != "" && password != "") {
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("Conectando a la red: ");
    Serial.println(ssid);
  } else {
    Serial.println("No se encontraron credenciales guardadas.");
  }
}

// Función para listar redes Wi-Fi cercanas
void listNetworks() {
  int numNetworks = WiFi.scanNetworks();
  if (numNetworks == 0) {
    Serial.println("No se encontraron redes.");
  } else {
    Serial.println("Redes Wi-Fi disponibles:");
    for (int i = 0; i < numNetworks; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.println(" dBm)");
    }
    Serial.println("Ingrese el número de la red a la que desea conectarse:");

    while (Serial.available() == 0) {}  // Espera a la entrada del usuario
    int selectedNetwork = Serial.parseInt() - 1;
    if (selectedNetwork >= 0 && selectedNetwork < numNetworks) {
      String ssid = WiFi.SSID(selectedNetwork);
      Serial.print("Seleccionó: ");
      Serial.println(ssid);
      Serial.print("Ingrese la contraseña: ");
      while (Serial.available() == 0) {}
      String password = Serial.readStringUntil('\n');
      password.trim();

      connectWiFi(ssid, password, true);

      // Preguntar si quiere guardar la red
      Serial.println("¿Desea guardar esta red para conexiones automáticas? (y/n)");
      while (Serial.available() == 0) {}
      String save = Serial.readStringUntil('\n');
      save.trim();
      if (save == "y" || save == "Y") {
        preferences.putString("ssid", ssid);
        preferences.putString("password", password);
        preferences.putBool("autoConnect", true);
        Serial.println("Credenciales guardadas.");
      } else {
        Serial.println("Credenciales no guardadas.");
      }
    } else {
      Serial.println("Selección inválida.");
    }
  }
}

// Función para borrar las credenciales de Wi-Fi
void clearCredentials() {
  preferences.remove("ssid");
  preferences.remove("password");
  preferences.putBool("autoConnect", false);
  Serial.println("Credenciales Wi-Fi borradas.");
}

// Función para desconectar del Wi-Fi
void disconnectWiFi() {
  WiFi.disconnect();
  Serial.println("Usted se encuentra desconectado de la red.");
}

// Función para configurar IP estática
void configureStaticIP() {
  IPAddress local_IP(192, 168, 1, 184);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(local_IP, gateway, subnet);
  Serial.println("Configuración de red personalizada establecida.");
}

// Función para conectarse al servidor
void connectToServer() {
  if (client.connect(host, port)) {
    Serial.println("Conexión al servidor exitosa.");
    client.println("GET / HTTP/1.1");
    client.println("Host: 192.168.1.100");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Error al conectarse al servidor.");
  }
}

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
