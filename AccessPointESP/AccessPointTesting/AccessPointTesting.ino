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

// Serve the HTML page with a button
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP32 Button Test</h1>";
  html += "<button onclick=\"buttonClicked()\">Click Me!</button>";
  html += "<script>";
  html += "function buttonClicked() {";
  html += "  console.log('Button clicked! Sending request to ESP32...');";  // Log in the browser console
  html += "  fetch('/button-click')";  // Send a request to the ESP32 when the button is clicked
  html += "}";
  html += "</script>";
  html += "</body></html>";

  server.send(200, "text/html", html);  // Send the HTML page
}

// Handle the button click and log it in the serial monitor
void handleButtonClick() {
  Serial.println("Button was clicked!");  // Log the event in the ESP32 serial monitor
  server.send(200, "text/plain", "Button click logged!");  // Send a response back to the client
}
