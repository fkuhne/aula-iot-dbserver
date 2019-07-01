#include "wifi.h"
#include "mqtt.h"
#include <Wire.h> //I2C Arduino Library
#define addr 0x1E //I2C Address for The HMC5883

WFclass wifi;

const String publishTopic("dblab/hands-on/mqtt/bussolaout");
const String subscribeTopic("dblab/hands-on/mqtt/bussolain");
const String mqttServer("emqx.dbserver.com.br");
const int mqttServerPort = 1883;
MqttClient mqttClient(mqttServer, mqttServerPort);

/* Função de configuração. Ela é executada uma única vez no início da execução
     do programa. */

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(addr);
  Wire.write(0x02);
  Wire.write(0x00); //Continuously Measure
  Wire.endTransmission();
  wifi.connect();
  /* Atenção: chamadas às funções subscribe e setCallback precisam
      ser posteriores à chamada à função connect. */
  mqttClient.connect();
  mqttClient.subscribe(subscribeTopic);

}

void loop()
{
  if (!mqttClient.connected())
  {
    mqttClient.connect();
    mqttClient.subscribe(subscribeTopic);
  }
  mqttClient.loop();

  int x, y, z; //triple axis data
  Wire.beginTransmission(addr);
  Wire.write(0x03);
  Wire.endTransmission();
  //Read the data
  Wire.requestFrom(addr, 6);
  if (6 <= Wire.available())
  {
    x = Wire.read() << 8; //MSB  x
    x |= Wire.read(); //LSB  x
    z = Wire.read() << 8; //MSB  z
    z |= Wire.read(); //LSB z
    y = Wire.read() << 8; //MSB y
    y |= Wire.read(); //LSB y
  }
  // Show Values
  //  Serial.print("X Value: ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(",  ");
  Serial.println(z);
  Serial.println();
  delay(1000);

  String a ("Coordenadas X: " +String (x) + ",Y: " +String(y) + ",Z: " + String(z));
  mqttClient.publish(publishTopic, a);

  /* TODO: publique o estado do botão no tópico de entrada,
       com mensagens "on" e "off". */
}
