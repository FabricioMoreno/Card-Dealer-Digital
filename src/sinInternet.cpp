// #include <Arduino.h>
// #include <Wire.h>
// #include <Stepper.h>
// #include <LiquidCrystal_I2C.h>

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

// // Pines para los botones
// const int startButtonPin = 12; // Pin para el botón de inicio
// const int resetButtonPin = 13; // Pin para el botón de reset

// // Variables de estado del sistema
// volatile bool startButtonPressed = false;
// volatile bool resetButtonPressed = false;
// bool parametersSet = false; // Bandera para verificar si los parámetros fueron establecidos

// // Variables del juego
// int players = 5;
// int cardsPerPlayer = 2;

// // Variables para el antirrebote
// unsigned long lastStartDebounceTime = 0;
// unsigned long lastResetDebounceTime = 0;
// unsigned long debounceDelay = 50; // 50 ms de retraso para el antirrebote

// void IRAM_ATTR startButtonISR() {
//   startButtonPressed = true;
// }

// void IRAM_ATTR resetButtonISR() {
//   resetButtonPressed = true;
// }

// void startCardDealing() {
//   int stepsPerStop = stepsPerRevolution / players;

//   for (int i = 0; i < players; i++) {
//     myStepper.step(stepsPerStop);
//     delay(1000); // Pausa entre jugadores

//     for (int j = 0; j < cardsPerPlayer; j++) {
//       digitalWrite(dcMotorPin1, HIGH);
//       digitalWrite(dcMotorPin2, LOW);
//       delay(500); // Tiempo para repartir una carta
//       digitalWrite(dcMotorPin1, LOW);
//       digitalWrite(dcMotorPin2, LOW);
//       delay(500); // Pausa entre cartas
//     }

//     delay(1000); // Pausa entre jugadores
//   }
// }

// void setup() {
//   // Configurar los pines de los botones como entradas con pull-up
//   pinMode(startButtonPin, INPUT_PULLUP);
//   pinMode(resetButtonPin, INPUT_PULLUP);

//   // Configurar las interrupciones para los botones
//   attachInterrupt(digitalPinToInterrupt(startButtonPin), startButtonISR, FALLING);
//   attachInterrupt(digitalPinToInterrupt(resetButtonPin), resetButtonISR, FALLING);

//   // Inicializar la pantalla LCD
//   Wire.begin(I2C_SDA, I2C_SCL);
//   lcd.begin(COLUMNS, ROWS);
//   lcd.backlight();
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Num Players: ");
//   lcd.print(players);

//   // Inicializar el motor paso a paso
//   myStepper.setSpeed(motorSpeed);

//   // Inicializar los pines del motor DC
//   pinMode(dcMotorPin1, OUTPUT);
//   pinMode(dcMotorPin2, OUTPUT);
//   digitalWrite(dcMotorPin1, LOW);
//   digitalWrite(dcMotorPin2, LOW);

//   Serial.begin(9600);
//   Serial.println("Sistema listo");
// }

// void loop() {
//   unsigned long currentTime = millis();

//   if (startButtonPressed && (currentTime - lastStartDebounceTime) > debounceDelay) {
//     startButtonPressed = false;
//     lastStartDebounceTime = currentTime;

//     // Establecer parámetros por defecto
//     players = 5;
//     cardsPerPlayer = 2;
//     parametersSet = true;

//     // Mostrar en la pantalla LCD
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("ACD Encendido");
//     lcd.setCursor(0, 1);
//     lcd.print("Repartiendo...");

//     // Iniciar el reparto
//     startCardDealing();
//   }

//   if (resetButtonPressed && (currentTime - lastResetDebounceTime) > debounceDelay) {
//     resetButtonPressed = false;
//     lastResetDebounceTime = currentTime;

//     if (parametersSet) {
//       // Mostrar en la pantalla LCD
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("ACD Reset");
//       lcd.setCursor(0, 1);
//       lcd.print("Repartiendo...");

//       // Reiniciar el reparto con los mismos parámetros
//       startCardDealing();
//     } else {
//       // Mostrar error en la pantalla LCD si no hay parámetros
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("Error: No Params");
//       lcd.setCursor(0, 1);
//       lcd.print("Set First");
//     }
//   }
// }

