#include <WiFi.h>
#include <WebServer.h>

// Access point credentials
const char* apSsid = "ESP32-Access-Point";    // Access Point SSID
const char* apPassword = "123456789";         // Access Point password

// Custom IP configuration
IPAddress local_IP(192, 168, 4, 1);  // Correct format for IPAddress (comma-separated values)
IPAddress gateway(192, 168, 4, 1);   // Set the gateway to match the IP
IPAddress subnet(255, 255, 255, 0);  // Subnet mask

// Create a WebServer object on port 80
WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Set up the ESP32 as an access point with a custom IP address
  Serial.print("Setting up access point...");

  // Configure the access point with custom IP and subnet
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(apSsid, apPassword);

  // Print the IP address of the access point
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP address: ");
  Serial.println(IP);

  // Define route for the root URL
  server.on("/", handleRoot);  // When you access the root ("/"), call the handleRoot function

  // Define route to handle button click
  server.on("/button-click", handleButtonClick);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  // Handle incoming HTTP requests
}

// Serve the HTML page with a button and WebSocket connection
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP32 Button and WebSocket Test</h1>";
  
  // Button to send WebSocket request
  html += "<button onclick=\"sendWebSocketMessage()\">Click Me to Send WebSocket Message!</button>";
  
  // WebSocket JavaScript logic
  html += "<script>";
  html += "let socket;";
  html += "window.onload = function() {";
  html += "  socket = new WebSocket('ws://192.168.4.2:8081');";  // Replace with your WebSocket server's URL
  html += "  socket.onopen = function() { console.log('WebSocket connection opened.'); };";
  html += "  socket.onmessage = function(event) { console.log('Received from server: ' + event.data); };";
  html += "  socket.onerror = function(error) { console.error('WebSocket Error: ' + error); };";
  html += "};";
  
  // Function to send message via WebSocket when the button is clicked
  html += "function sendWebSocketMessage() {";
  html += "  console.log('Sending WebSocket message...');";
  html += "  socket.send('Hello from ESP32 web page!');";  // Message sent to WebSocket server
  html += "}";
  html += "</script>";

  html += "</body></html>";

  server.send(200, "text/html", html);  // Send the HTML page
}

// Handle the button click (HTTP request)
void handleButtonClick() {
  Serial.println("HTTP Button was clicked!");  // Log the event in the ESP32 serial monitor
  server.send(200, "text/plain", "Button click logged via HTTP!");  // Send a response back to the client
}
