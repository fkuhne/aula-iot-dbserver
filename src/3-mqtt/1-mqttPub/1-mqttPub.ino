/*
   DBLab - DBServer
   Oficina prática de Internet das Coisas

   06/2018


   EXERCÍCIO 3.1: CLIENTE MQTT SIMPLES

   Este código cria um cliente MQTT, conecta-se em um broker, e
     envia dados simples a ele.

   Procure pelos TODO's no código e complete com a função necessária para
     implementar a função referida.
*/

#include "wifi.h"
#include "mqtt.h"

WFclass wifi;

const String publishTopic("dblab/hands-on/mqtt/out");
const String mqttServer("emqx.dbserver.com.br");
const int mqttServerPort = 1883;

MqttClient mqttClient(mqttServer, mqttServerPort);

int value = 0;
long lastTimeMsg = 0;

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
     do programa. */
void setup()
{
  Serial.begin(9600);
  Serial.println();
  printBanner();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  wifi.connect();
  mqttClient.connect();

  digitalWrite(LED_BUILTIN, HIGH);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
     do programa. */
void loop()
{
  if (!mqttClient.connected()) mqttClient.connect();
  mqttClient.loop();

  long now = millis();
  if (now - lastTimeMsg > 2000)
  {
    lastTimeMsg = now;

    /* Publica um "Hello World" a cada 2 segundos... */
    ++value;
    String message("Hello World! #");
    message += String(value, DEC);
    mqttClient.publish(publishTopic, message.c_str());

    Serial.println("Mensagem publicada: " + message);

    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}


