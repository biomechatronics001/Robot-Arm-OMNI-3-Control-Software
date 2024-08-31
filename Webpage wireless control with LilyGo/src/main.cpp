#include "rclib.h"
#include <DNSServer.h>
#include <ESPUI.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <Arduino.h>

const char *ssid = "goodlife";
const char *password = "goodlife";
const char *hostname = "goodlife";
IPAddress local_IP(192, 168, 1, 200); // Static IP address of ESP32
IPAddress gateway(192, 168, 1, 0);    // Gateway
IPAddress subnet(255, 255, 255, 0);   // Subnet mask

WebSocketsServer webSocket = WebSocketsServer(81); // WebSocket port
uint16_t status;
uint16_t millisLabelId;
uint16_t switchOne;
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
            webSocket.sendTXT(num, "Hello from ESP32");
            break;
        }
        case WStype_TEXT:
            Serial.printf("[%u] Received text: %s\n", num, payload);

            StaticJsonDocument<2048> doc;
            auto error = deserializeJson(doc, payload, length);
            if (!error) {
                // Enable and disable
                if (doc.containsKey("shi3neng")) {
                    rc_set_status(31, 0x01);
                    webSocket.sendTXT(num, "Enabled");
                }
                if (doc.containsKey("shi1neng")) {
                    rc_set_status(31, 0x00);
                    webSocket.sendTXT(num, "Disabled");
                }
                // Motor control
                if (doc.containsKey("motors")) {
                    JsonArray motors = doc["motors"];
                    for (JsonObject motor : motors) {
                        int id = motor["id"];
                        int position = motor["position"];
                        int speed = motor["speed"];
                        delay(20);
                        rc_spt(id, position, speed);
                    }
                    webSocket.sendTXT(num, "Motor command processed");
                }
                // Set limits
                if (doc.containsKey("setLimit")) {
                    JsonObject setLimit = doc["setLimit"];
                    int motorId = setLimit["motorId"];
                    uint8_t limitType = setLimit["limitType"];
                    float value = setLimit["value"];
                    rc_set_lim(motorId, limitType, value);
                    Serial.printf("Limit set: Motor %d, Type %d, Value %.2f\n", motorId, limitType, value);
                    webSocket.sendTXT(num, "Limit command processed");
                }
                // Read limits
                if (doc.containsKey("readLimit")) {
                    JsonObject readLimit = doc["readLimit"];
                    int motorId = readLimit["motorId"];
                    uint8_t limitType = readLimit["limitType"];
                    int status = rc_read_lim(motorId,limitType);
                    char buffer[64];
                    sprintf(buffer, "Motor %d limit is %d", motorId, status);
                    webSocket.sendTXT(num, buffer);
                }
                // Emergency stop
                if (doc.containsKey("estop")) {
                    int motorId = doc["estop"]["motorId"];
                    rc_estop(motorId);
                    webSocket.sendTXT(num, "Emergency stop activated");
                }
                // Set motor status
                if (doc.containsKey("setStatus")) {
                    JsonObject setStatus = doc["setStatus"];
                    int motorId = setStatus["motorId"];
                    uint8_t status = setStatus["status"];
                    rc_set_status(motorId, status);
                    webSocket.sendTXT(num, "Motor status set");
                }
                // Read motor status
                if (doc.containsKey("readStatus")) {
                    int motorId = doc["readStatus"]["motorId"];
                    int status = rc_read_status(motorId);
                    char buffer[64];
                    sprintf(buffer, "Motor %d status is %d", motorId, status);
                    webSocket.sendTXT(num, buffer);
                }
                // Set motor mode
                if (doc.containsKey("setMode")) {
                    JsonObject setMode = doc["setMode"];
                    int motorId = setMode["motorId"];
                    uint8_t mode = setMode["mode"];
                    rc_set_mode(motorId, mode);
                    webSocket.sendTXT(num, "Motor mode set");
                }
                // Read motor mode
                if (doc.containsKey("readMode")) {
                    int motorId = doc["readMode"]["motorId"];
                    int mode = rc_read_mode(motorId);
                    char buffer[64];
                    sprintf(buffer, "Motor %d mode is %d", motorId, mode);
                    webSocket.sendTXT(num, buffer);
                }
                // Set current position to zero point
                if (doc.containsKey("setZeroPoint")) {
                    int motorId = doc["setZeroPoint"]["motorId"];
                    rc_set_zp(motorId,1);
                    webSocket.sendTXT(num, "Zero point set");
                }
                // Set PID parameters
                if (doc.containsKey("setPID")) {
                    JsonObject setPID = doc["setPID"];
                    int motorId = setPID["motorId"];
                    uint8_t parameter = setPID["parameter"];
                    float value = setPID["value"];
                    rc_set_PID(motorId, parameter, value);
                    webSocket.sendTXT(num, "PID parameter set");
                }
                // Read PID parameters
                if (doc.containsKey("readPID")) {
                    JsonObject readPID = doc["readPID"];
                    int motorId = readPID["motorId"];
                    uint8_t parameter = readPID["parameter"];
                    float value = rc_read_PID(motorId, parameter);
                    char buffer[64];
                    sprintf(buffer, "PID of Motor %d, Parameter %d is %.2f", motorId, parameter, value);
                    webSocket.sendTXT(num, buffer);
                }
                // Single point run
                if (doc.containsKey("singleRun")) {
                    JsonObject singleRun = doc["singleRun"];
                    int motorId = singleRun["motorId"];
                    float position = singleRun["position"];
                    rc_spr(motorId, position);
                    webSocket.sendTXT(num, "Single run executed");
                }
                // Continuous trajectory position data
                if (doc.containsKey("setCTPosition")) {
                    JsonObject setCTPosition = doc["setCTPosition"];
                    int motorId = setCTPosition["motorId"];
                    uint16_t index = setCTPosition["index"];
                    float value = setCTPosition["value"];
                    rc_set_ctp(motorId, index, value);
                    webSocket.sendTXT(num, "Continuous trajectory position data set");
                }
                // Continuous trajectory speed data
                if (doc.containsKey("setCTSpeed")) {
                    JsonObject setCTSpeed = doc["setCTSpeed"];
                    int motorId = setCTSpeed["motorId"];
                    uint16_t index = setCTSpeed["index"];
                    float value = setCTSpeed["value"];
                    rc_set_ctv(motorId, index, value);
                    webSocket.sendTXT(num, "Continuous trajectory speed data set");
                }
                // Continuous trajectory torque data
                if (doc.containsKey("setCTTorque")) {
                    JsonObject setCTTorque = doc["setCTTorque"];
                    int motorId = setCTTorque["motorId"];
                    uint16_t index = setCTTorque["index"];
                    float value = setCTTorque["value"];
                    rc_set_ctmf(motorId, index, value);
                    webSocket.sendTXT(num, "Continuous trajectory torque data set");
                }
                // Run specified trajectory data
                if (doc.containsKey("runTrajectory")) {
                    int motorId = doc["runTrajectory"]["motorId"];
                    uint16_t index = doc["runTrajectory"]["index"];
                    rc_tdr(motorId, index);
                    webSocket.sendTXT(num, "Specified trajectory run executed");
                }
                // Record data to a specified index position
                if (doc.containsKey("recordData")) {
                    int motorId = doc["recordData"]["motorId"];
                    uint16_t index = doc["recordData"]["index"];
                    rc_record(motorId, index);
                    webSocket.sendTXT(num, "Data recording completed");
                }
                // Read running data
                if (doc.containsKey("readRunData")) {
                    int motorId = doc["readRunData"]["motorId"];
                    uint8_t parameter = doc["readRunData"]["parameter"];
                    float value = rc_read_rd(motorId, parameter);
                    char buffer[64];
                    sprintf(buffer, "Running data Motor %d, Parameter %d is %.2f", motorId, parameter, value);
                    webSocket.sendTXT(num, buffer);
                }
                // Set CAN ID
                if (doc.containsKey("setCANID")) {
                    JsonObject setCANID = doc["setCANID"];
                    int motorId = setCANID["motorId"];
                    uint8_t newID = setCANID["newID"];
                    rc_set_CAN_ID(motorId, newID);
                    webSocket.sendTXT(num, "CAN ID set");
                }
                // Reset settings
                if (doc.containsKey("resetSettings")) {
                    int motorId = doc["resetSettings"]["motorId"];
                    rc_reset(motorId);
                    webSocket.sendTXT(num, "Settings reset");
                }
            } else {
                Serial.print("JSON deserialization failed: ");
                Serial.println(error.c_str());
            }
            break;
    }
}


unsigned long previousMillis = 0; // Will store the last time a CAN Message was sent
const int interval = 10;          // Interval at which to send CAN Messages (milliseconds)
const int rx_queue_size = 10;     // Receive Queue size

void setup()
{

    Serial.begin(115200);
    rc_init();
      // Configure static IP address
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
    // Try to connect to existing network
    WiFi.begin(ssid, password);
    Serial.print("\n\nTry to connect to existing network");

    uint8_t timeout = 10;

    // Wait for connection, 5s timeout
    do
    {
        delay(500);
        Serial.print(".");
        timeout--;
    } while (timeout && WiFi.status() != WL_CONNECTED);

        if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("\n\nnot connected");
    }

            if (WiFi.status() == WL_CONNECTED)
    {   
    Serial.print("Connected to WiFi. IP address: ");
    Serial.println(WiFi.localIP());
    }
    Serial.println("");
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
        if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("\n\nnot connected");
    }

    // Put your setup code here, to run once
}

void loop()
{
    // Put your setup code here, to loop run
    // dnsServer.processNextRequest();
    webSocket.loop();
    String message;  // Define once, used for the entire function
}
