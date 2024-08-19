// #include <WiFi.h>
// #include <WebServer.h>
// #include <ArduinoJson.h>

// // Configuración WiFi
// const char *ssid = "NETLIFE_AYALA";
// const char *password = "09923499073";

// // Crear un servidor en el puerto 80
// WebServer server(80);

// // Variables del juego
// int players = 5;
// int cardsPerPlayer = 2;
// bool systemOn = false;
// bool isPaused = false;

// void handleStart()

// {
//   server.enableCORS();
//   //Enable CORS
//   server.sendHeader("Access-Control-Allow-Origin", "*");
//   server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
//   server.sendHeader("Access-Control-Allow-Headers", "*");

//   String body = server.arg("plain");
//   JsonDocument doc;
//   deserializeJson(doc, body);
//   players = doc["players"];
//   cardsPerPlayer = doc["cardsPerPlayer"];
//   systemOn = true;

//   String msg = "Datos recibidos desde la web: " + String(players) + " " + String(cardsPerPlayer);

//   Serial.println(msg);

//   server.send(200, "application/json", "{\"status\":\"game started\"}");
// }

// // Funciones que encargan de tener contacto con la web
// void handleCommand()
// {
//   String body = server.arg("plain");
//   JsonDocument doc;
//   deserializeJson(doc, body);

//   String command = doc["command"];

//   if (command == "play")
//   {
//     // Pausa o reanuda todo el sistema
//     isPaused = !isPaused;
//     if (isPaused)
//     {
//       Serial.println("Juego pausado");
//     }
//     else
//     {
//       Serial.println("Juego reanudado");
//     }
//   }
//   else if (command == "stop")
//   {
//     // Apaga todo el sistema
//     systemOn = false;
//     Serial.println("Juego detenido");
//   }

//   server.send(200, "application/json", "{\"status\":\"command received\"}");
// }

// void setup()
// {
//   Serial.begin(9600);

//   // Conectar a la red WiFi
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(1000);
//     Serial.println("Conectando a WiFi...");
//   }
//   Serial.println("Conectado a WiFi");

//   // Imprimir la IP de la ESP32
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());

//   server.enableCORS();

//   server.on("/start", HTTP_GET, handleStart);
//   server.on("/start", HTTP_POST, handleStart);
//   server.on("/command", HTTP_POST, handleCommand);
//   server.begin();
//   Serial.println("Servidor iniciado");
// }

// void loop()
// {
//   server.handleClient();
//   // Tu código aquí
// }