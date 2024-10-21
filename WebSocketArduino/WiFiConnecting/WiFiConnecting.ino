#include <WiFi.h>
#include <WebSocketsClient.h>

// Replace these with your network credentials
const char* ssid     = "Hello There";     // Your WiFi SSID
const char* password = "General Kenobi"; // Your WiFi Password

// WebSocket server details (replace with your MERN stack server address and port)
const char* websockets_server_host = "your-server-ip-or-domain";  // e.g., 192.168.1.100 or your server domain
const uint16_t websockets_server_port = 8080; // Replace with the port you're using for WebSocket communication

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket Disconnected");
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket Connected to server");
      // Send a message to the server after connection
      webSocket.sendTXT("Hello from ESP32");
      break;
    case WStype_TEXT:
      // Handle incoming message
      Serial.printf("Received from server: %s\n", payload);

      // For example, echo the message back to the server
      webSocket.sendTXT("ESP32 received: " + String((char*)payload));
      break;
    case WStype_BIN:
      Serial.println("Received binary data");
      break;
    case WStype_PING:
      Serial.println("Received ping");
      break;
    case WStype_PONG:
      Serial.println("Received pong");
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Connect to WebSocket server
  webSocket.begin(websockets_server_host, websockets_server_port, "/ws"); // Replace "/ws" with your WebSocket endpoint

  // Assign WebSocket event handler
  webSocket.onEvent(webSocketEvent);

  // Optionally set WebSocket heartbeats for stability
  webSocket.enableHeartbeat(30000, 10000, 2);
}

void loop() {
  // Maintain WebSocket connection
  webSocket.loop();
}
