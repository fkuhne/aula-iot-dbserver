/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .h, header, define da interface dos
 * metodos publicos, variáveris e constantes 
 * privadas da classe ESP8266WebserviceClient_CLASS.
 *
 */
 
/* ------------------- ESP8266WebserviceClient_CLASS ------------------- */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class HttpClient
{
    public:
      HttpClient() {} // Construtor. Não faz nada
      void sendRequest(String &state, const char* host); // Envia requisião para o serviço HTTP
    private:
      WiFiClient wifiClient;
};

