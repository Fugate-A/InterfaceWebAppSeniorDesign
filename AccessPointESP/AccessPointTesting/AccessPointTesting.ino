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

// Chair IP Mapping
const char* chairIPMap[] = {
    "192.168.4.3", // Chair 1
    "192.168.4.4"  // Chair 2
};

// Create a WebServer object on port 80
WebServer server(80);

// Function to send command to the motor controller via HTTP
void sendMotorCommand(const String& targetIP, const String& command, int value) {
  HTTPClient http;
  String url = "http://" + targetIP + "/move"; // Motor controller endpoint
  http.begin(url);

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
  http.end(); // Close HTTP connection
}

/*// WebSocket message handler to handle messages from the server and forward them to the motor ESP
void handleWebSocketMessage(String message) {
  Serial.print("Received WebSocket message: ");
  Serial.println(message);

  // Extract chair identifier, command, and value from the message
  int firstSpaceIndex = message.indexOf(' ');
  int secondSpaceIndex = message.indexOf(' ', firstSpaceIndex + 1);
  if (firstSpaceIndex == -1 || secondSpaceIndex == -1) {
    Serial.println("Error: Malformed WebSocket message");
    return;
  }

  String chairId = message.substring(firstSpaceIndex + 1, secondSpaceIndex); // Extract chair identifier
  String commandValuePart = message.substring(secondSpaceIndex + 1);         // Extract command and value

  int commaIndex = commandValuePart.indexOf(',');
  if (commaIndex == -1) {
    Serial.println("Error: Malformed command-value pair");
    return;
  }

  String command = commandValuePart.substring(0, commaIndex); // Extract command
  int value = commandValuePart.substring(commaIndex + 1).toInt(); // Extract value

  // Determine target IP based on chair identifier
  int chairIndex = -1;
  if (chairId == "chair1") {
    chairIndex = 0;
  } else if (chairId == "chair2") {
    chairIndex = 1;
  } else {
    Serial.println("Error: Unknown chair identifier");
    return;
  }

  String targetIP = chairIPMap[chairIndex];

  // Forward command and value to the appropriate motor controller ESP32
  sendMotorCommand(targetIP, command, value);
}*/

void handleWebSocketMessage(String message) {
  Serial.print("Received WebSocket message: ");
  Serial.println(message);

  // Extract chair identifier, command, and value from the message
  int firstSpaceIndex = message.indexOf(' ');
  int secondSpaceIndex = message.indexOf(' ', firstSpaceIndex + 1);

  if (firstSpaceIndex == -1 || secondSpaceIndex == -1) {
    Serial.println("Error: Malformed WebSocket message");
    return;
  }

  String chairId = message.substring(0, firstSpaceIndex); // Extract chair identifier
  String command = message.substring(firstSpaceIndex + 1, secondSpaceIndex); // Extract command
  String valueString = message.substring(secondSpaceIndex + 1); // Extract value as string
  int value = valueString.toInt(); // Convert value to integer

  // Determine target IP based on chair identifier
  int chairIndex = -1;
  if (chairId == "chair1") {
    chairIndex = 0;
  } else if (chairId == "chair2") {
    chairIndex = 1;
  } else {
    Serial.println("Error: Unknown chair identifier");
    return;
  }

  String targetIP = chairIPMap[chairIndex];

  // Forward command and value to the appropriate motor controller ESP32
  sendMotorCommand(targetIP, command, value);
}

// WebSocket event handler to manage WebSocket events
void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
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
