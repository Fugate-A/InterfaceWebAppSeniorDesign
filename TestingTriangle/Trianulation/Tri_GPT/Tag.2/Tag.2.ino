#include <SPI.h>
#include <DW1000Ranging.h>
#include <WiFi.h>

#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4
#define PIN_RST 27
#define PIN_IRQ 34

const char *ssid = "Hello There";
const char *password = "General Kenobi";
const char *host = "192.168.137.1";
WiFiClient client;

struct UWBData {
    uint16_t shortAddress;
    float range;
    float rxPower;
};

UWBData uwb_data;  // single instance to hold the current UWB range data
long runtime = 0;
String all_json = "";

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    if (client.connect(host, 80)) {
        Serial.println("Success");
        client.print(String("GET /") + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");
    }

    delay(1000);

    // UWB initialization
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, DW_CS, PIN_IRQ);
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachNewDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);

    // Start the module as a tag
    DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_LOWPOWER);
}

void loop() {
    DW1000Ranging.loop();
    if ((millis() - runtime) > 1000) {
        make_json(&all_json);
        send_udp(&all_json);
        runtime = millis();
    }
}

void newRange() {
    // Update UWB data with new range data
    uwb_data.shortAddress = DW1000Ranging.getDistantDevice()->getShortAddress();
    uwb_data.range = DW1000Ranging.getDistantDevice()->getRange();
    uwb_data.rxPower = DW1000Ranging.getDistantDevice()->getRXPower();

    Serial.print("from: ");
    Serial.print(uwb_data.shortAddress, HEX);
    Serial.print("\t Range: ");
    Serial.print(uwb_data.range);
    Serial.print(" m");
    Serial.print("\t RX power: ");
    Serial.print(uwb_data.rxPower);
    Serial.println(" dBm");
}

void newDevice(DW1000Device *device) {
    Serial.print("Ranging init; 1 device added! -> ");
    Serial.print(" short: ");
    Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device *device) {
    Serial.print("Delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
}

void make_json(String *json) {
    // Create a simple JSON message from UWB data
    *json = "{\"shortAddress\":\"" + String(uwb_data.shortAddress, HEX) +
            "\", \"range\":\"" + String(uwb_data.range) +
            "\", \"rxPower\":\"" + String(uwb_data.rxPower) + "\"}";
}

void send_udp(String *msg_json) {
    if (client.connected()) {
        client.print(*msg_json);
        Serial.println("UDP data sent: " + *msg_json);
    }
}
