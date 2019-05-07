/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 1 PERIFÉRICOS: DISPLAY LCD.
 * 
 * Dependências: 
 *  LiquidCrystal_I2C from DFRobot
 *    - Baixar do Github e instalar manualmente https://github.com/agnunez/ESP8266-I2C-LCD1602)
 *  
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 */

#include "wifi.h"
#include "mqtt.h"
#include <LiquidCrystal_I2C.h>

// Configura o LCD display. Pinos: D2: SDA, D1: SCL
LiquidCrystal_I2C lcd(0x27, 16, 2);

WFclass wifi;

const String subscribeTopic("dblab/hands-on/mqtt/lcd/in");
const String mqttServer("emqx.dbserver.com.br");
const int mqttServerPort = 1883;
MqttClient mqttClient(mqttServer, mqttServerPort);

void printBanner()
{
  Serial.println("  _____  ____  _           _");
  Serial.println(" |  __ \\|  _ \\| |         | |");
  Serial.println(" | |  | | |_) | |     __ _| |__");
  Serial.println(" | |  | |  _ <| |    / _' | '_ \\");
  Serial.println(" | |__| | |_) | |___| (_| | |_) |");
  Serial.println(" |_____/|____/|______\\__,_|_.__/");
  Serial.println();
}

/* Função de configuração. Ela é executada uma única vez no início da execução
 *   do programa. */
void setup()
{
  Serial.begin(9600);
  Serial.println();
  printBanner();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  /* Inicializa o display LCD. */
  lcd.begin();
  lcd.backlight();
  lcd.clear();

  /* Estabelece conexão WIFI. */
  wifi.connect();

  /* Inicializa cliente MQTT. */
  mqttClient.connect();
  mqttClient.setCallback(callback);

  /* TODO: verificar a necessidade de se inscrever em outros tópicos. */
  mqttClient.subscribe(subscribeTopic);

  lcd.print("Hello, DBLab. ;)s");
  digitalWrite(LED_BUILTIN, HIGH);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  mqttClient.loop();
}

/* Função chamada quando receber uma mensagem em um tópico inscrito. */
void callback(char *topic, byte *payload, unsigned int length)
{
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = 0;

  Serial.print("Mensagem recebida no tópico ");
  Serial.print(topic); Serial.print(": ");
  Serial.println(message);

  lcd.clear(); 
  lcd.home();
  lcd.print(message);

  /* TODO: Implementar esta função de acordo com a necessidade.
   *   Dica: pesquisar métodos da classe no código-fonte. */
   
  Serial.println();
}

