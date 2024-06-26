#include "rclib.h"
#include <DNSServer.h>
#include <ESPUI.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <Arduino.h>

const char *ssid = "A北";
const char *password = "maita666";
const char *hostname = "espressif";
IPAddress local_IP(192, 168, 1, 200); // ESP32的静态IP地址
IPAddress gateway(192, 168, 1, 0);    // 网关
IPAddress subnet(255, 255, 255, 0);   // 子网掩码

WebSocketsServer webSocket = WebSocketsServer(81); // webscoket端口
uint16_t status;
uint16_t millisLabelId;
uint16_t switchOne;
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] 断开连接!\n", num);
            break;
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] 从 %d.%d.%d.%d 连接\n", num, ip[0], ip[1], ip[2], ip[3]);
            webSocket.sendTXT(num, "Hello from ESP32");
            break;
        }
        case WStype_TEXT:
            Serial.printf("[%u] 收到文本: %s\n", num, payload);

            StaticJsonDocument<2048> doc;
            auto error = deserializeJson(doc, payload, length);
            if (!error) {
                //使能失能
                if (doc.containsKey("shi3neng")) {
                    rc_set_status(31, 0x01);
                    webSocket.sendTXT(num, "已使能");
                }
                if (doc.containsKey("shi1neng")) {
                    rc_set_status(31, 0x00);
                    webSocket.sendTXT(num, "已失能");
                }
                // 马达控制
                if (doc.containsKey("motors")) {
                    JsonArray motors = doc["motors"];
                    for (JsonObject motor : motors) {
                        int id = motor["id"];
                        int position = motor["position"];
                        int speed = motor["speed"];
                        delay(20);
                        rc_spt(id, position, speed);
                    }
                    webSocket.sendTXT(num, "马达命令已处理");
                }
                // 设置限制
                if (doc.containsKey("setLimit")) {
                    JsonObject setLimit = doc["setLimit"];
                    int motorId = setLimit["motorId"];
                    uint8_t limitType = setLimit["limitType"];
                    float value = setLimit["value"];
                    rc_set_lim(motorId, limitType, value);
                    Serial.printf("已设置限制: Motor %d, Type %d, Value %.2f\n", motorId, limitType, value);
                    webSocket.sendTXT(num, "限制命令已处理");
                }
                //读取限制
                if (doc.containsKey("readLimit")) {
                    JsonObject readLimit = doc["readLimit"];
                    int motorId = readLimit["motorId"];
                    uint8_t limitType = readLimit["limitType"];
                    int status = rc_read_lim(motorId,limitType);
                    char buffer[64];
                    sprintf(buffer, "Motor %d limit is %d", motorId, status);
                    webSocket.sendTXT(num, buffer);
                }
                // 急停
                if (doc.containsKey("estop")) {
                    int motorId = doc["estop"]["motorId"];
                    rc_estop(motorId);
                    webSocket.sendTXT(num, "急停已激活");
                }
                // 设置电机状态
                if (doc.containsKey("setStatus")) {
                    JsonObject setStatus = doc["setStatus"];
                    int motorId = setStatus["motorId"];
                    uint8_t status = setStatus["status"];
                    rc_set_status(motorId, status);
                    webSocket.sendTXT(num, "电机状态已设置");
                }
                // 读取电机状态
                if (doc.containsKey("readStatus")) {
                    int motorId = doc["readStatus"]["motorId"];
                    int status = rc_read_status(motorId);
                    char buffer[64];
                    sprintf(buffer, "Motor %d status is %d", motorId, status);
                    webSocket.sendTXT(num, buffer);
                }
                // 设置电机模式
                if (doc.containsKey("setMode")) {
                    JsonObject setMode = doc["setMode"];
                    int motorId = setMode["motorId"];
                    uint8_t mode = setMode["mode"];
                    rc_set_mode(motorId, mode);
                    webSocket.sendTXT(num, "电机模式已设置");
                }
                // 读取电机模式
                if (doc.containsKey("readMode")) {
                    int motorId = doc["readMode"]["motorId"];
                    int mode = rc_read_mode(motorId);
                    char buffer[64];
                    sprintf(buffer, "Motor %d mode is %d", motorId, mode);
                    webSocket.sendTXT(num, buffer);
                }
                // 设置当前位置为零点
                if (doc.containsKey("setZeroPoint")) {
                    int motorId = doc["setZeroPoint"]["motorId"];
                    rc_set_zp(motorId,1);
                    webSocket.sendTXT(num, "零点已设置");
                }
                // 设置PID参数
                if (doc.containsKey("setPID")) {
                    JsonObject setPID = doc["setPID"];
                    int motorId = setPID["motorId"];
                    uint8_t parameter = setPID["parameter"];
                    float value = setPID["value"];
                    rc_set_PID(motorId, parameter, value);
                    webSocket.sendTXT(num, "PID 参数已设置");
                }
                // 读取PID参数
                if (doc.containsKey("readPID")) {
                    JsonObject readPID = doc["readPID"];
                    int motorId = readPID["motorId"];
                    uint8_t parameter = readPID["parameter"];
                    float value = rc_read_PID(motorId, parameter);
                    char buffer[64];
                    sprintf(buffer, "PID of Motor %d, Parameter %d is %.2f", motorId, parameter, value);
                    webSocket.sendTXT(num, buffer);
                }
                // 单点运行
                if (doc.containsKey("singleRun")) {
                    JsonObject singleRun = doc["singleRun"];
                    int motorId = singleRun["motorId"];
                    float position = singleRun["position"];
                    rc_spr(motorId, position);
                    webSocket.sendTXT(num, "单点运行已执行");
                }
                // 连续轨迹位置数据
                if (doc.containsKey("setCTPosition")) {
                    JsonObject setCTPosition = doc["setCTPosition"];
                    int motorId = setCTPosition["motorId"];
                    uint16_t index = setCTPosition["index"];
                    float value = setCTPosition["value"];
                    rc_set_ctp(motorId, index, value);
                    webSocket.sendTXT(num, "连续轨迹位置数据已设置");
                }
                // 连续轨迹速度数据
                if (doc.containsKey("setCTSpeed")) {
                    JsonObject setCTSpeed = doc["setCTSpeed"];
                    int motorId = setCTSpeed["motorId"];
                    uint16_t index = setCTSpeed["index"];
                    float value = setCTSpeed["value"];
                    rc_set_ctv(motorId, index, value);
                    webSocket.sendTXT(num, "连续轨迹速度数据已设置");
                }
                // 连续轨迹矩流数据
                if (doc.containsKey("setCTTorque")) {
                    JsonObject setCTTorque = doc["setCTTorque"];
                    int motorId = setCTTorque["motorId"];
                    uint16_t index = setCTTorque["index"];
                    float value = setCTTorque["value"];
                    rc_set_ctmf(motorId, index, value);
                    webSocket.sendTXT(num, "连续轨迹矩流数据已设置");
                }
                // 指定轨迹数据运行
                if (doc.containsKey("runTrajectory")) {
                    int motorId = doc["runTrajectory"]["motorId"];
                    uint16_t index = doc["runTrajectory"]["index"];
                    rc_tdr(motorId, index);
                    webSocket.sendTXT(num, "指定轨迹数据运行已执行");
                }
                // 记录数据到指定索引位置
                if (doc.containsKey("recordData")) {
                    int motorId = doc["recordData"]["motorId"];
                    uint16_t index = doc["recordData"]["index"];
                    rc_record(motorId, index);
                    webSocket.sendTXT(num, "数据记录已完成");
                }
                // 读取运行数据
                if (doc.containsKey("readRunData")) {
                    int motorId = doc["readRunData"]["motorId"];
                    uint8_t parameter = doc["readRunData"]["parameter"];
                    float value = rc_read_rd(motorId, parameter);
                    char buffer[64];
                    sprintf(buffer, "运行数据 Motor %d, Parameter %d is %.2f", motorId, parameter, value);
                    webSocket.sendTXT(num, buffer);
                }
                // 设置CAN ID
                if (doc.containsKey("setCANID")) {
                    JsonObject setCANID = doc["setCANID"];
                    int motorId = setCANID["motorId"];
                    uint8_t newID = setCANID["newID"];
                    rc_set_CAN_ID(motorId, newID);
                    webSocket.sendTXT(num, "CAN ID 已设置");
                }
                // 还原设置
                if (doc.containsKey("resetSettings")) {
                    int motorId = doc["resetSettings"]["motorId"];
                    rc_reset(motorId);
                    webSocket.sendTXT(num, "设置已还原");
                }
            } else {
                Serial.print("JSON 反序列化失败: ");
                Serial.println(error.c_str());
            }
            break;
    }
}


unsigned long previousMillis = 0; // will store last time a CAN Message was send (将存储最后一次发送的CAN消息)
const int interval = 10;          // interval at which send CAN Messages (milliseconds) (发送CAN消息的时间间隔(毫秒))
const int rx_queue_size = 10;     // Receive Queue size (接收队列大小)

void setup()
{

    Serial.begin(115200);
    rc_init();
      // 配置静态IP地址
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
    // try to connect to existing network
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

    // put your setup code here, to run once: (将您的设置代码放在此处，运行一次：)
}

void loop()
{
    // put your setup code here, to loop run:
    // dnsServer.processNextRequest();
    webSocket.loop();
    String message;  // 定义一次，用于整个函数
}
