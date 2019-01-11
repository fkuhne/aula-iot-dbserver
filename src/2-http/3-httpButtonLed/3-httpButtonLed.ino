/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 2.3: SERVIÇO HTTP PARA COMUNICAÇÃO ENTRE DISPOSITIVOS
 * 
 * Este código age como um servidor e cliente HTTP ao mesmo tempo. Como
 *   servidor, ele disponibiliza um LED para ser controlado pela internet,
 *   aguardando clientes conectarem-se e enviarem requisições. Como cliente,
 *   ele envia requisições GET para outro servidor, a partir do estado de
 *   seu botão.
 * 
 * Aqui, continuamos usando os paradigmas de programação orientada a objetos e 
 *   programação orientada a eventos, como visto no exemplo anterior.
 *   
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 */

#include "wifi.h"
#include "httpService.h"
#include "httpClient.h"

#define LED_PIN D5
#define BUTTON_PIN D0 /* D3 é o botão Flash. */

/* TODO: Coloque aqui o endereço IP do host contendo
 *   o LED que queremos acionar. */
const char *host = "";

bool currentButtonState = LOW;

/* Instancia o cliente Wi-Fi. */
WFclass wifi;

/* Instancia um serviço web. */
HttpService httpService;

/* Instancia um cliente web. */
HttpClient httpClient;

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

  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, LOW);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  /* Cria cliente Wi-Fi e conecta-o à rede disponível. */
  wifi.connect();

  /* Configura callback quando a rota /led é chamada. */
  httpService.on("/led", httpHandler);
  httpService.start();

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
  httpService.handleClient();

  /* Verifica se estado do botão mudou. */
  int buttonState = digitalRead(BUTTON_PIN);
  if(buttonState != currentButtonState)
  {
    /* Aguarda um pouco para filtrar o ruído... */
    delay(50);
    buttonState = digitalRead(BUTTON_PIN);
    if(buttonState != currentButtonState)
    {
      currentButtonState = buttonState;
      
      String state;
      if(buttonState == HIGH) state = "on";
      else state = "off";

      httpClient.sendRequest(state, host);      

      Serial.println("Botão está agora " + state);  
      Serial.println();
    }
  }

  delay(10); /* Dá um tempo para o processador respirar... */
}

/* Função chamada para tratar requisição HTTP do cliente. */
void httpHandler()
{
  digitalWrite(LED_BUILTIN, LOW);

  String state;
  String argument("state");
  httpService.httpHandler(argument, state);

  if(state == "on") digitalWrite(LED_PIN, HIGH);
  else if(state == "off") digitalWrite(LED_PIN, LOW);

  Serial.println("Led está agora " + state);
  Serial.println();

  digitalWrite(LED_BUILTIN, HIGH);
}

