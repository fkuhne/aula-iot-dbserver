/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 09/2018
 *
 * EXERCÍCIO 4.1: SENSOR DE MOVIMENTO RCWL-0516 E CLIENTE MQTT 
 * 
 * Este código cria um cliente MQTT, conecta-se em um broker, e
 *   envia dados simples a ele.
 */

#include "wifi.h"
#include "mqtt.h"

#define SENSOR_PIN D4

WFclass wifi;

const String publishTopic("dblab/hands-on/mqtt/doppler/out");
const String mqttServer("iot.eclipse.org");
const int mqttServerPort = 1883;
MqttClient mqttClient(mqttServer, mqttServerPort);

long lastTime = 0;
int lastSensorState = LOW;

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

void loop()
{
  mqttClient.loop();

  long now = millis();

  boolean sensorState = (boolean)digitalRead(SENSOR_PIN);
  digitalWrite(LED_BUILTIN, !sensorState);

  if (lastSensorState != sensorState)
  {
    lastSensorState = sensorState;

    String message("O sensor está");
    if (sensorState == true) message += String(" ligado.");
    else message += String(" DESLIGADO!");

    mqttClient.publish(publishTopic, message);

    Serial.println(message);
  }
}

