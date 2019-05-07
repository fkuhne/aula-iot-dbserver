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
#include <hcsr04.h>

#define TRIG_PIN D5
#define ECHO_PIN D6

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
  digitalWrite(LED_BUILTIN, LOW);
  
  digitalWrite(LED_BUILTIN, HIGH);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  /* A cada 500 milisegundos publica-se a distância lida pelo sensor. */
  long now = millis();  
  if (now - lastTimeMsg > 1000)
  {
    lastTimeMsg = now;
    
    Serial.println(hcsr04.distanceInMillimeters());
   
  }
}

