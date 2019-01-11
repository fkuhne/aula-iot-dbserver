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

#define SENSOR_PIN D4

boolean lastSensorState = false;

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

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
  boolean sensorState = (boolean)digitalRead(SENSOR_PIN);
  digitalWrite(LED_BUILTIN, !sensorState);

  if (lastSensorState != sensorState)
  {
    lastSensorState = sensorState;

    String message("O sensor está");
    if (sensorState == true) message += String(" ligado.");
    else message += String(" DESLIGADO!");

    Serial.println(message);
  }
}

