/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .cpp, implementação da classe wifi.
 *
 */
 
/* ------------------- ESP8266Webservice_CLASS ------------------- */
#include "httpService.h"

// Contrutor da classe
HttpService::HttpService()
{
    httpServer = new ESP8266WebServer(80);
}

// Inicializa WebServer
void HttpService::start()
{
  httpServer->begin();    
  Serial.println("Servidor HTTP rodando...");
}

// Define rotas httpHandler
void HttpService::on(const char *route, void (*func)())
{
  httpServer->on(route, func);
}

// Manipula requisições de clientes
void HttpService::handleClient()
{
  httpServer->handleClient();
}

// httpHandler
void HttpService::httpHandler(String &argument, String &state)
{
  Serial.print("Recebendo requisição de ");
  Serial.println(httpServer->client().remoteIP());
  
  /* o servidor recebe argumentos na forma: '/led?argument=state'. */
  state = httpServer->arg(argument);
  httpServer->send(200, "text/plain", argument + " = " + state);
}

