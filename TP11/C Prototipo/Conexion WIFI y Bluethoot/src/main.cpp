#include <Arduino.h>
#include <WiFi.h>          // Librería para manejar conexiones Wi-Fi
#include <WiFiClient.h>    // Librería para manejar conexiones de cliente
#include <Preferences.h>   // Librería para almacenar credenciales en NVS

Preferences preferences;   // Objeto para manejar NVS

const char* host = "192.168.1.100";  // Cambia esto a la IP de tu host local
const int port = 3005;               // Puerto del servidor remoto

WiFiClient client;        // Cliente para la conexión TCP
String ssid;              // SSID de la red Wi-Fi
String password;          // Contraseña de la red Wi-Fi
bool autoConnect = false; // Conexión automática habilitada/deshabilitada

void connectWiFi();       // Declaración adelantada para conectar Wi-Fi
void listNetworks();      // Declaración adelantada para listar redes
void connectToServer();   // Declaración adelantada para conectar al servidor
void disconnectWiFi();    // Declaración para desconectar Wi-Fi

// Evento para monitorear el estado de la conexión Wi-Fi
void WiFiEvent(WiFiEvent_t event) {
  switch(event) {
    case SYSTEM_EVENT_STA_CONNECTED:
      Serial.println("Conectado a la red Wi-Fi.");
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("Desconectado de la red Wi-Fi.");
      if (autoConnect) {
        Serial.println("Intentando reconectar en 20 segundos...");
        delay(20000);
        connectWiFi();  // Intentar reconectar
      }
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.print("Conexión exitosa. Dirección IP: ");
      Serial.println(WiFi.localIP());
      Serial.println("Usted se encuentra conectado a internet.");
      connectToServer();  // Intentar conectar al servidor remoto
      break;
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.onEvent(WiFiEvent);  // Configurar los eventos Wi-Fi

  // Cargar credenciales guardadas
  preferences.begin("wifi-creds", false);
  ssid = preferences.getString("ssid", "");
  password = preferences.getString("password", "");
  autoConnect = preferences.getBool("autoConnect", false);

  if (ssid != "") {
    Serial.println("Red Wi-Fi guardada encontrada. Intentando conectar...");
    connectWiFi();
  } else {
    Serial.println("No hay redes guardadas. Listando redes cercanas...");
    listNetworks();
  }

  // Mostrar menú inicial
  Serial.println("\nMenú de opciones:");
  Serial.println("1: Conectar a una red Wi-Fi");
  Serial.println("2: Borrar/redactar credenciales Wi-Fi");
  Serial.println("3: Configurar parámetros de red (WiFi.config)");
  Serial.println("4: Desconectar del Wi-Fi");
}

void loop() {
  if (Serial.available() > 0) {
    String option = Serial.readStringUntil('\n');
    option.trim();

    if (option == "1") {
      listNetworks();
    } else if (option == "2") {
      preferences.remove("ssid");
      preferences.remove("password");
      Serial.println("Credenciales Wi-Fi borradas.");
    } else if (option == "3") {
      // Configuración de IP estática
      IPAddress local_IP(192, 168, 1, 184);
      IPAddress gateway(192, 168, 1, 1);
      IPAddress subnet(255, 255, 255, 0);
      WiFi.config(local_IP, gateway, subnet);
      Serial.println("Configuración de red personalizada establecida.");
    } else if (option == "4") {
      disconnectWiFi();
    } else {
      Serial.println("Opción no válida.");
    }

    // Mostrar menú después de cada operación
    Serial.println("\nMenú de opciones:");
    Serial.println("1: Conectar a una red Wi-Fi");
    Serial.println("2: Borrar/redactar credenciales Wi-Fi");
    Serial.println("3: Configurar parámetros de red (WiFi.config)");
    Serial.println("4: Desconectar del Wi-Fi");
  }
}

// Función para conectar al Wi-Fi usando las credenciales guardadas o ingresadas
void connectWiFi() {
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
      Serial.print("Seleccionó: ");
      Serial.println(WiFi.SSID(selectedNetwork));
      Serial.print("Ingrese la contraseña: ");
      while (Serial.available() == 0) {}
      password = Serial.readStringUntil('\n');
      password.trim();

      ssid = WiFi.SSID(selectedNetwork);
      connectWiFi();

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

// Función para desconectar del Wi-Fi
void disconnectWiFi() {
  WiFi.disconnect();
  Serial.println("Usted se encuentra desconectado de la red.");
}

// Función para conectarse a un servidor en el puerto 3005
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
