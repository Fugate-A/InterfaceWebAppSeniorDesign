#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsClient.h>
#include <HTTPClient.h>

// Access Point Credentials
const char* apSsid = "ChairGuru";
const char* apPassword = "123456789";

// Custom IP configuration for the AP
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

WebSocketsClient webSocket;

// Motor Controller IP Address
IPAddress motor_IP(192, 168, 4, 3); //guru1
//IPAddress motor2_IP(192, 168, 4, 4); //guru2

// Create a WebServer object on port 80
WebServer server(80);

// Function to send command to the motor controller via HTTP
void sendMotorCommand(const String& command, int value) {
  HTTPClient http;
  http.begin("http://192.168.4.3/move");  // Motor controller endpoint

  // Create JSON payload with command and value
  http.addHeader("Content-Type", "application/json");
  String payload = "{\"command\":\"" + command + "\", \"value\":" + String(value) + "}";

  int httpResponseCode = http.POST(payload);
  if (httpResponseCode > 0) {
    Serial.print("Motor HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Motor Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();  // Close HTTP connection
}

// WebSocket message handler to handle messages from the server and forward them to the motor ESP
void handleWebSocketMessage(String message) {
  Serial.print("Received WebSocket message: ");
  Serial.println(message);

  // Check if the message contains a comma (indicating a command and value)
  int commaIndex = message.indexOf(',');
  if (commaIndex == -1) {
    Serial.println("Error: Malformed WebSocket message");
    return;
  }

  // Extract the command and value from the message
  String command = message.substring(0, commaIndex);
  int value = message.substring(commaIndex + 1).toInt();

  // Check if the parsed value is valid
  if (value == 0 && message.substring(commaIndex + 1) != "0") {
    Serial.println("Error: Invalid value parsed");
    return;
  }

  // Forward command and value to the motor controller ESP32 via HTTP
  sendMotorCommand(command, value);
}

// WebSocket event handler to manage WebSocket events
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket disconnected from server");
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket connected to server at 192.168.4.2");
      webSocket.sendTXT("ESP32 Access Point connected to server");
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

  // Start HTTP server for testing purposes
  server.on("/", []() {
    server.send(200, "text/plain", "ESP32 WebSocket Access Point");
  });
  server.begin();

  // Connect to WebSocket server on 192.168.4.2
  webSocket.begin("192.168.4.2", 8081, "/"); // Server IP address and port
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  server.handleClient();
  webSocket.loop();
}
