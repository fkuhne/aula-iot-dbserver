#include "wifi.h"
#include "mqtt.h"

WFclass wifi;

const String publishTopic("dblab/hands-on/mqtt/out/211");
const String mqttServer("emqx.dbserver.com.br");
const int mqttServerPort = 1883;

MqttClient mqttClient(mqttServer, mqttServerPort);

int value = 0;
long lastTimeMsg = 0;
int pino = A0;
float valor = 0;
String estadoLuz = "";

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
  mqttClient.loop();

  long now = millis();
  if (now - lastTimeMsg > 1000)
  {
    lastTimeMsg = now;
    
    /* Publica um "Hello World" a cada 2 segundos... */
    ++value;
    
    valor = analogRead(pino);
    String estadoLuz(valor);
    
    if (valor > 500){
      estadoLuz = "Luz Desligada";
    } else {
      estadoLuz = "Luz Ligada";
    }
   
    mqttClient.publish(publishTopic, estadoLuz.c_str());
    Serial.println("Mensagem publicada: " + estadoLuz);
    
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
