#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsClient.h>
#include <esp_now.h>

// Access Point Credentials
const char* apSsid = "ESP32-Access-Point";
const char* apPassword = "123456789";

// Custom IP configuration for the AP
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// WebSocket client object
WebSocketsClient webSocket;

// Motor Controller ESP32's MAC Address
uint8_t motorControllerAddress[] = {0x0C, 0xB8, 0x15, 0x44, 0xF1, 0x00};

// Create a WebServer object on port 80
WebServer server(80);

// Function to send commands via ESP-NOW
void sendMotorCommand(String command) {
  esp_now_send(motorControllerAddress, (uint8_t *)command.c_str(), command.length());
}

// ESP-NOW send callback
void onSend(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "ESP-NOW Send Success" : "ESP-NOW Send Failure");
}

// WebSocket message handler to send commands to the motor controller
void handleWebSocketMessage(String message) {
  Serial.print("Received WebSocket message: ");
  Serial.println(message);

  // Forward command to motor controller ESP32
  sendMotorCommand(message);

  Serial.print("Sent move message to motor esp: ");
  Serial.println(message);

}

// WebSocket event handler
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket disconnected");
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket connected");
      webSocket.sendTXT("ESP32 connected to WebSocket server");
      break;
    case WStype_TEXT:
      handleWebSocketMessage((char*)payload);
      break;
    case WStype_ERROR:
      Serial.println("WebSocket error occurred");
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);

  // Set up the ESP32 as an access point
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(apSsid, apPassword);
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());

  // Initialize ESP-NOW and register send callback
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(onSend);

  // Add the motor controller ESP32 as a peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, motorControllerAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // Connect to WebSocket server
  webSocket.begin("192.168.4.2", 8081, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);

  // Start HTTP server
  server.on("/", []() {
    server.send(200, "text/plain", "ESP32 WebSocket and ESP-NOW Access Point");
  });
  server.begin();
}

void loop() {
  server.handleClient();
  webSocket.loop();
}
