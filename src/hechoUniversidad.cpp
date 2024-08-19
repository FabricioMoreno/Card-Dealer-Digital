// #include <WiFi.h>
// #include <WebServer.h>
// #include <ArduinoJson.h>
// #include <Stepper.h>
// #include <LiquidCrystal_I2C.h>

// // Configuración WiFi
// const char *ssid = "Redmi Note 11";
// const char *password = "fabriciomoreno";

// // Crear un servidor en el puerto 80
// WebServer server(80);

// // Definición de los pines del motor paso a paso
// const int motorPin1 = 19;
// const int motorPin2 = 18;
// const int motorPin3 = 5;
// const int motorPin4 = 17;

// // Número de pasos por revolución para tu motor paso a paso
// const int stepsPerRevolution = 2048; // Ajusta esto según tu motor
// const int motorSpeed = 10;           // Ajusta esto según tu motor

// // Crear un objeto de la clase Stepper
// Stepper myStepper(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4);

// // Pines I2C para el LCD
// const int I2C_SDA = 21;
// const int I2C_SCL = 22;

// // Tamaño del LCD
// const int COLUMNS = 16;
// const int ROWS = 2;

// // Crear un objeto de la clase LiquidCrystal_I2C para el LCD
// LiquidCrystal_I2C lcd(0x27, COLUMNS, ROWS); // 0x27 es la dirección I2C del adaptador

// // Pines del motor DC para repartir cartas
// const int dcMotorPin1 = 26; // Pin de control 1 para el motor DC
// const int dcMotorPin2 = 27; // Pin de control 2 para el motor DC

// // Pin para el LED de estado
// const int ledPin = 13; // Pin para el LED de encendido

// // Pines para los botones físicos
// const int buttonPlayPausePin = 14; // Pin para el botón play/pause
// const int buttonRestartPin = 12;   // Pin para el botón de reinicio
// const int buttonPowerPin = 15;     // Pin para el botón de encendido/apagado

// // Variables del juego
// int players = 5;
// int cardsPerPlayer = 2;
// bool systemOn = false;
// bool isPaused = false;
// bool isRestart = false;

// // Variables para el antirrebote
// unsigned long lastDebounceTime = 0;
// unsigned long debounceDelay = 50; // 50 ms de retraso para el antirrebote

// void handleCommand() {
//   String body = server.arg("plain");
//   StaticJsonDocument<200> doc;
//   DeserializationError error = deserializeJson(doc, body);

//   if (error) {
//     server.send(400, "application/json", "{\"status\":\"invalid json\"}");
//     return;
//   }

//   String command = doc["command"];

//   if (command == "start") {
//     players = doc["players"];
//     cardsPerPlayer = doc["cardsPerPlayer"];
//     systemOn = true;
//     isPaused = false;
//     isRestart = false;
//     Serial.println("Juego iniciado");
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Juego iniciado");
//   } else if (command == "restart") {
//     systemOn = true;
//     isPaused = false;
//     isRestart = true;
//     Serial.println("Juego reiniciado");
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Juego reiniciado");
//   }

//   server.send(200, "application/json", "{\"status\":\"command received\"}");
// }

// void setup() {
//   // Inicializar la comunicación I2C con los pines específicos
//   Wire.begin(I2C_SDA, I2C_SCL);
//   // Inicializar la pantalla LCD
//   lcd.begin(COLUMNS, ROWS);
//   lcd.backlight();
//   lcd.setCursor(0, 0);
//   lcd.print("Num Players: ");
//   lcd.print(players);
//   delay(2000);
//   lcd.clear();

//   Serial.begin(9600);
//   Serial.println("Programa iniciado");
//   lcd.print("Bienvenido");
//   lcd.setCursor(0, 1);
//   lcd.print("Usuario");
//   delay(2000);
//   lcd.clear();

//   lcd.setCursor(0, 0);
//   lcd.print("ACD Apagado");
//   lcd.setCursor(0, 1);
//   lcd.print("SIWTCH --> OFF");

//   // Inicializar el motor paso a paso
//   myStepper.setSpeed(motorSpeed); // Velocidad en RPM

//   // Inicializar los pines del motor DC
//   pinMode(dcMotorPin1, OUTPUT);
//   pinMode(dcMotorPin2, OUTPUT);

//   digitalWrite(dcMotorPin1, LOW); // Apagar el motor DC inicialmente
//   digitalWrite(dcMotorPin2, LOW); // Apagar el motor DC inicialmente

//   // Configurar el pin del LED como salida
//   pinMode(ledPin, OUTPUT);
//   digitalWrite(ledPin, LOW); // Asegurarse de que el LED esté apagado inicialmente

//   // Configurar los pines de los botones como entrada
//   pinMode(buttonPlayPausePin, INPUT_PULLUP);
//   pinMode(buttonRestartPin, INPUT_PULLUP);
//   pinMode(buttonPowerPin, INPUT_PULLUP);

//   // Conectar a la red WiFi
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Conectando a WiFi...");
//   }
//   Serial.println("Conectado a WiFi");

//   // Configurar las rutas del servidor
//   server.on("/command", HTTP_POST, handleCommand);
//   server.begin();
//   Serial.println("Servidor iniciado");
// }

// void loop() {
//   // Manejar peticiones del servidor
//   server.handleClient();
//   Serial.println(buttonPowerPin);


//   // Leer estado del botón de encendido/apagado
//   if (digitalRead(buttonPowerPin) == LOW) {
//     delay(50); // Antirrebote
//     if (digitalRead(buttonPowerPin) == LOW) {
//       systemOn = !systemOn;
//       lcd.clear();
//       if (systemOn) {
//         Serial.println("Sistema encendido");
//         lcd.print("Sistema encendido");
//       } else {
//         Serial.println("Sistema apagado");
//         lcd.print("Sistema apagado");
//         // Apagar motores y LED si el sistema está apagado
//         digitalWrite(dcMotorPin1, LOW);
//         digitalWrite(dcMotorPin2, LOW);
//         digitalWrite(ledPin, LOW);
//       }
//       delay(1000);
//     }
//   }

//   // Leer estado del botón de reinicio
//   if (digitalRead(buttonRestartPin) == LOW) {
//     delay(50); // Antirrebote
//     if (digitalRead(buttonRestartPin) == LOW) {
//       isRestart = true;
//       systemOn = true;
//       isPaused = false;
//       lcd.clear();
//       Serial.println("Juego reiniciado");
//       lcd.print("Juego reiniciado");
//       delay(1000);
//     }
//   }

//   // Leer estado del botón de play/pause
//   if (digitalRead(buttonPlayPausePin) == LOW) {
//     delay(50); // Antirrebote
//     if (digitalRead(buttonPlayPausePin) == LOW) {
//       isPaused = !isPaused;
//       lcd.clear();
//       if (isPaused) {
//         Serial.println("Juego pausado");
//         lcd.print("Juego pausado");
//       } else {
//         Serial.println("Juego reanudado");
//         lcd.print("Juego reanudado");
//       }
//       delay(1000);
//     }
//   }

//   // Control del juego
//   if (systemOn && !isPaused) {
//     if (isRestart) {
//       lcd.clear();
//       lcd.print("Reiniciando juego");
//       delay(2000); // Agregar un retraso para que se vea el mensaje
//       lcd.clear();
//       lcd.print("Juego iniciado");
//       isRestart = false; // Resetear la bandera de reinicio
//     }
//     lcd.setCursor(0, 0);
//     lcd.print("Repartiendo...");
//     digitalWrite(ledPin, HIGH); // Encender el LED
//     // Mover el motor paso a paso
//     myStepper.step(stepsPerRevolution); // Ajusta la cantidad de pasos según sea necesario
//     delay(1000);                        // Esperar un segundo antes de mover de nuevo

//     // Repartir cartas con el motor DC
//     for (int i = 0; i < players; i++) {
//       for (int j = 0; j < cardsPerPlayer; j++) {
//         digitalWrite(dcMotorPin1, HIGH); // Encender el motor DC en una dirección
//         digitalWrite(dcMotorPin2, LOW);
//         delay(1000); // Ajusta el tiempo según sea necesario
//         digitalWrite(dcMotorPin1, LOW); // Apagar el motor DC
//         digitalWrite(dcMotorPin2, LOW);
//         delay(500); // Ajusta el tiempo entre cartas según sea necesario
//       }
//     }
//   } else {
//     digitalWrite(ledPin, LOW); // Apagar el LED
//   }
// }
