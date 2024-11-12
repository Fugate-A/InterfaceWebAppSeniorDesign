#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsClient.h>

// Access Point Credentials
const char* apSsid = "ChairGuru";
const char* apPassword = "123456789";

// Custom IP configuration for the AP
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// WebSocket client for the server (192.168.4.2)
WebSocketsClient webSocketServer;

// WebSocket client for the combo ESP32 (192.168.4.3)
WebSocketsClient webSocketCombo;

// Create a WebServer object on port 80
WebServer server(80);

// Function to forward command to the combo ESP32
void forwardCommandToCombo(const String& message) {
    Serial.print("Forwarding message to combo ESP32: ");
    Serial.println(message);

    // Create a modifiable String object and send it via WebSocket
    String modifiableMessage = message;
    webSocketCombo.sendTXT(modifiableMessage);
}

// WebSocket event handler for the server
void webSocketServerEvent(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.println("WebSocket disconnected from server");
            break;
        case WStype_CONNECTED:
            Serial.println("WebSocket connected to server at 192.168.4.2");
            webSocketServer.sendTXT("ESP32 Access Point connected to server");
            break;
        case WStype_TEXT:
            // Handle incoming message from the server
            Serial.print("Message received from server: ");
            Serial.println((char*)payload);
            forwardCommandToCombo(String((char*)payload)); // Forward the message to combo ESP32
            break;
        case WStype_ERROR:
            Serial.println("WebSocket error occurred with server");
            break;
        default:
            break;
    }
}

// WebSocket event handler for the combo ESP32
void webSocketComboEvent(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.println("WebSocket disconnected from combo ESP32");
            break;
        case WStype_CONNECTED:
            Serial.println("WebSocket connected to combo ESP32 at 192.168.4.3");
            break;
        case WStype_ERROR:
            Serial.println("WebSocket error occurred with combo ESP32");
            break;
        default:
            break;
    }
}

void setup() {
    Serial.begin(115200);

    // Configure the ESP32 as an access point
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(apSsid, apPassword);
    Serial.print("Access Point IP address: ");
    Serial.println(WiFi.softAPIP());

    // Start HTTP server for testing purposes
    server.on("/", []() {
        server.send(200, "text/plain", "ESP32 WebSocket Access Point");
    });
    server.begin();

    // Connect to the WebSocket server at 192.168.4.2
    webSocketServer.begin("192.168.4.2", 8081, "/"); // Server IP address and port
    webSocketServer.onEvent(webSocketServerEvent);
    webSocketServer.setReconnectInterval(5000); // Retry connection every 5 seconds

    // Connect to the WebSocket combo ESP32 at 192.168.4.3
    webSocketCombo.begin("192.168.4.3", 80, "/ws"); // Combo ESP32 WebSocket endpoint
    webSocketCombo.onEvent(webSocketComboEvent);
    webSocketCombo.setReconnectInterval(2500); // Retry connection every 5 seconds
}

void loop() {
    server.handleClient();
    webSocketServer.loop();
    webSocketCombo.loop();
}
