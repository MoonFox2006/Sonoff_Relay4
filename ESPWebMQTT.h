#ifndef __ESPWEBMQTT_H
#define __ESPWEBMQTT_H

#include "ESPWeb.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char defMQTTClient[] PROGMEM = "ESP8266_"; // Префикс имени клиента для MQTT-брокера по умолчанию
const uint16_t defMQTTPort = 1883; // Порт MQTT-брокера по умолчанию

const char pathMQTT[] PROGMEM = "/mqtt"; // Путь до страницы конфигурации параметров MQTT

// Имена JSON-переменных
const char jsonMQTTConnected[] PROGMEM = "mqttconnected";

// Имена параметров для Web-форм
const char paramMQTTServer[] PROGMEM = "mqttserver";
const char paramMQTTPort[] PROGMEM = "mqttport";
const char paramMQTTUser[] PROGMEM = "mqttuser";
const char paramMQTTPassword[] PROGMEM = "mqttpswd";
const char paramMQTTClient[] PROGMEM = "mqttclient";

class ESPWebMQTTBase : public ESPWebBase { // Расширение базового класса с поддержкой MQTT
public:
  ESPWebMQTTBase();

  PubSubClient* pubSubClient; // Клиент MQTT-брокера

protected:
  void setupExtra();
  void loopExtra();
  uint16_t readConfig();
  uint16_t writeConfig(bool commit = true);
  void defaultConfig(uint8_t level = 0);
  bool setConfigParam(const String& name, const String& value);
  void setupHttpServer();
  void handleRootPage();
  virtual void handleMQTTConfig(); // Обработчик страницы настройки параметров MQTT
  String jsonData(); // Формирование JSON-пакета данных

  virtual String btnMQTTConfig(); // HTML-код кнопки параметров MQTT
  String navigator();

  virtual bool mqttReconnect(); // Восстановление соединения с MQTT-брокером
  virtual void mqttCallback(char* topic, byte* payload, unsigned int length); // Callback-функция, вызываемая MQTT-брокером при получении топика, на которое оформлена подписка
  virtual void mqttResubscribe(); // Осуществление подписки на топики
  bool mqttSubscribe(const String& topic); // Хэлпер для подписки на топик
  bool mqttPublish(const String& topic, const String& value, bool retained = true); // Хэлпер для публикации топика

  WiFiClient* _espClient;
  String _mqttServer; // MQTT-брокер
  uint16_t _mqttPort; // Порт MQTT-брокера
  String _mqttUser; // Имя пользователя для авторизации
  String _mqttPassword; // Пароль для авторизации
  String _mqttClient; // Имя клиента для MQTT-брокера (используется при формировании имени топика для публикации в целях различия между несколькими клиентами с идентичным скетчем)
};

#endif
