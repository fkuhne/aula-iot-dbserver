/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 3.1: CLIENTE MQTT SIMPLES 
 * 
 * Este código cria um cliente MQTT, conecta-se em um broker, e
 *   envia dados simples a ele.
 *
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 */

#include "wifi.h"
#include "mqtt.h"

WFclass wifi;

const String publishTopic("dblab/hands-on/mqtt/out/211");
const String mqttServer("iot.eclipse.org");
const int mqttServerPort = 1883;

MqttClient mqttClient(mqttServer, mqttServerPort);

long lastTimeMsg = 0;

#include <hcsr04.h>

#define TRIG_PIN D5
#define ECHO_PIN D6

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);

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

  wifi.connect();
  mqttClient.connect();
  
  digitalWrite(LED_BUILTIN, HIGH);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  if(!mqttClient.connected()) mqttClient.connect();
  mqttClient.loop();

  long now = millis();
  if (now - lastTimeMsg > 1000)
  {
    lastTimeMsg = now;

    Serial.println();
    
    /* Publica um "Hello World" a cada 2 segundos... */
    String message("D: ");
    message += String(hcsr04.distanceInMillimeters());
    mqttClient.publish(publishTopic, message);

    Serial.println("Mensagem publicada: " + message);
    
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
