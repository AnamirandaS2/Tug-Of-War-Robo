#include <RF24.h>  // Inclui a biblioteca RF24

#define pinCE  9 // Define o pino CE para o módulo NRF24L01
#define pinCSN 10  // Define o pino CSN para o módulo NRF24L01

#define pinPot1 A4  // Define o pino para o primeiro potenciômetro
#define pinPot2 A5  // Define o pino para o segundo potenciômetro
#define pinBotao 2  // Define o pino para o botão

// Define uma estrutura para armazenar os dados dos potenciômetros e do botão
struct tipoDadoRF {
  int pot1;
  int pot2;
  bool botao;
} dadosRF;

RF24 radio(pinCE, pinCSN);  // Cria uma instância da classe RF24

const uint64_t pipeOut = 0xE8E8F0F0E1LL;  // Endereço do tubo de saída

void setup() {
  Serial.begin(9600);  // Inicia a comunicação serial
  radio.begin();  // Inicia o módulo de rádio
  radio.setAutoAck(false);  // Desativa a confirmação automática de recebimento de pacotes
  radio.setPALevel(RF24_PA_LOW);  // Define o nível de potência do amplificador para baixo
  radio.setDataRate(RF24_250KBPS);  // Define a taxa de dados para 250Kbps
  radio.openWritingPipe(pipeOut);  // Abre o tubo de escrita

  pinMode(pinPot1, INPUT);  // Define o pino do primeiro potenciômetro como entrada
  pinMode(pinPot2, INPUT);  // Define o pino do segundo potenciômetro como entrada
  pinMode(pinBotao, INPUT_PULLUP);  // Define o pino do botão como entrada com resistor de pull-up
}

void loop() {
  dadosRF.pot1 = analogRead(pinPot1);  // Lê o valor do primeiro potenciômetro
  dadosRF.pot2 = analogRead(pinPot2);  // Lê o valor do segundo potenciômetro
  dadosRF.botao = digitalRead(pinBotao) == LOW;  // Lê o estado do botão

  radio.write(&dadosRF, sizeof(tipoDadoRF));  // Envia os dados para o outro dispositivo via rádio

  Serial.print("Pot1: ");  // Imprime "Pot1: " na porta serial
  Serial.println(dadosRF.pot1);  // Imprime o valor do primeiro potenciômetro na porta serial
  Serial.print("Pot2: ");  // Imprime "Pot2: " na porta serial
  Serial.println(dadosRF.pot2);  // Imprime o valor do segundo potenciômetro na porta serial
  Serial.print("Botao: ");  // Imprime "Botao: " na porta serial
  Serial.println(dadosRF.botao ? "Pressionado" : "Não pressionado");  // Imprime o estado do botão na porta serial

  delay(10);  // Aguarda 10 milissegundos antes de repetir o loop
}