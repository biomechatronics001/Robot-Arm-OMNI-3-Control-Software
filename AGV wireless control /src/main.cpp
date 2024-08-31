#include "test.h"
#include <DNSServer.h>
#include <ESPUI.h>
#include "Freenove_WS2812_Lib_for_ESP32.h"

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;

#if defined(ESP32)
#include <WiFi.h>
#else
// esp8266

#ifndef MMU_IRAM_HEAP
#warning Try MMU option '2nd heap shared' in 'tools' IDE menu (cf. https://arduino-esp8266.readthedocs.io/en/latest/mmu.html#option-summary)
#warning use decorators: { HeapSelectIram doAllocationsInIRAM; ESPUI.addControl(...) ... } (cf. https://arduino-esp8266.readthedocs.io/en/latest/mmu.html#how-to-select-heap)
#warning then check http://<ip>/heap
#endif // MMU_IRAM_HEAP
#ifndef DEBUG_ESP_OOM
#error on ESP8266 and ESPUI, you must define OOM debug option when developping
#endif
#endif

const char *ssid = "GuangYu2019";
const char *password = "Gyems123";
const char *hostname = "espressif";

uint16_t status1=0;
uint16_t status2=0;
uint16_t button1;
uint16_t button2;
uint16_t button3;
uint16_t button4;
//uint16_t button5;
uint16_t millisLabelId;
uint16_t switchOne;
int32_t Speed;
int32_t rotatespeed;

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(1, 4, 0, TYPE_GRB);

void numberCall_1(Control *sender_1, int32_t type_1)
{
    Serial.println(sender_1->value);
    Speed = sender_1->value.toInt();
}
void numberCall_2(Control *sender_2, int type_2)
{
    Serial.println(sender_2->value);
    rotatespeed = sender_2->value.toInt();
}

void buttonCallback_1(Control *sender, int type)
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_1 DOWN");
        break;

    case B_UP:
        Serial.println("Button_1 UP");
        status1=1;
        break;
    }
}

void buttonCallback_2(Control *sender, int type)
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_2 DOWN");
        break;

    case B_UP:
        Serial.println("Button_2 UP");
        status1=2;
        break;
    }
}
void buttonCallback_3(Control *sender, int type)
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_2 DOWN");
        break;

    case B_UP:
        Serial.println("Button_2 UP");
        status1=3;
        break;
    }
}
void buttonCallback_4(Control *sender, int type)
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_2 DOWN");
        break;

    case B_UP:
        Serial.println("Button_2 UP");
        status1=4;
        break;
    }
}
/*void buttonCallback_5(Control *sender, int type)
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_2 DOWN");
        break;

    case B_UP:
        Serial.println("Button_2 UP");
        status1=5;
        break;
    }
}*/

CAN_device_t CAN_cfg;             // CAN Config (CAN配置)
unsigned long previousMillis = 0; // will store last time a CAN Message was send (将存储最后一次发送的CAN消息)
const int interval = 10;          // interval at which send CAN Messages (milliseconds) (发送CAN消息的时间间隔(毫秒))
const int rx_queue_size = 10;     // Receive Queue size (接收队列大小)

void setup()
{
    pinMode(PIN_5V_EN, OUTPUT);
    digitalWrite(PIN_5V_EN, HIGH);

    pinMode(CAN_SE_PIN, OUTPUT);
    digitalWrite(CAN_SE_PIN, LOW);

    pinMode(RS485_EN_PIN, OUTPUT);
    digitalWrite(RS485_EN_PIN, HIGH);

    pinMode(RS485_SE_PIN, OUTPUT);
    digitalWrite(RS485_SE_PIN, HIGH);

    pinMode(WS2812_PIN, OUTPUT);
    digitalWrite(WS2812_PIN, LOW);

    ESPUI.setVerbosity(Verbosity::VerboseJSON);
    Serial.begin(115200);
    CAN_cfg.speed = CAN_SPEED_1000KBPS;
    CAN_cfg.tx_pin_id = GPIO_NUM_27;
    CAN_cfg.rx_pin_id = GPIO_NUM_26;
    CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
    // Init CAN Module
    ESP32Can.CANInit();

#if defined(ESP32)
    WiFi.setHostname(hostname);
#else
    WiFi.hostname(hostname);
#endif

    // try to connect to existing network
    WiFi.begin(ssid, password);
    Serial.print("\n\nTry to connect to existing network");

    {
        uint8_t timeout = 10;

        // Wait for connection, 5s timeout
        do
        {
            delay(500);
            Serial.print(".");
            timeout--;
        } while (timeout && WiFi.status() != WL_CONNECTED);

        // not connected -> create hotspot
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.print("\n\nCreating hotspot");

            WiFi.mode(WIFI_AP);
            delay(100);
            WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
#if defined(ESP32)
            uint32_t chipid = 0;
            for (int i = 0; i < 17; i = i + 8)
            {
                chipid |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
            }
#else
            uint32_t chipid = ESP.getChipId();
#endif
            char ap_ssid[25];
            snprintf(ap_ssid, 26, "ESPUI-%08X", chipid);
            WiFi.softAP(ap_ssid);

            timeout = 5;

            do
            {
                delay(500);
                Serial.print(".");
                timeout--;
            } while (timeout);
        }
    }

    dnsServer.start(DNS_PORT, "*", apIP);

    Serial.println("\n\nWiFi parameters:");
    Serial.print("Mode: ");
    Serial.println(WiFi.getMode() == WIFI_AP ? "Station" : "Client");
    Serial.print("IP address: ");
    Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());
#ifdef ESP8266
    {
        HeapSelectIram doAllocationsInIRAM;
#endif

        ESPUI.addControl(ControlType::Number, "速度模式数值（正值前进-负值后退）", "0", ControlColor::Sunflower, Control::noParent, &numberCall_1);
        ESPUI.addControl(ControlType::Number, "旋转模式数值（正值左转-负值右转）", "0", ControlColor::Dark, Control::noParent, &numberCall_2);
        button1 = ESPUI.addControl(
            ControlType::Button, " ", "速度模式启动", ControlColor::Peterriver, Control::noParent, &buttonCallback_1);
        button2 = ESPUI.addControl(
            ControlType::Button, " ", "旋转模式启动", ControlColor::Peterriver, Control::noParent, &buttonCallback_2);
        button3 = ESPUI.addControl(
            ControlType::Button, " ", "电机停止", ControlColor::Peterriver, Control::noParent, &buttonCallback_3);
        button4 = ESPUI.addControl(
            ControlType::Button, " ", "电机失能", ControlColor::Peterriver, Control::noParent, &buttonCallback_4);
        /*button5 = ESPUI.addControl(
            ControlType::Button, " ", "电机失能", ControlColor::Peterriver, Control::noParent, &buttonCallback_5);*/

        ESPUI.begin("Myactuator Demo", "myactuator", "123456");

#ifdef ESP8266
    } // HeapSelectIram
#endif

    
    strip.begin();
    strip.setBrightness(10);
	strip.setLedColorData(0, 0, 0, 255);
	strip.show();
    
}

void loop()
{
    // put your setup code here, to loop run: (将您的设置代码放在此处，循环运行:)
    dnsServer.processNextRequest();
    if (status2 == 0)
    {
        switch (status1)
        {
        case 1:
            int32_t speed1;
            speed1 = -(Speed * 100);
            speedrun(speed1); // 速度运行
            status1 = 0;
            status2 = 1;
            break;
        case 2:
            int32_t speed2;
            speed2 = rotatespeed * 100;
            rotaterun(speed2);
            status1 = 0;
            status2 = 2;
            break;
            }
    }
    if(status1==3)
    {
        speedrun(0);
        status1=0;
        status2=0;
    }
    if(status1==4)
    {
        STOP();
        status1=0;
        status2=0;
    }
    if (status1==1&status2==1)
    {
        int32_t speed1;
        speed1=-(Speed*100);
        speedrun(speed1); // 速度运行
        status1=0;
    }    
    if(status1==2&status2==2)
    {
        int32_t speed2;
        speed2=rotatespeed*100;
        rotaterun(speed2);
        status1=0;
    }
    
}
