#include <WiFi.h>
#include <PubSubClient.h>

// Configurações - variáveis editáveis
const char* default_SSID = "Wokwi-GUEST"; // Nome da rede Wi-Fi
const char* default_PASSWORD = ""; // Senha da rede Wi-Fi
const char* default_BROKER_MQTT = "4.228.61.236"; // IP do Broker MQTT
const int default_BROKER_PORT = 1883; // Porta do Broker MQTT
const char* default_TOPICO_SUBSCRIBE = "/TEF/devin/cmd"; // Tópico MQTT de escuta
const char* default_TOPICO_PUBLISH_1 = "/TEF/devin/attrs/l"; // Tópico MQTT de envio de informações para Broker
const char* default_TOPICO_PUBLISH_2 = "/TEF/devin/attrs/s";
const char* default_ID_MQTT = "fiware_100"; // ID MQTT
const int default_LED_PIN = 2; // Pino do LED
const int default_PIR_PIN = 18; // Pino do PIR
const int default_LDR_PIN = 34; // Pino do LDR

const char* topicPrefix = "devin"; 

WiFiClient espClient;
PubSubClient MQTT(espClient);
char EstadoSaida = '0';

void initSerial() {
    Serial.begin(115200);
}

void initWiFi() {
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(default_SSID);
    reconectWiFi();
}

void initMQTT() {
    MQTT.setServer(default_BROKER_MQTT, default_BROKER_PORT);
    MQTT.setCallback(mqtt_callback);
}

void setup() {
    InitOutput();
    initSerial();
    initWiFi();
    initMQTT();
    delay(5000);
    MQTT.publish(default_TOPICO_PUBLISH_1, "s|on");
}

void loop() {
    VerificaConexoesWiFIEMQTT();
    EnviaEstadoOutputMQTT();
    handleLuminosity();
    MQTT.loop();
}

void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED)
        return;
    WiFi.begin(default_SSID, default_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Conectado com sucesso na rede ");
    Serial.print(default_SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for (int i = 0; i < length; i++) {
        char c = (char)payload[i];
        msg += c;
    }
    Serial.print("- Mensagem recebida: ");
    Serial.println(msg);
}

void VerificaConexoesWiFIEMQTT() {
    if (!MQTT.connected())
        reconnectMQTT();
    reconectWiFi();
}

void EnviaEstadoOutputMQTT() {
    int ldrValue = analogRead(default_LDR_PIN); // Lê o valor do LDR
    String payload = "{";
    payload += "\"LED\":\"";
    payload += (EstadoSaida == '1') ? "ON" : "OFF";
    payload += "\",\"LDR\":";
    payload += ldrValue;
    payload += "}";

    MQTT.publish(default_TOPICO_PUBLISH_1, payload.c_str());
    Serial.print("- Dados enviados ao MQTT: ");
    Serial.println(payload);
    delay(1000);
}

void InitOutput() {
    pinMode(default_LED_PIN, OUTPUT);
    pinMode(default_PIR_PIN, INPUT);
    pinMode(default_LDR_PIN, INPUT);
    digitalWrite(default_LED_PIN, LOW);  // LED começa apagado
}

void reconnectMQTT() {
    while (!MQTT.connected()) {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(default_BROKER_MQTT);
        if (MQTT.connect(default_ID_MQTT)) {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(default_TOPICO_SUBSCRIBE);
        } else {
            Serial.println("Falha ao reconectar no broker. Tentando novamente em 2s...");
            delay(2000);
        }
    }
}

void handleLuminosity() {
    int ldrValue = analogRead(default_LDR_PIN);  // Lê o valor do LDR
    Serial.print("Luminosidade: ");
    Serial.println(ldrValue);

    if (ldrValue < 500) {  // Se a luz ambiente for baixa
        int pirState = digitalRead(default_PIR_PIN); // Lê o PIR
        if (pirState == HIGH) {
            digitalWrite(default_LED_PIN, HIGH);  // Acende o LED
            EstadoSaida = '1';
            Serial.println("Luz baixa e movimento detectado, LED aceso!");
        } else {
            digitalWrite(default_LED_PIN, LOW);  // Apaga o LED
            EstadoSaida = '0';
        }
    } else {  // Luz ambiente alta
        digitalWrite(default_LED_PIN, LOW);  // Apaga o LED
        EstadoSaida = '0';
        Serial.println("Luz alta, LED apagado.");
    }
}
