/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 09/2018
 *
 *
 * EXERCÍCIO 4.4: SERVIÇO HTTP COM WEBSOCKET E CLIENTE MQTT 
 * 
 * Este código cria um serviço HTTP e conecta-se à rede Wi-Fi disponível.
 *
 * Uma página web estará disponível no IP correspondente ao dispositivo. Abra 
 *   um navegador e digite o IP na barra de endereço.
 *   
 * Dados provenientes de sensores no laboratório serão publicados no site, e
 *   atualizados em intervalos de 1 segundo. Com o uso de websockets, o
 *   conteúdo do site atualizado automaticamente, sem a necessidade de o
 *   cliente requisitar (através de um novo GET).
 * 
 * Dependência:
 *   Biblioteca WebSockets (Markus Sattler) - instalar pela IDE do Arduino
 * Referências:
 *   https://www.hackster.io/brzi/nodemcu-websockets-tutorial-3a2013
 *   https://github.com/Links2004/arduinoWebSockets
 */

#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>

String WebPage = "<!DOCTYPE html><html><style>input[type=\"text\"]{width: 90%; height: 3vh;}input[type=\"button\"]{width: 9%; height: 3.6vh;}.rxd{height: 90vh;}textarea{width: 99%; height: 100%; resize: none;}</style><script>var Socket;function start(){Socket=new WebSocket('ws://' + window.location.hostname + ':81/');Socket.onmessage=function(evt){document.getElementById(\"rxConsole\").value =evt.data;}}</script><body onload=\"javascript:start();\"><div class=\"rxd\"><textarea id=\"rxConsole\" readonly></textarea></div></body></html>";

ESP8266WebServer server(80); /* Define web server na porta 80 com HTTP */
WebSocketsServer webSocket(81); /* Cria serviço de websocket na porta 81. */

long lastTimeMsg = 0; /* Variável de temporização. */

String temperature, humidity, distance; /* Variáveis para recebimento dos valores dos sensores. */

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

  server.on("/", [](){
    server.send(200, "text/html", WebPage);
  });
  server.begin();
  Serial.println("Servidor HTTP rodando...");

  webSocket.begin();
  Serial.println("Servidor websocket rodando...");
  
  digitalWrite(LED_BUILTIN, HIGH);
}
 
/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
 *   do programa. */
void loop()
{
  webSocket.loop();
  server.handleClient();

  long now = millis();
  if(now - lastTimeMsg > 500)
  {
    lastTimeMsg = now;

    temperature = String(random(10, 30));
    humidity = String(random(20, 90));
    distance = String(random(20, 2000));
    
    /* Publica dado no serviço websocket. */
    String message(temperature + "\n" + humidity + "\n" + distance);
    webSocket.broadcastTXT(message.c_str(), message.length());
  }
}

