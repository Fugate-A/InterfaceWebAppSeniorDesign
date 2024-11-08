#include <SPI.h>
#include <DW1000Ranging.h>
#include <WiFi.h>
#include "link.h"
#include <WebServer.h>
//have issues with http server 
//request with this, maybe becausefirewall 
//or UDHP, will test on Access-Point
#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4
#define PIN_RST 27
#define PIN_IRQ 34

// const char *ssid = "SpectrumSetup-D1";
// const char *password = "ablestudy738";
// const char *host = "192.168.1.10";

const char *ssid = "ChairGuru";
const char *password = "123456789";
const char *host = "192.168.4.1";
WiFiClient client;
WebServer server(80); //http server on port 80

struct MyLink *uwb_data;
int index_num = 0;
long runtime = 0;
String all_json = "";

// Function declarations
void newRange();
void newDevice(DW1000Device *device);
void inactiveDevice(DW1000Device *device);
void send_uwb_data();
String create_json_payload();

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());

    // if (client.connect(host, 80))
    // {
    //     Serial.println("Success");
    //     client.print(String("GET /") + " HTTP/1.1\r\n" +
    //                  "Host: " + host + "\r\n" +
    //                  "Connection: close\r\n" +
    //                  "\r\n");
    // }

    delay(4000);

    //init the configuration
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, DW_CS, PIN_IRQ);
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachNewDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);

    //we start the module as a tag
    DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_LOWPOWER);

    //set up http route
    server.on("/getUWBData", HTTP_GET, send_uwb_data); //define endpoint
    server.on("/hello", HTTP_GET, []() {
      server.send(200, "text/plain", "Hello World!");
});
    server.begin();
    uwb_data = init_link();
}

void loop()
{
    DW1000Ranging.loop();
    server.handleClient(); //handle incoming client request
    if ((millis() - runtime) > 3000)
    {
        make_link_json(uwb_data, &all_json);
        // send_udp(&all_json);
        runtime = millis();
    }
}

void newRange()
{
    char c[30];

    // Serial.print("from: ");
    // Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
    // Serial.print("\t Range: ");
    // Serial.print(DW1000Ranging.getDistantDevice()->getRange());
    // Serial.print(" m");
    // Serial.print("\t RX power: ");
    // Serial.print(DW1000Ranging.getDistantDevice()->getRXPower());
    // Serial.println(" dBm");
    fresh_link(uwb_data, DW1000Ranging.getDistantDevice()->getShortAddress(),
     DW1000Ranging.getDistantDevice()->getRange(),
      DW1000Ranging.getDistantDevice()->getRXPower());
}

void newDevice(DW1000Device *device)
{
    Serial.print("ranging init; 1 device added ! -> ");
    Serial.println(" short: ");
    Serial.print(device->getShortAddress(), HEX);
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());
    add_link(uwb_data, device->getShortAddress());
}

void inactiveDevice(DW1000Device *device)
{
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
    delete_link(uwb_data, device->getShortAddress());
}

void send_uwb_data() {
    String jsonPayload = create_json_payload();  // Get JSON data
    server.send(200, "application/json", jsonPayload);  // Send response as JSON
}

//Create JSON Payload
String create_json_payload() {
  String jsonPayload = "{";

  //Check if there's valid device in range
  DW1000Device *device = DW1000Ranging.getDistantDevice();
  if (device == NULL){
    Serial.println("No device in range");
    return "{\"error\": \"No device in range\"}";
  }

    // Get the latest device data
    uint64_t shortAddress = DW1000Ranging.getDistantDevice()->getShortAddress();
    float range = DW1000Ranging.getDistantDevice()->getRange();
    float rxPower = DW1000Ranging.getDistantDevice()->getRXPower();

    // Build the JSON object
    jsonPayload += "\"shortAddress\": \"" + String(shortAddress, HEX) + "\",";
    jsonPayload += "\"range\": " + String(range, 3) + ",";
    jsonPayload += "\"rxPower\": " + String(rxPower, 1);
    
    jsonPayload += "}";

    return jsonPayload;
}

// void send_udp(String *msg_json)
// {
//     if (client.connected())
//     {
//         client.print(*msg_json);
//         Serial.println("UDP send");
//     }
// }