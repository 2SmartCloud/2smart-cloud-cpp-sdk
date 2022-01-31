#include "mqtt_client.h"

#include "utils/src/utils.h"

MqttClient::MqttClient() { CreateClient(); }

void MqttClient::CreateClient() {
    this->wifi_client_ = new WiFiClient;
    this->client_ = new PubSubClient(*wifi_client_);
    session_id_.append(RandomString(millis(), 24));
}

bool MqttClient::Init(String username, String host, String port, String password, MQTT_CALLBACK_SIGNATURE) {
    this->username_ = username;
    this->host_ = host;
    this->port_ = port;
    this->password_ = password;
    client_->setServer(this->host_.c_str(), this->port_.toInt());
    client_->setCallback(callback);
    client_->setSocketTimeout(SOCKET_CONNECTION_TIMEOUT_S);
    Serial.println("MqttClient::Init");
    return (this->Connect());
}

bool MqttClient::Connect() {
    Serial.print("MqttClient::Connect: ");
    Serial.println(session_id_.c_str());
    if (this->username_ == "") return false;
    if (this->IsConnected()) return true;
    if (!this->CheckConnection()) {
        Serial.println("Can't connect to remote host!");
        return false;
    }

    return client_->connect(session_id_.c_str(), this->username_.c_str(), this->password_.c_str(), 0, 0, 0, 0, 0);
}

bool MqttClient::Reconnect() {
    if (millis() - reconnect_mqtt_time_ < kDelayForReconnectMQTT_) return false;

    Serial.println("MqttClient::Reconnect");
    Serial.println(millis() - reconnect_mqtt_time_);
    Serial.println(kDelayForReconnectMQTT_);
    Serial.println(!this->IsConnected());

    if (!this->IsConnected()) {
        if (this->Connect()) {
            Serial.println("MQTT connected");
            mqtt_reconnected_ = true;
        } else {
            Serial.print("failed, rc=");
            Serial.print(client_->state());
            Serial.println(" try again in 5 seconds");
        }

        reconnect_mqtt_time_ = millis();
    }

    return this->IsConnected();
}

bool MqttClient::Subscribe(String topic) {  // subscribe to 1 topic
    return client_->subscribe(topic.c_str());
}

bool MqttClient::Publish(String topic, String payload, bool retained = 1) {  // publish to 1 topic
    if (!this->IsConnected()) return false;
    if (client_->publish(topic.c_str(), payload.c_str(), retained)) {
        return true;
    } else {
        Serial.printf("Err publishing %s\r\n", topic.c_str());
        return false;
    }
}

void MqttClient::MqttLoop() {
    if (!this->IsConnected()) Reconnect();

    client_->loop();
}

bool MqttClient::IsConnected() { return client_->connected(); }

bool MqttClient::IsReconnected() {
    if (mqtt_reconnected_) {
        mqtt_reconnected_ = false;
        return true;
    }

    return false;
}

// Check connection to host with custom timeout to prevent long loop stuck by PubSubClient::connect
bool MqttClient::CheckConnection() {
    int result = this->wifi_client_->connect(this->host_.c_str(), this->port_.toInt(), 1000);

    Serial.println("Mqtt::CheckConnection");

    this->wifi_client_->flush();
    this->wifi_client_->stop();

    Serial.println("Mqtt::CheckConnection flush");

    return static_cast<bool>(result);
}
