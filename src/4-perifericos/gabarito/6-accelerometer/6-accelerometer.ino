/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 09/2018
 *
 *
 * EXERCÍCIO 6 PERIFÉRICOS: ACELERÔMETRO ADXL345.
 * 
 * Referência:
 *   - https://learn.adafruit.com/adxl345-digital-accelerometer
 *
 * Dependências:
 *   - Adafruit ADXL345 library (https://github.com/adafruit/Adafruit_ADXL345)
 *   - Adafruit Unified Sensor Library (https://github.com/adafruit/Adafruit_Sensor) *  
 * 
 */

#include "wifi.h"
#include "mqtt.h"
#include <Adafruit_ADXL345_U.h>

WFclass wifi;

const String publishTopic("dblab/hands-on/mqtt/accelerometer/out");
const String mqttServer("iot.eclipse.org");
const int mqttServerPort = 1883;
MqttClient mqttClient(mqttServer, mqttServerPort);

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

long lastTime = 0;

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

  /* Inicializa e configura o sensor. */
  accel.begin();
  accel.setRange(ADXL345_RANGE_16_G);

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
  mqttClient.loop();
  
  long now = millis();
  if (now - lastTime > 1000)
  {
    lastTime = now;

    /* Get a new sensor event */
    sensors_event_t event;
    accel.getEvent(&event);

    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  "); Serial.println("m/s^2 ");

    String msg(event.acceleration.x);
    msg += ", ";
    msg += String(event.acceleration.y);
    msg += ", ";
    msg += String(event.acceleration.z);
    
    mqttClient.publish(publishTopic, msg);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}

