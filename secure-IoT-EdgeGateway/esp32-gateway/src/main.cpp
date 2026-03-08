#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "YOUR_WIFI";
const char* WIFI_PASS = "YOUR_PASS";
const char* MQTT_HOST = "broker.hivemq.com";
const int   MQTT_PORT = 1883;
const char* MQTT_TOPIC = "secure-edgegateway/sensor";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void connectWiFi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
}

void connectMQTT()
{
    while (!mqttClient.connected())
    {
        String clientId = "esp32-gateway-";
        clientId += String((uint32_t)ESP.getEfuseMac(), HEX);
        mqttClient.connect(clientId.c_str());
        delay(500);
    }
}

void setup()
{
    Serial.begin(115200);
    connectWiFi();
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);
}

void loop()
{
    if (!mqttClient.connected())
    {
        connectMQTT();
    }

    mqttClient.loop();

    if (Serial.available())
    {
        String data = Serial.readStringUntil('\n');
        data.trim();

        if (data.length() > 0)
        {
            mqttClient.publish(MQTT_TOPIC, data.c_str());
        }
    }
}