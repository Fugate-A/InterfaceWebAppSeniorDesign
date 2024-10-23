#include <WiFi.h>
#include <WebSocketsClient.h>

//look into dns server esp32 library
//look into http client

const char* ssid = "Hello There";     // Your WiFi SSID
const char* password = "General Kenobi"; // Your WiFi Password

// WebSocket server details
const char* websockets_server_host = "192.168.137.1";  // Replace with your WebSocket server IP
const uint16_t websockets_server_port = 8081;           // Replace with the WebSocket server port
const char* websockets_server_path = "/";               // WebSocket server path

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
      // Handle incoming message (commands from the WebSocket server)
      Serial.printf("Received command: %s\n", (char*)payload);

      // Check if the command is "MOVE_CHAIRS" or any other command sent from the web app
      if (strcmp((char*)payload, "MOVE_CHAIRS") == 0) {
        Serial.println("Executing MOVE_CHAIRS command...");
        // Here, add the logic to handle the MOVE_CHAIRS command (e.g., move motors)
      }
      break;
  }
}

void setup() {
  // Start Serial communication
  Serial.begin(115200);
  delay(1000); // Give some time for the Serial Monitor to start

  Serial.println();
  Serial.println("======================================");
  Serial.println("      ESP32 WiFi Connection");
  Serial.println("======================================");
  
  // Begin WiFi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  // Wait until the ESP32 is connected to the WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Connection successful
  Serial.println();
  Serial.println("======================================");
  Serial.println("       Connected to WiFi!");
  Serial.print("       IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("======================================");

  // Connect to WebSocket server
  webSocket.begin(websockets_server_host, websockets_server_port, websockets_server_path);
  webSocket.onEvent(webSocketEvent); // Register WebSocket event handler
}

void loop() {
  // Keep WebSocket connection alive
  webSocket.loop();

  // Monitor the WiFi connection status
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost! Attempting to reconnect...");
    
    // Try to reconnect
    WiFi.disconnect();
    WiFi.begin(ssid, password);

    // Wait until the connection is reestablished
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    // Connection reestablished
    Serial.println();
    Serial.println("Reconnected to WiFi!");
    Serial.print("New IP Address: ");
    Serial.println(WiFi.localIP());
  }

  delay(5000); // Check connection status every 5 seconds
}
