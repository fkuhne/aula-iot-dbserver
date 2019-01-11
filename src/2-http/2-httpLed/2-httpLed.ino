/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 2.2: SERVIÇO HTTP PARA CONTROLE DO LED
 * 
 * Este código cria um serviço HTTP e conecta-se à rede Wi-Fi disponível.
 *
 * Uma página web estará disponível no IP correspondente ao dispositivo. Abra 
 *   um navegador e digite o IP na barra de endereço.
 *
 * Aqui, continuamos usando os paradigmas de programação orientada a objetos e 
 *   programação orientada a eventos, como visto no exemplo anterior.
 *   
 * A novidade é que agora a página, servida por este dispositivo, pode enviar
 *   requisições 'GET' ao servidor. Usaremos isto para controlar o estado de um LED.
 *   
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 * 
 */
 
#include <ESP8266WebServer.h>
#include "wifi.h"

#define LED_PIN D5

/* Define web server na porta 80 com HTTP */
ESP8266WebServer server(80);

/* Instancia o cliente Wi-Fi. */
WFclass wifi;

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

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  /* Cria cliente Wi-Fi e conecta-o à rede disponível. */
  wifi.connect();

  /* Registrando as funções de callback para as rotas desejadas: */  
  server.on("/", handleRoot); /* Rota raiz. */

  /* TODO: adicione callbacks para as rotas '/on' e '/off'. */
  
  /* Finalmente inicializa o servidor webserver, com as configurações feitas. */
  server.begin();
  Serial.println("Servidor HTTP rodando...");

  digitalWrite(LED_BUILTIN, HIGH);
}
 
/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  server.handleClient();
}
  
/* Função chamada quando cliente faz requisição URI de '/',
 * ela envia o status HTTP 200 (OK) e um texto para o 
 * browser ou cliente. (obs. status http 404 (error).) */
void handleRoot()
{
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Recebendo requisição de ");
  Serial.println(server.client().remoteIP());
  
  String webString =
  "<!DOCTYPE HTML><html><head>"
  "<meta name='apple-mobile-web-app-capable' content='yes'>"
  "<style>body{background-color:#4285F4;font-size:60px;font-family:verdana;}</style>"
  "<script>"
  "function on(){window.location.assign('/on')}"
  "function off(){window.location.assign('/off')}"
  "</script>"
  "</head>"
  "<body><center>"
  "<div><bold>DBLab</bold></br>Oficina de Internet das Coisas</div></br>"
  "</br><div><input type='button' style='font-size:80px' value='ON' onclick='on()'></br></br>"
  "<input type='button' style='font-size:80px' value='OFF' onclick='off()'></div>"
  "</center></body></html>";  
  server.send(200, "text/html", webString);

  digitalWrite(LED_BUILTIN, HIGH);
}

/* Função (callback) que é executada quando a rota '/on' é acessada. Neste caso,
 *   o LED está sendo ligado. */
void handleLedOn()
{
  digitalWrite(LED_PIN, HIGH);
  handleRoot();
}

/* Função (callback) que é executada quando a rota '/off' é acessada. Neste caso,
 *   o LED está sendo desligado. */
void handleLedOff()
{
  digitalWrite(LED_PIN, LOW);
  handleRoot();
}

