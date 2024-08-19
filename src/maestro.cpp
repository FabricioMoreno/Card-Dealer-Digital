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
// const int motorSpeed = 12;           // Ajusta esto según tu motor

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

// // Pines para los pulsadores
// const int startButtonPin = 12; // Pin para el pulsador de inicio
// const int resetButtonPin = 13; // Pin para el pulsador de reset

// // Variables de estado del sistema
// bool parametersSet = false; // Bandera para verificar si los parámetros fueron establecidos
// bool dealingInProgress = false; // Flag para controlar la ejecución de repartir cartas

// // Variables para el antirrebote con tiempos
// unsigned long lastStartButtonPress = 0; // Tiempo del último pulso del botón de inicio
// unsigned long lastResetButtonPress = 0; // Tiempo del último pulso del botón de reset
// const unsigned long debounceDelay = 50; // Tiempo de antirrebote en milisegundos

// // Variables del juego
// int players = 5;
// int cardsPerPlayer = 2;

// void startCardDealing() {
//   int stepsPerStop = stepsPerRevolution / players;
//   Serial.print("Steps per stop: ");
//   Serial.println(stepsPerStop);

//   for (int i = 0; i < players; i++) {
//     Serial.print("Moving to position for player ");
//     Serial.println(i + 1);

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

//   Serial.println("Card dealing complete.");
// }

// void setup() {
//   // Configurar los pines de los pulsadores como entradas con pull-up
//   pinMode(startButtonPin, INPUT_PULLUP);
//   pinMode(resetButtonPin, INPUT_PULLUP);

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
//   unsigned long currentMillis = millis();

//   // Leer el estado de los pulsadores
//   bool currentStartButtonState = digitalRead(startButtonPin);
//   bool currentResetButtonState = digitalRead(resetButtonPin);

//   // Manejar el pulsador de inicio
//   if (currentStartButtonState == LOW) {
//     if (currentMillis - lastStartButtonPress > debounceDelay) {
//       lastStartButtonPress = currentMillis;
//       if (!dealingInProgress) {
//         dealingInProgress = true;

//         // Establecer parámetros por defecto
//         players = 2;
//         cardsPerPlayer = 2;
//         parametersSet = true;

//         // Mostrar en la pantalla LCD
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("ACD Encendido");
//         lcd.setCursor(0, 1);
//         lcd.print("Repartiendo...");

//         // Iniciar el reparto
//         startCardDealing();

//         dealingInProgress = false;
//       }
//     }
//   }

//   // Manejar el pulsador de reinicio
//   if (currentResetButtonState == LOW) {
//     if (currentMillis - lastResetButtonPress > debounceDelay) {
//       lastResetButtonPress = currentMillis;
//       if (parametersSet) {
//         if (!dealingInProgress) {
//           dealingInProgress = true;

//           // Mostrar en la pantalla LCD
//           lcd.clear();
//           lcd.setCursor(0, 0);
//           lcd.print("ACD Reset");
//           lcd.setCursor(0, 1);
//           lcd.print("Repartiendo...");

//           // Reiniciar el reparto con los mismos parámetros
//           startCardDealing();

//           dealingInProgress = false;
//         }
//       } else {
//         // Mostrar error en la pantalla LCD si no hay parámetros
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("Error: No Params");
//         lcd.setCursor(0, 1);
//         lcd.print("Set First");
//       }
//     }
//   }
// }
