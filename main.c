// Incluindo as bibliotecas necessárias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definindo os pinos do sensor de temperatura, buzina, LED e motor
const int sensorTempPin = A0;
const int buzinaPin = 2;
const int ledPin = 3;
const int motorPin = 4;

// Definindo os valores de temperatura de referência
const int temperaturaMinima = 30;
const int temperaturaEmergencia = 50;

// Inicializando o display LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Inicializando o monitor serial
  Serial.begin(9600);

  // Inicializando o display LCD
  lcd.begin(16, 2);
  lcd.print("Temperatura:");

  // Configurando os pinos do buzina, LED e motor
  pinMode(buzinaPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Lendo a temperatura
  int temperatura = lerTemperatura();

  // Exibindo a temperatura no display LCD
  lcd.setCursor(0, 1);
  lcd.print(temperatura);
  lcd.print(" C");

  // Verificando a temperatura e tomando as ações correspondentes
  if (temperatura >= temperaturaMinima) {
    acionarMotor();
  } else {
    desligarMotor();
  }

  if (temperatura >= temperaturaEmergencia) {
    acionarEmergencia();
  } else {
    desligarEmergencia();
  }

  delay(1000); // Aguardando 1 segundo antes de ler a temperatura novamente
}

int lerTemperatura() {
  // Lendo a tensão do sensor de temperatura
  int tensao = analogRead(sensorTempPin);

  // Convertendo a tensão em temperatura em graus Celsius
  float temperatura = (tensao * 5.0) / 1024.0;
  temperatura = (temperatura - 0.5) * 100;

  // Exibindo a tensão e a temperatura no monitor serial
  Serial.print("Tensao: ");
  Serial.print(tensao);
  Serial.print(" | Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");

  return temperatura;
}

void acionarMotor() {
  // Acionando o motor
  digitalWrite(motorPin, HIGH);
}

void desligarMotor() {
  // Desligando o motor
  digitalWrite(motorPin, LOW);
}

void acionarEmergencia() {
  // Acionando o LED vermelho e a buzina
  digitalWrite(ledPin, HIGH);
  digitalWrite(buzinaPin, HIGH);
}

void desligarEmergencia() {
  // Desligando o LED vermelho e a buzina
  digitalWrite(ledPin, LOW);
  digitalWrite(buzinaPin, LOW);
}