#include <WiFi.h>
#include <WebSocketsClient.h>

// Replace these with your network credentials
const char* ssid     = "Your_SSID";     
const char* password = "Your_PASSWORD";

// WebSocket server details
const char* websockets_server_host = "your-server-ip";  // Replace with your server IP or domain
const uint16_t websockets_server_port = 8081;           // Replace with the WebSocket server port
const char* websockets_server_path = "/";               // If using a specific WebSocket path, update it here

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket Disconnected");
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket Connected");
      // Send identifier to the server when connected
      webSocket.sendTXT("ESP32_CONNECTED");
      break;
    case WStype_TEXT:
      // Handle incoming message from the server
      Serial.printf("Received from server: %s\n", payload);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  
  // Connect to WebSocket server
  webSocket.begin(websockets_server_host, websockets_server_port, websockets_server_path);
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // Keep WebSocket connection alive
  webSocket.loop();
}
