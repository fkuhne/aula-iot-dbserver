#include "wifi.h"
#include "mqtt.h"

#define LED_PIN D5 //LED_BUILTIN
#define BUTTON_PIN D0 //D3 is the 'Flash' button

WFclass wifi;

const String publishTopic("dblab/hands-on/mqtt/out");
const String subscribeTopic("dblab/hands-on/mqtt/in");
const String mqttServer("emqx.dbserver.com.br");
const int mqttServerPort = 1883;
MqttClient mqttClient(mqttServer, mqttServerPort);

int currentButtonState = LOW;

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

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, LOW);

  wifi.connect();

  /* Atenção: chamadas às funções subscribe e setCallback precisam
   *  ser posteriores à chamada à função connect. */
  mqttClient.connect();
  mqttClient.subscribe(subscribeTopic);
  mqttClient.setCallback(callback);
    
  digitalWrite(LED_BUILTIN, HIGH);
}

/* Função chamada quando receber uma mensagem em um tópico inscrito. */
void callback(char *topic, byte *payload, unsigned int length)
{
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = 0;

  Serial.println("Mensagem \"" + String(message) + "\" recebida no tópico \"" + String(topic) + "\"");

  if (!strncmp(message, "on", 2)) digitalWrite(LED_PIN, HIGH);
  else if (!strncmp(message, "off", 3)) digitalWrite(LED_PIN, LOW);
}

void loop()
{
  if (!mqttClient.connected())
  {
    mqttClient.connect();
    mqttClient.setCallback(callback);
    mqttClient.subscribe(subscribeTopic);
  }
  mqttClient.loop();

  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != currentButtonState)
  {
    delay(50);
    buttonState = digitalRead(BUTTON_PIN);
    if (buttonState != currentButtonState)
    {
      currentButtonState = buttonState;

      String message("O botão está");
      if (buttonState == HIGH) message += String(" ligado.");
      else message += String(" desligado.");

      mqttClient.publish(publishTopic, message);

      /* TODO: publique o estado do botão no tópico de entrada,
           com mensagens "on" e "off". */
      if (buttonState == HIGH) mqttClient.publish(subscribeTopic, "on");
      else mqttClient.publish(subscribeTopic, "off");
    }
  }

  delay(10); /* Dá um tempo para o processador respirar... */
}
