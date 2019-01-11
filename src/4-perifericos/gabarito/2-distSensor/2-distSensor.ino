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
 */

#include "wifi.h"
#include "mqtt.h"

#define TRIG_PIN D5
#define ECHO_PIN D6

WFclass wifi;

const String publishTopic("dblab/hands-on/mqtt/distance/out");
const String mqttServer("iot.eclipse.org");
const int mqttServerPort = 1883;
MqttClient mqttClient(mqttServer, mqttServerPort);

/* Speed of sound is 343 m/s, or 0.343 mm/us. */
const double soundSpeed = 0.340; //343 * 1000.0 / 1000000.0;

int lastTimeMsg = 0;

long readUltrasonicDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long distance = pulseIn(ECHO_PIN, HIGH);
  return distance;
}

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
 *   do programa. */
void loop()
{
  mqttClient.loop();

  /* A cada 500 milisegundos publica-se a distância lida pelo sensor. */
  long now = millis();  
  if (now - lastTimeMsg > 500)
  {
    lastTimeMsg = now;
   
    /* Divide por dois, pois o pulso de som vai e volta. */
    double distance = (soundSpeed / 2) * readUltrasonicDistance();
    String mm = String(distance);
    String msg = String("Dist: " + mm + "mm");

    Serial.println(msg);
    mqttClient.publish(publishTopic, msg);
  }
}
