#include "rclib.h"
#include <DNSServer.h>
#include <ESPUI.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <Arduino.h>
IPAddress apIP(192, 168, 4, 1);

const char *ssid = "GuangYu2019";
const char *password = "Gyems123";
const char *hostname = "espressif";

uint16_t status;
uint16_t button1;
uint16_t button2;
uint16_t button3;
uint16_t button4;
uint16_t button5;
uint16_t button6;
uint16_t button7;
uint16_t button8;
uint16_t button9;
uint16_t button10;
uint16_t button11;
uint16_t button12;
uint16_t button13;
uint16_t button14;
uint16_t button15;
uint16_t button16;
uint16_t button17;
uint16_t millisLabelId;
uint16_t switchOne;

uint16_t label1;
uint16_t label2;
uint16_t label3;
uint16_t label4;
uint16_t label5;
uint16_t label6;
uint16_t label7;
uint16_t label8;

void numberCall_1(Control *sender_1, int type_1)
{
    Serial.println(sender_1->value);
    yanshi = sender_1->value.toInt();
}

void buttonCallback_1(Control *sender, int type) // 电流限制为0
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_1 DOWN");
        break;

    case B_UP:
        Serial.println("Button_1 UP");
        panduan = 0;
        break;
    }
}

void buttonCallback_2(Control *sender, int type) // 电流限制为20
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_2 DOWN");
        break;

    case B_UP:
        Serial.println("Button_2 UP");
        panduan = 1;
        break;
    }
}

void buttonCallback_3(Control *sender, int type) // 读取当前位置
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_3 DOWN");
        break;

    case B_UP:
        Serial.println("Button_3 UP");
        panduan = 2;
        break;
    }
}

void buttonCallback_4(Control *sender, int type) // 保存读取的值
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_4 DOWN");
        break;

    case B_UP:
        Serial.println("Button_4 UP");
        panduan = 3;
        break;
    }
}
void buttonCallback_5(Control *sender, int type) // 清空记录的值
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_5 DOWN");
        break;

    case B_UP:
        Serial.println("Button_5 UP");
        panduan = 4;
        break;
    }
}

void buttonCallback_6(Control *sender, int type) // 执行动作
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_6 DOWN");
        break;

    case B_UP:
        Serial.println("Button_6 UP");
        panduan = 5;
        break;
    }
}
void buttonCallback_7(Control *sender, int type) // 急停
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_7 DOWN");
        break;

    case B_UP:
        Serial.println("Button_7 UP");
        panduan = 6;
        break;
    }
}
void buttonCallback_8(Control *sender, int type) // 张开
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_8 DOWN");
        break;

    case B_UP:
        Serial.println("Button_8 UP");
        panduan1 = 0;
        break;
    }
}
void buttonCallback_9(Control *sender, int type) // 闭合
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_9 DOWN");
        break;

    case B_UP:
        Serial.println("Button_9 UP");
        panduan1 = 1;
        break;
    }
}
void buttonCallback_10(Control *sender, int type) // 1,90
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_10 DOWN");
        break;

    case B_UP:
        Serial.println("Button_10 UP");
        panduan = 7;
        break;
    }
}
void buttonCallback_11(Control *sender, int type) // 1,45
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_11 DOWN");
        break;

    case B_UP:
        Serial.println("Button_11 UP");
        panduan = 8;
        break;
    }
}

void buttonCallback_13(Control *sender, int type) // 2,45
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_13 DOWN");
        break;

    case B_UP:
        Serial.println("Button_13 UP");
        panduan = 10;
        break;
    }
}
void buttonCallback_14(Control *sender, int type) // 2,30
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_14 DOWN");
        break;

    case B_UP:
        Serial.println("Button_14 UP");
        panduan = 11;
        break;
    }
}
void buttonCallback_15(Control *sender, int type) // 2,30
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_15 DOWN");
        break;

    case B_UP:
        Serial.println("Button_15 UP");
        panduan = 12;
        break;
    }
}
// CAN Config (CAN配置)
unsigned long previousMillis = 0; // will store last time a CAN Message was send (将存储最后一次发送的CAN消息)
const int interval = 10;          // interval at which send CAN Messages (milliseconds) (发送CAN消息的时间间隔(毫秒))
const int rx_queue_size = 10;     // Receive Queue size (接收队列大小)

void setup()
{

    Serial.begin(115200);
    rc_init();

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

    // not connected -> create hotspot
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("\n\nCreating hotspot");

        WiFi.mode(WIFI_AP);
        delay(100);

        uint32_t chipid = 0;
        for (int i = 0; i < 17; i = i + 8)
        {
            chipid |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
        }

        char ap_ssid[25];
        snprintf(ap_ssid, 26, "ESPUI-%08X", chipid);
        WiFi.softAP(ap_ssid);
        WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

        Serial.println("\n\nWiFi parameters:");
        Serial.print("Mode: ");
        Serial.println(WiFi.getMode() == WIFI_AP ? "Station" : "Client");
        Serial.print("IP address: ");
        Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());
    }
    ESPUI.setVerbosity(Verbosity::VerboseJSON);
    ESPUI.addControl(ControlType::Number, "延时:", "", ControlColor::Sunflower, Control::noParent, &numberCall_1);
    button1 = ESPUI.addControl(
        ControlType::Button, " ", "失能", ControlColor::Peterriver, Control::noParent, &buttonCallback_1);
    button2 = ESPUI.addControl(
        ControlType::Button, " ", "使能", ControlColor::Peterriver, button1, &buttonCallback_2);
    button3 = ESPUI.addControl(
        ControlType::Button, " ", "读取当前位置", ControlColor::Peterriver, Control::noParent, &buttonCallback_3);
    button4 = ESPUI.addControl(
        ControlType::Button, " ", "保存读取的位置", ControlColor::Peterriver, button3, &buttonCallback_4);
    button5 = ESPUI.addControl(
        ControlType::Button, " ", "清空记录的值", ControlColor::Peterriver, button3, &buttonCallback_5);
    button6 = ESPUI.addControl(
        ControlType::Button, " ", "执行动作", ControlColor::Peterriver, Control::noParent, &buttonCallback_6);
    button7 = ESPUI.addControl(
        ControlType::Button, " ", "使能", ControlColor::Peterriver, button6, &buttonCallback_7);
    button8 = ESPUI.addControl(
        ControlType::Button, " ", "张开", ControlColor::Peterriver, Control::noParent, &buttonCallback_8);
    button9 = ESPUI.addControl(
        ControlType::Button, " ", "闭合", ControlColor::Peterriver, button8, &buttonCallback_9);
    /*    button10 = ESPUI.addControl(
            ControlType::Button, " ", "+15", ControlColor::Peterriver, Control::noParent, &buttonCallback_10);
        button11 = ESPUI.addControl(
            ControlType::Button, " ", "-15", ControlColor::Peterriver, button10, &buttonCallback_11);

        button13 = ESPUI.addControl(
            ControlType::Button, " ", "+10", ControlColor::Peterriver, button10, &buttonCallback_13);
        button14 = ESPUI.addControl(
            ControlType::Button, " ", "-10", ControlColor::Peterriver, button10, &buttonCallback_14);*/
    button15 = ESPUI.addControl(
        ControlType::Button, " ", "do", ControlColor::Peterriver, Control::noParent, &buttonCallback_15);
    label1 = ESPUI.label("轴1", ControlColor::Emerald, " ");
    label2 = ESPUI.label("轴2", ControlColor::Emerald, " ");
    label3 = ESPUI.label("轴3", ControlColor::Emerald, " ");
    label4 = ESPUI.label("轴4", ControlColor::Emerald, " ");
    label5 = ESPUI.label("轴5", ControlColor::Emerald, " ");
    label6 = ESPUI.label("轴6", ControlColor::Emerald, " ");
    label7 = ESPUI.label("轴7", ControlColor::Emerald, " ");
    ESPUI.begin("Myactuator Demo", "myactuator", "123456");
    panduan = -1;
    panduan1 = -1;
    ii = 0;
    j = 0;
    q = 0;
    p = 0;
    yanshi = 3000;
    // put your setup code here, to run once: (将您的设置代码放在此处，运行一次：)
}

void loop()
{
    // put your setup code here, to loop run: (将您的设置代码放在此处，循环运行:)
    // dnsServer.processNextRequest();
    switch (panduan)
    {
    case 0:
        rc_set_status(31, 0x00); // 失能
        delay(50);
        panduan = -1;
        break;
    case 1:
        rc_set_status(31, 0x01); // 使能
        delay(50);
        panduan = -1;
        break;
    case 2: // 读取位置
        a1 = rc_read_rd(1, 0x00);
        ESPUI.updateLabel(label1, String(a1));
        delay(20);
        a2 = rc_read_rd(2, 0x00);
        ESPUI.updateLabel(label2, String(a2));
        delay(20);
        a3 = rc_read_rd(3, 0x00);
        ESPUI.updateLabel(label3, String(a3));
        delay(20);
        a4 = rc_read_rd(4, 0x00);
        ESPUI.updateLabel(label4, String(a4));
        delay(20);
        a5 = rc_read_rd(5, 0x00);
        ESPUI.updateLabel(label5, String(a5));
        delay(20);
        a6 = rc_read_rd(6, 0x00);
        ESPUI.updateLabel(label6, String(a6));
        delay(20);
        a7 = rc_read_rd(7, 0x00);
        ESPUI.updateLabel(label7, String(a7));
        delay(20);
        //  printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n", a1, a2, a3, a4, a5, a6, a7, a8);
        //   a8 = rc_read_rd(8, 0x00);
        panduan = -1;
        break;
    case 3: // 保存读取值
        b1[ii] = a1;
        b2[ii] = a2;
        b3[ii] = a3;
        b4[ii] = a4;
        b5[ii] = a5;
        b6[ii] = a6;
        b7[ii] = a7;
        //  b8[ii] = a8;
        c[ii] = yanshi;
        ii = ii + 1;
        panduan = -1;
        break;
    case 4: // 清空读取值
        ii = 0;
        memset(b1, 0, sizeof(b1));
        memset(b2, 0, sizeof(b2));
        memset(b3, 0, sizeof(b3));
        memset(b4, 0, sizeof(b4));
        memset(b5, 0, sizeof(b5));
        memset(b6, 0, sizeof(b6));
        memset(b7, 0, sizeof(b7));
        // memset(b8, 0, sizeof(b8));
        panduan = -1;
        break;
    case 5: // 执行动作
        if (j <= ii - 1)
        {
            rc_spt(1, b1[j], 15);
            delay(20);
            rc_spt(2, b2[j], 15);
            delay(20);
            rc_spt(3, b3[j], 15);
            delay(20);
            rc_spt(4, b4[j], 15);
            delay(20);
            rc_spt(5, b5[j], 15);
            delay(20);
            rc_spt(6, b6[j], 15);
            delay(20);
            rc_spt(7, b7[j], 15);
            delay(20);
            //  rc_spt(8, b8[j], 15);
            //  delay(50);
            j = j + 1;
        }
        else
        {
            panduan = -1;
            j = 0;
        }
        break;
    case 6: // 使能
        rc_set_status(31, 0x01);
        delay(20);
        panduan = -1;
        break;
    /*case 7:
        p = p + 15;
        rc_spt(1, p, 15);
        panduan = -1;
        break;
    case 8:
        p = p - 15;
        rc_spt(1, p, 15);
        panduan = -1;
        break;
    case 10:
        q = q + 10;
        rc_spt(2, q, 15);
        panduan = -1;
        break;
    case 11:
        q = q - 10;
        rc_spt(2, q, 15);
        panduan = -1;
        break;*/
    case 12: // do
        // 在此处写入要执行的指令
        panduan = -1;
        break;
    default:
        break;
    }

    switch (panduan1)
    {
    case 0:
        rc_spt(7, 1800, 500);
        delay(20);
        panduan1 = -1;
        break;
    case 1:
        rc_spt(7, 0, 500);
        delay(20);
        panduan1 = -1;
        break;
    default:
        break;
    }
    delay(c[j]);
}