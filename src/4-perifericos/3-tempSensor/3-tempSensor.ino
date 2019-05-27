/*
   DBLab - DBServer
   Oficina prática de Internet das Coisas

   06/2018


   EXERCÍCIO 4 PERIFÉRICOS: SENSOR DE TEMPERATURA.

   Procure pelos TODO's no código e complete com a função necessária para
     implementar a função referida.

*/

#include "wifi.h"
#include "mqtt.h"

const String publishTopic("dblab/hands-on/mqtt/out/210");
const String mqttServer("emqx.dbserver.com.br");
const int mqttServerPort = 1883;

WFclass wifi;
MqttClient mqttClient(mqttServer, mqttServerPort);

int value = 0;
long lastTimeMsg = 0;

#include <DHT.h>

#define MESSAGE_MAX_SIZE 50

#define LED_PIN D5
#define DHTPIN D1     // Define pino data do DHT.
#define DHTTYPE DHT11   // Define o modelo do DHT, 11 (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Inicializa sensor de temperatura DHT.

int lastTime = 0;

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

  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, LOW);

  pinMode(LED_PIN, OUTPUT);

  // Inicializa sensor de temperatura.
  dht.begin();
  wifi.connect();
  mqttClient.connect();

  //digitalWrite(LED_BUILTIN, HIGH);

}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
     do programa. */
void loop()
{
  if (!mqttClient.connected()) mqttClient.connect();
  mqttClient.loop();

  long now = millis();
  if (now - lastTime > 2000)
  {
    lastTime = now;

    /* Rotina para tratar valores lido pelo sensor e assim publicar via mqtt. */
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    char humidity[MESSAGE_MAX_SIZE] = "";
    char temperature[MESSAGE_MAX_SIZE] = "";

    snprintf (temperature, MESSAGE_MAX_SIZE, "T: %02dC", (int)temp);
    snprintf (humidity, MESSAGE_MAX_SIZE, "H: %02d%%", (int)hum);

    if ((int)temp < 100) {
      mqttClient.publish(publishTopic, String(temperature) + " | " + String(humidity));
    }
    
    if ((int)temp > 24) {
      blink(2);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
    Serial.println((int)temp);
    Serial.println(temperature);
    Serial.println(humidity);
  }
}
void blink(int times) {
    int i;
    for (i = 0; i < times; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(400);
      digitalWrite(LED_PIN, LOW);
      delay(300);
    }
}
