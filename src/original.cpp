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

// // Pin para switch on/off
// const int buttonPin = 12;            // Pin para el botón de encendido/apagado
// volatile bool buttonPressed = false; // Bandera de estado del botón
// bool systemOn = false;               // Estado del sistema

// // Pin para el LED de estado
// const int ledPin = 13; // Pin para el LED de encendido

// // Variables del juego
// int players = 5; // Puedes ajustar esto según el número de jugadores
// int cardsPerPlayer = 2;

// // Variables para el antirrebote
// unsigned long lastDebounceTime = 0;
// unsigned long debounceDelay = 50; // 50 ms de retraso para el antirrebote

// void IRAM_ATTR toggleButton()
// {
//   buttonPressed = true; // Bandera para indicar que el botón fue presionado
// }

// void setup()
// {
//   // Configurar el pin del botón como entrada con resistencia pull-down
//   pinMode(buttonPin, INPUT_PULLDOWN);
//   attachInterrupt(digitalPinToInterrupt(buttonPin), toggleButton, CHANGE); // Configurar la interrupción en modo CHANGE
//   int buttonState = digitalRead(buttonPin);
//   if (buttonState == HIGH)
//   {
//     buttonPressed = true;
//     systemOn = true;
//     // El botón está presionado
//   }
//   else
//   {
//     buttonPressed = false;
//     systemOn = false;
//   }

//   // Configurar el pin del LED como salida
//   pinMode(ledPin, OUTPUT);
//   digitalWrite(ledPin, LOW); // Asegurarse de que el LED esté apagado inicialmente

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
// }

// void loop()
// {
//   // Verificar si el botón fue presionado
//   if (buttonPressed)
//   {
//     unsigned long currentTime = millis();
//     if ((currentTime - lastDebounceTime) > debounceDelay)
//     {
//       systemOn = !systemOn; // Cambiar el estado del sistema
//       lastDebounceTime = currentTime;
//       buttonPressed = false; // Reiniciar la bandera del botón

//       // Si se apaga el sistema, detener el motor y limpiar la pantalla LCD
//       if (!systemOn)
//       {
//         // Detener el motor paso a paso
//         myStepper.setSpeed(0);
//         myStepper.step(0);

//         // Detener el motor DC
//         digitalWrite(dcMotorPin1, LOW);
//         digitalWrite(dcMotorPin2, LOW);

//         // Apagar el LED
//         digitalWrite(ledPin, LOW);
//       }
//     }
//         // Limpiar la pantalla LCD
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("ACD Encendido");
//         lcd.setCursor(0, 1);
//         lcd.print("SIWTCH --> ON");
//         delay(3000);
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("En Reparto...");
//         lcd.setCursor(0, 1);
//         lcd.print("P: ");
//         lcd.print(players);
//         lcd.print("  CPP: ");
//         lcd.print(cardsPerPlayer);
//   }

//   // Lógica para manejar el sistema encendido o apagado
//   if (systemOn)
//   {
//     // Encender el LED
//     digitalWrite(ledPin, HIGH);

//     int stepsPerStop = stepsPerRevolution / players; // Calcular pasos entre paradas

//     for (int i = 0; i < players; i++)
//     {
//       // Verificar si se apagó el sistema durante el ciclo de jugadores
//       // Si se apaga el sistema, detener el motor y limpiar la pantalla LCD
//       if (!systemOn)
//       {
//         // Detener el motor paso a paso
//         myStepper.setSpeed(0);
//         myStepper.step(0);

//         // Detener el motor DC
//         digitalWrite(dcMotorPin1, LOW);
//         digitalWrite(dcMotorPin2, LOW);

//         // Apagar el LED
//         digitalWrite(ledPin, LOW);

//         break;
//       }

//       // Verificar si el botón fue presionado
//       if (buttonPressed)
//       {
//         unsigned long currentTime = millis();
//         if ((currentTime - lastDebounceTime) > debounceDelay)
//         {
//           systemOn = !systemOn; // Cambiar el estado del sistema
//           lastDebounceTime = currentTime;
//           buttonPressed = false; // Reiniciar la bandera del botón

//           // Si se apaga el sistema, detener el motor y limpiar la pantalla LCD
//           if (!systemOn)
//           {
//             // Detener el motor paso a paso
//             myStepper.setSpeed(0);
//             myStepper.step(0);

//             // Detener el motor DC
//             digitalWrite(dcMotorPin1, LOW);
//             digitalWrite(dcMotorPin2, LOW);

//             // Apagar el LED
//             digitalWrite(ledPin, LOW);

//             break;
//           }
//         }
//       }

//       // Mover el motor paso a paso a la posición del jugador
//       myStepper.step(stepsPerStop);
//       delay(1000); // Pequeña pausa antes de repartir cartas (ajustable)

//       // Repartir dos cartas usando el motor DC
//       for (int j = 0; j < cardsPerPlayer; j++)
//       {
//         // Verificar si se apagó el sistema durante el ciclo de cartas
//         if (!systemOn)
//           break;

//         // Encender el motor DC en una dirección
//         digitalWrite(dcMotorPin1, HIGH);
//         digitalWrite(dcMotorPin2, LOW);
//         delay(500); // Tiempo para repartir una carta (ajustable)

//         // Apagar el motor DC
//         digitalWrite(dcMotorPin1, LOW);
//         digitalWrite(dcMotorPin2, LOW);
//         delay(500); // Pausa entre cartas (ajustable)
//       }

//       delay(1000); // Pequeña pausa entre jugadores (ajustable)
//     }

//     // Esperar antes de la siguiente vuelta (puedes ajustar o quitar esto según tus necesidades)
//     delay(5000);
//   }
//   else
//   {
//     // Si el sistema está apagado, apagar el LED
//     digitalWrite(ledPin, LOW);
//   }
// }

    