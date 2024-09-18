## TP#20. Trabajo Practico

**Objetivos:**
- Familiarizarse con las tecnologías de los módulos de comunicación incorporados en el ESP32.
- Conocer las librerías asociadas a cada modulo de comunicación para el ESP32 incluidas en el framework Arduino.

Realizar los siguientes ejercicios según se solicita a continuación, dejar los registros de desarrollo en el repositorio personal de la materia, con la estructura ABP de trabajo habitual.

## Serie de Prácticas Wi-Fi con el ESP32

----------------------------------------------------------------

### Práctica 1: Conexión Básica a una Red Wi-Fi y Monitorización de Estado

**Objetivos:**
- Aprender a conectar el ESP32 a una red Wi-Fi en modo Estación (STA),
monitorear el estado de la conexión y manejar la reconexión automática en
caso de pérdida de la red.

**Librerías Necesarias**
- WiFi.h: Librería estándar de Arduino para manejo de Wi-Fi.

**Pasos a Seguir**
1. Configuración del Entorno de Desarrollo
    - Configura un nuevo proyecto en PlatformIO para el ESP32 utilizando el framework Arduino.
2. Implementar Conexión Wi-Fi
    - Define las credenciales de la red Wi-Fi (SSID y contraseña).
    - Implementa la lógica para conectar el ESP32 a la red Wi-Fi.
    - Agrega un bucle que monitorice la conexión Wi-Fi.
3. Monitorizar Estado de Conexión
    - Imprime el estado de la conexión en el Monitor Serie.
4. Prueba de Funcionamiento
    - Prueba el programa con credenciales correctas e incorrectas.
    - Deshabilita el Wi-Fi del router para comprobar la reconexión automática.

----------------------------------------------------------------

### Práctica 2: Configurar el ESP32 como Punto de Acceso (AP)

**Objetivo**
- Configurar el ESP32 como un punto de acceso (AP) para que otros dispositivos se conecten a él.

**Librerías Necesarias**
- WiFi.h: Librería estándar para manejar la conexión Wi-Fi en modo AP.

**Pasos a Seguir**
1. Configuración del Modo AP
    - Configura el ESP32 para que funcione en modo Punto de Acceso.
    - Define el SSID y la contraseña de la red que creará el ESP32.
2. Iniciar el Punto de Acceso
    - Implementa la lógica para iniciar el punto de acceso y mostrar la dirección IP asignada en el Monitor Serie.
3. Monitorear Conexiones
    - Implementa una función que muestre la cantidad de dispositivos conectados al punto de acceso.
4. Prueba de Funcionamiento
    - Conéctate a la red creada por el ESP32 desde un smartphone o PC.
    - Verifica en el Monitor Serie el número de dispositivos conectados.

----------------------------------------------------------------

### Práctica 3: Servidor Web Simple con Wi-Fi

**Objetivo**
- Crear un servidor web en el ESP32 para controlar un LED desde un navegador web.

**Librerías Necesarias**
- WiFi.h: Para la conexión Wi-Fi.
- WebServer.h: Para implementar el servidor web.

**Pasos a Seguir**

1. Configurar Conexión Wi-Fi
- Conecta el ESP32 a una red Wi-Fi.
2. Implementar el Servidor Web
- Configura un servidor web que escuche en el puerto 80.
- Crea una página web simple con dos botones para encender y apagar un LED.
3. Controlar el LED
- Define rutas para encender y apagar el LED.
- Implementa la lógica para cambiar el estado del LED según las peticiones recibidas.
4. Prueba de Funcionamiento
- Accede a la página web alojada por el ESP32 desde un navegador.
- Interactúa con los botones y observa el comportamiento del LED.

----------------------------------------------------------------

### Práctica 4: Cliente HTTP para Enviar Datos a un Servidor

**Objetivo**
- Configurar el ESP32 como cliente HTTP para enviar datos a un servidor
remoto.

**Librerías Necesarias**
- WiFi.h: Para la conexión Wi-Fi.
- HTTPClient.h: Para realizar solicitudes HTTP.