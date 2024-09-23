// Este es el punto de acceso de mi aplicacion. LLamo a las funciones definidas en la cabece cabecera.
// Aqui defino tambien los menus que luego boy a mostrar en el monitor serial, y y la carga de las credenciales de wifi, si las ubiese

#include <Arduino.h>
#include "wifi_functions.h" // Esto incluye todas las funciones (Wi-Fi, AP y Bluetooth)

Preferences preferences;   // Objeto para manejar NVS
WiFiClient client;         // Cliente para la conexión TCP

void setup() {
  Serial.begin(115200);

  // Eventos Wi-Fi
  WiFi.onEvent(WiFiEvent);

  // Inicializar Bluetooth
  initBluetooth();

  // Opcional: conectarse a Wi-Fi guardado
  preferences.begin("wifi-creds", false);
  String ssid = preferences.getString("ssid", "");
  String password = preferences.getString("password", "");
  bool autoConnect = preferences.getBool("autoConnect", false);

  if (ssid != "") {
    Serial.println("Intentando conectar a red Wi-Fi guardada...");
    connectWiFi(ssid, password, autoConnect);
  } else {
    Serial.println("No hay redes guardadas. Listando redes...");
    listNetworks();
  }

  // Menú inicial
  Serial.println("\nOpciones:");
  Serial.println("1: Conectar Wi-Fi");
  Serial.println("2: Borrar credenciales Wi-Fi");
  Serial.println("3: Configurar IP estática");
  Serial.println("4: Desconectar Wi-Fi");
  Serial.println("5: Iniciar Punto de Acceso");
}

void loop() {
  if (Serial.available() > 0) {
    String option = Serial.readStringUntil('\n');
    option.trim();

    if (option == "1") {
      listNetworks();
    } else if (option == "2") {
      clearCredentials();
    } else if (option == "3") {
      configureStaticIP();
    } else if (option == "4") {
      disconnectWiFi();
    } else if (option == "5") {
      setupAP("ESP32_AP", "123456789");
    } else {
      Serial.println("Opción inválida.");
    }

    // Mostrar menú
    Serial.println("\nOpciones:");
    Serial.println("1: Conectar Wi-Fi");
    Serial.println("2: Borrar credenciales Wi-Fi");
    Serial.println("3: Configurar IP estática");
    Serial.println("4: Desconectar Wi-Fi");
    Serial.println("5: Iniciar Punto de Acceso");
  }
}
