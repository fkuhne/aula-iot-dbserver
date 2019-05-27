/*
 * DBLab - DBServer
 * IOTAR
 *
 * Arquivo .cpp, implementação da classe MqttClient.
 *
 * 10/2018
 */
  
/* ------------------- MqttClient ------------------- */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class MqttClient
{
  public:
    MqttClient(const String &mqttServer, const int mqttPort); // Construtor
    void connect(); // Funcão para efetuar conexão com servidor mqtt
    int connected(); // Função para verificar conexão
    void loop(); // Função de repetição

    void setCallback(void (*callback)(char*, uint8_t*, unsigned int)); // Configura callback para tratar mensagens
    boolean subscribe(const String &topic); // Inscrição em um tópico
    boolean unsubscribe(const String &topic); // Desinscrição em um tópico
    boolean publish(const String &topic, const String &payload); // Função para publicar mensagens

  private:
    String _mqttServer;
    int _mqttPort;
    String _deviceId;
    
    WiFiClient wifiClient;
    PubSubClient* mqttClient;
};

