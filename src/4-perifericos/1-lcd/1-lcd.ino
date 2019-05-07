/*
   DBLab - DBServer
   Oficina prática de Internet das Coisas

   06/2018


   EXERCÍCIO 1 PERIFÉRICOS: DISPLAY LCD.

   Dependências:
    LiquidCrystal_I2C from DFRobot
      - Baixar do Github e instalar manualmente https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

   Procure pelos TODO's no código e complete com a função necessária para
     implementar a função referida.
*/

#include <LiquidCrystal_I2C.h>
#include "wifi.h"
#include "mqtt.h"

WFclass wifi;

// Configura o LCD display. Pinos: D2: SDA, D1: SCL
LiquidCrystal_I2C lcd(0x27, 16, 2);

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

  /* Inicializa o display LCD. */
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  
  lcd.print("Hello, DBLab. ;)");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
     do programa. */
void loop()
{
}
