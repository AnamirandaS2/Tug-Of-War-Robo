#include <RF24.h> 

// Definição dos pinos
const int chavePin = 2;  // Pino onde a chave está conectada
const int motorPin = 9;  // Pino onde o motor está conectado

void setup() {
  pinMode(chavePin, INPUT);  // Configura o pino da chave como entrada
  pinMode(motorPin, OUTPUT);  // Configura o pino do motor como saída
  Serial.begin(9600);
}

void loop() {
  // Verifica se a chave está ligada
  if (digitalRead(chavePin) == HIGH) {
    acionarMotor();  // Se a chave estiver ligada, aciona o motor
  } else {
    desligarMotor();  // Se a chave estiver desligada, desliga o motor
  }
}

// Função para acionar o motor com velocidade gradativa
void acionarMotor() {
  for (int velocidade = 0; velocidade <= 255; velocidade += 5) {
    analogWrite(motorPin, velocidade);  // Define a velocidade do motor
    delay(2000);  // Aguarda um curto período de tempo para a velocidade aumentar gradativamente
    Serial.print("Velocidade: ");
    Serial.println("teste");
  }
}

// Função para desligar o motor
void desligarMotor() {
  analogWrite(motorPin, 0);  // Desliga o motor
}