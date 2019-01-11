/*
 * DBLab - DBServer
 * Oficina prática de Internet das Coisas
 *
 * 06/2018
 *
 * Arquivo .h, header, define da interface dos
 * metodos publicos, variáveris e constantes 
 * privadas da classe wifi.
 *
 */
 
/* ------------------- ESP8266Webservice_CLASS ------------------- */
#include <ESP8266WebServer.h>

class HttpService
{
  public:
    HttpService(); // Contrutor
    void start(); // Inicializa Webservice
    void on(const char* route, void (*func)()); // Define rotas httpHandler
    void handleClient(); // Handle Client
    void httpHandler(String &argument, String &state); // Http httpHandler

  private:
    ESP8266WebServer* httpServer;
};

//#endif
