/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 *
 * EXERCÍCIO 2.1: SERVIÇO HTTP E CLIENTE WI-FI
 * 
 * Este código cria um serviço HTTP e conecta-se à rede Wi-Fi disponível.
 * 
 * Aqui, utiliza-se dois conceitos importantes em programação:
 *   - Programação orientada a eventos, onde uma função (callback) é
 *   executada toda vez que um determinado evento ocorre. Neste caso, toda
 *   vez que um site é acessado por um cliente (browser), o programa
 *   responde com o conteúdo requisitado. Ver função handleRoot() e server.on().
 *   - Programação orientada a objetos: é quando utilizamos 'objetos' são
 *   utilizados para representar dados, atributos, métodos ou estados. Assim, ao
 *   se criar um novo objeto de um determinado tipo, aquela variável passa a possuir
 *   todos os atributos e métodos associados ao seu tipo de objeto. Ver, por exemplo,
 *   o objeto ESP8266WebServer e seus métodos begin, on e send. 
 *
 * Uma página web estará disponível no IP correspondente ao dispositivo. Abra 
 *   um navegador e digite o IP na barra de endereço.
 *
 * Procure pelos TODO's no código e complete com a função necessária para
 *   implementar a função referida.
 */
 
#include <ESP8266WebServer.h>
#include "wifi.h"

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

  /* Cria cliente Wi-Fi e conecta-o à rede disponível. */
  wifi.connect();

  /* Registro de callback para acesso à rota raiz. */
  server.on("/", handleRoot);

  /* Finalmente inicializa o servidor webserver, com as configurações feitas. */
  server.begin();
  Serial.println("Servidor HTTP rodando...");
  
  digitalWrite(LED_BUILTIN, HIGH);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop(void)
{
  server.handleClient(); // Espera por requisições HTTP de clientes.
}

/* Função chamada quando cliente faz requisição URI de '/',
 * ela envia o status HTTP 200 (OK) e um texto para o 
 * browser ou cliente. (obs. status http 404 (error).) */
void handleRoot() 
{
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.print("Cliente ");
  Serial.print(server.client().remoteIP());
  Serial.println(" conectado.");
  
  server.send(200, "text/plain", "Ola DBLab! ;)");
  
  digitalWrite(LED_BUILTIN, HIGH);
}

