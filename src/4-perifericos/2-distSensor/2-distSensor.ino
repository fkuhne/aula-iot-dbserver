/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 09/2018
 *
 *
 * EXERCÍCIO 2 PERIFÉRICOS: SENSOR DE DISTÂNCIA.
 * 
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 *
 *
 *https://github.com/jeremylindsayni/Bifrost.Arduino.Sensors.HCSR04
 */
 
#include <hcsr04.h>
#include "wifi.h"
#include "mqtt.h"

#define TRIG_PIN D5
#define ECHO_PIN D6

WFclass wifi;

const String publishTopic("dblab/hands-on/mqtt/distancia");
const String mqttServer("emqx.dbserver.com.br");
const int mqttServerPort = 1883;

MqttClient mqttClient(mqttServer, mqttServerPort);

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);

int lastTimeMsg = 0;

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
  pinMode(A0, INPUT);
  digitalWrite(LED_BUILTIN, LOW);

  wifi.connect();
  mqttClient.connect();
  
  digitalWrite(LED_BUILTIN, HIGH);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  if (!mqttClient.connected()) mqttClient.connect();
  mqttClient.loop();

  /* A cada 500 milisegundos publica-se a distância lida pelo sensor. */
  long now = millis();  
  if (now - lastTimeMsg > 1000)
  {
    lastTimeMsg = now;

    String message("D: ");
    int mm = hcsr04.distanceInMillimeters();
    int luminosidade = analogRead(A0);
    message += String(mm, DEC);
    message += String(" - L: ");
    message += String(luminosidade);
    Serial.println(message);

    if(mm > -1) {
      mqttClient.publish(publishTopic, message.c_str());
    }
  }
}
