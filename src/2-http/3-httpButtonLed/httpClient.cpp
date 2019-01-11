/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .cpp, implementação da classe ESP8266WebserviceClient_CLASS.
 *
 */
 
/* ------------------- ESP8266WebserviceClient_CLASS ------------------- */
#include "HttpClient.h"

void HttpClient::sendRequest(String &state, const char *host)
{
  /* Monta URI para a requisição. */
  String url = "/led?state=" + state;

  Serial.print("Enviando requisição para o host ");
  Serial.println(host);
  Serial.println("GET URL: " + url);

  wifiClient.connect(host, 80);
  wifiClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");

  wifiClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");
}

