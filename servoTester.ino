#include <ESP32Servo.h>

// Define el objeto servo
Servo myservo;

// Define los pines
const int potPin = 34;  // Pin ADC para el potenciómetro
const int servoPin = 13; // Pin PWM para el servomotor

void setup() {
  // Inicia la comunicación serie
  Serial.begin(115200);

  // Adjunta el servomotor al pin PWM
  myservo.attach(servoPin);

  // Inicia el pin del potenciómetro
  pinMode(potPin, INPUT);
}

void loop() {
  // Lee el valor del potenciómetro
  int potValue = analogRead(potPin);

  // Filtra el valor del potenciómetro para suavizar las lecturas
  potValue = filterValue(potValue);

  // Limita el valor a un rango válido (0-4095)
  potValue = constrain(potValue, 0, 4095);

  // Mapea el valor del potenciómetro (0-4095) al rango del servo (0-180 grados)
  int servoValue = map(potValue, 0, 4095, 0, 180);

  // Mueve el servomotor a la posición deseada
  myservo.write(servoValue);

  // Imprime los valores para depuración
  Serial.print("Pot Value: ");
  Serial.print(potValue);
  Serial.print(" - Servo Value: ");
  Serial.println(servoValue);

  // Espera un momento antes de la siguiente lectura
  delay(15);
}

// Función para filtrar el valor del potenciómetro (filtro simple de media móvil)
int filterValue(int value) {
  static int previousValue = 0;
  int filteredValue = (previousValue + value) / 2;
  previousValue = value;
  return filteredValue;
}
