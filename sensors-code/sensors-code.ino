#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include "config.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* websocket_server = "http://192.168.129.7:8081/sockets/test"; // Adresse du serveur WebSocket

using namespace websockets;

WebsocketsClient client;

void setup() {
    Serial.begin(9600);

    // Connexion au réseau WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");

    // Connexion au serveur WebSocket
    bool connected = client.connect(websocket_server);
    if (connected) {
        Serial.println("Connected to WebSocket server");
        client.send("Hello Server");
    } else {
        Serial.println("Connection to WebSocket server failed");
    }

    // Définition de la fonction de rappel pour la réception des messages
    client.onMessage([&](WebsocketsMessage message) {
        Serial.print("Received message: ");
        Serial.println(message.data());
    });
}

void loop() {
    // Permettre au client WebSocket de vérifier les messages entrants
    //client.poll();
    
    // Lire les données de l'Arduino via RX/TX et les envoyer via WebSocket
    readDataFromArduino();
    
    //delay(500);
}

void sendDataToWebSocket(String data) {
     client.send(data);
}

void readDataFromArduino() {
    // Lire les données du port série (RX/TX) de l'Arduino
    if (Serial.available()) {
        String data = Serial.readString();
        Serial.println(data);
        // Envoyer les données lues via WebSocket
        sendDataToWebSocket(data);
    }
}
