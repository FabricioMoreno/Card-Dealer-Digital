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


// // Variables del juego
// int players = 5;
// int cardsPerPlayer = 2;


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
 
//   Serial.begin(9600);
//   Serial.println("Sistema listo");
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

// }

// void loop() {
//  startCardDealing();
// }

