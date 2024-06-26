#include "rclib.h"
#include "wenjian.h"
#include <DNSServer.h>
#include <ESPUI.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <Arduino.h>
#include <SPIFFS.h>
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
    Position = sender_1->value.toInt();
}

void numberCall_2(Control *sender_2, int type_2)
{
    Serial.println(sender_2->value);
    Speed = sender_2->value.toInt();
}

void numberCall_3(Control *sender_3, int type_3)
{
    Serial.println(sender_3->value);
    yanshi = sender_3->value.toInt();
}

void numberCall_4(Control *sender_4, int type_4)
{
    Serial.println(sender_4->value);
    ID = sender_4->value.toInt();
}

void buttonCallback_1(Control *sender, int type) // enable 使能
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

void buttonCallback_2(Control *sender, int type) // disable 失能
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

void buttonCallback_3(Control *sender, int type) // read current Position 读取当前位置
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

void buttonCallback_4(Control *sender, int type) // save the read Position 保存读取的位置
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

void buttonCallback_5(Control *sender, int type) // delete recorded Position 删除记录的位置
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

void buttonCallback_6(Control *sender, int type) // do 执行动作
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

void buttonCallback_7(Control *sender, int type) // stop 急停
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

void buttonCallback_8(Control *sender, int type) // motor 1     轴1
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_8 DOWN");
        break;

    case B_UP:
        Serial.println("Button_8 UP");
        panduan = 11;
        break;
    }
}

void buttonCallback_9(Control *sender, int type) // motor 2     轴2
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_9 DOWN");
        break;

    case B_UP:
        Serial.println("Button_9 UP");
        panduan = 12;
        break;
    }
}

void buttonCallback_10(Control *sender, int type) // motor 3    轴3
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_10 DOWN");
        break;

    case B_UP:
        Serial.println("Button_10 UP");
        panduan = 13;
        break;
    }
}

void buttonCallback_11(Control *sender, int type) // motor 4    轴4
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_11 DOWN");
        break;

    case B_UP:
        Serial.println("Button_11 UP");
        panduan = 14;
        break;
    }
}

void buttonCallback_12(Control *sender, int type) // motor 5    轴5
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_12 DOWN");
        break;

    case B_UP:
        Serial.println("Button_12 UP");
        panduan = 15;
        break;
    }
}

void buttonCallback_13(Control *sender, int type) // motor 6    轴6
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_13 DOWN");
        break;

    case B_UP:
        Serial.println("Button_13 UP");
        panduan = 16;
        break;
    }
}

void buttonCallback_14(Control *sender, int type) // claw    夹爪
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_14 DOWN");
        break;

    case B_UP:
        Serial.println("Button_14 UP");
        panduan = 17;
        break;
    }
}

void buttonCallback_15(Control *sender, int type) // open claw    张开
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_15 DOWN");
        break;
    case B_UP:
        Serial.println("Button_15 UP");
        panduan1 = 1;
        break;
    }
}

void buttonCallback_16(Control *sender, int type) // close claw    闭合
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_16 DOWN");
        break;

    case B_UP:
        Serial.println("Button_16 UP");
        panduan1 = 2;
        break;
    }
}

void buttonCallback_17(Control *sender, int type) // set current position as zero    设置当前位置为零点
{
    switch (type)
    {
    case B_DOWN:
        Serial.println("Button_17 DOWN");
        break;

    case B_UP:
        Serial.println("Button_17 UP");
        panduan = 7;
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
    ESPUI.addControl(ControlType::Number, "Position:", "0", ControlColor::Sunflower, Control::noParent, &numberCall_1);
    ESPUI.addControl(ControlType::Number, "Speed:", "0", ControlColor::Sunflower, Control::noParent, &numberCall_2);
    ESPUI.addControl(ControlType::Number, "Delay:", "0", ControlColor::Sunflower, Control::noParent, &numberCall_3);
    ESPUI.addControl(ControlType::Number, "ID:", "0", ControlColor::Sunflower, Control::noParent, &numberCall_4);
    button1 = ESPUI.addControl(
        ControlType::Button, " ", "enable", ControlColor::Peterriver, Control::noParent, &buttonCallback_1);
    button2 = ESPUI.addControl(
        ControlType::Button, " ", "disable", ControlColor::Peterriver, button1, &buttonCallback_2);
    button3 = ESPUI.addControl(
        ControlType::Button, " ", "read Current Position", ControlColor::Peterriver, Control::noParent, &buttonCallback_3);
    button4 = ESPUI.addControl(
        ControlType::Button, " ", "save the read Position", ControlColor::Peterriver, button3, &buttonCallback_4);
    button5 = ESPUI.addControl(
        ControlType::Button, " ", "Delete recorded Position", ControlColor::Peterriver, button3, &buttonCallback_5);
    button6 = ESPUI.addControl(
        ControlType::Button, " ", "do", ControlColor::Peterriver, button3, &buttonCallback_6);
    button7 = ESPUI.addControl(
        ControlType::Button, " ", "stop", ControlColor::Peterriver, button3, &buttonCallback_7);
    button8 = ESPUI.addControl(
        ControlType::Button, " ", "motor 1", ControlColor::Peterriver, Control::noParent, &buttonCallback_8);
    button9 = ESPUI.addControl(
        ControlType::Button, " ", "motor 2", ControlColor::Peterriver, button8, &buttonCallback_9);
    button10 = ESPUI.addControl(
        ControlType::Button, " ", "motor 3", ControlColor::Peterriver, button8, &buttonCallback_10);
    button11 = ESPUI.addControl(
        ControlType::Button, " ", "motor 4", ControlColor::Peterriver, button8, &buttonCallback_11);
    button12 = ESPUI.addControl(
        ControlType::Button, " ", "motor 5", ControlColor::Peterriver, button8, &buttonCallback_12);
    button13 = ESPUI.addControl(
        ControlType::Button, " ", "motor 6", ControlColor::Peterriver, button8, &buttonCallback_13);
    button14 = ESPUI.addControl(
        ControlType::Button, " ", "claw", ControlColor::Peterriver, button8, &buttonCallback_14);
    button15 = ESPUI.addControl(
        ControlType::Button, " ", "open claw", ControlColor::Peterriver, Control::noParent, &buttonCallback_15);
    button16 = ESPUI.addControl(
        ControlType::Button, " ", "close claw", ControlColor::Peterriver, button15, &buttonCallback_16);
    button17 = ESPUI.addControl(
        ControlType::Button, " ", "set current position as zero ", ControlColor::Peterriver, button2, &buttonCallback_17);
    label1 = ESPUI.label("motor 1", ControlColor::Emerald, " ");
    label2 = ESPUI.label("motor 2", ControlColor::Emerald, " ");
    label3 = ESPUI.label("motor 3", ControlColor::Emerald, " ");
    label4 = ESPUI.label("motor 4", ControlColor::Emerald, " ");
    label5 = ESPUI.label("motor 5", ControlColor::Emerald, " ");
    label6 = ESPUI.label("motor 6", ControlColor::Emerald, " ");
    label7 = ESPUI.label("claw", ControlColor::Emerald, " ");
    ESPUI.begin("Myactuator Demo", "myactuator", "123456");
    panduan = -1;
    panduan1 = -1;
    ii = 0;
    j = 0;
    yanshi = 3000; // The default delay is three seconds延时默认为3s
    // put your setup code here, to run once: (将您的设置代码放在此处，运行一次：)
}

void loop()
{
    // put your setup code here, to loop run: (将您的设置代码放在此处，循环运行:)
    // dnsServer.processNextRequest();
    switch (panduan)
    {
    case 0:
        rc_set_status(ID, 0x01); // enable 使能
        delay(50);
        panduan = -1;
        break;
    case 1:
        rc_set_status(ID, 0x00); // disable 失能
        delay(50);
        panduan = -1;
        break;
    case 2: // read Position 读取位置
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
        panduan = -1;
        break;
    case 3: // save value 保存读取值
        b1[ii] = a1;
        b2[ii] = a2;
        b3[ii] = a3;
        b4[ii] = a4;
        b5[ii] = a5;
        b6[ii] = a6;
        // b7[ii] = a7;
        c[ii] = yanshi;
        ii = ii + 1;
        panduan = -1;
        break;
    case 4: // delete 清空读取值
        ii = 0;
        memset(b1, 0, sizeof(b1));
        memset(b2, 0, sizeof(b2));
        memset(b3, 0, sizeof(b3));
        memset(b4, 0, sizeof(b4));
        memset(b5, 0, sizeof(b5));
        memset(b6, 0, sizeof(b6));
        // memset(b7, 0, sizeof(b7));
        panduan = -1;
        break;
    case 5: // do 执行动作
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
            // rc_spt(7, b7[j], 15);
            // delay(20);
            j = j + 1;
        }
        else
        {
            panduan = -1;
            j = 0;
        }
        break;
    case 6: // stop 急停
        rc_estop(31);
        delay(20);
        panduan = -1;
        break;
    case 7: // 设置当前位置为零点
        rc_set_zp(ID, 0x01);
        delay(20);
        panduan = -1;
        break;
    case 11: // motor1 1轴
        rc_spt(1, Position, Speed);
        panduan = -1;
        break;
    case 12:
        rc_spt(2, Position, Speed);
        panduan = -1;
        break;
    case 13:
        rc_spt(3, Position, Speed);
        panduan = -1;
        break;
    case 14:
        rc_spt(4, Position, Speed);
        panduan = -1;
        break;
    case 15:
        rc_spt(5, Position, Speed);
        panduan = -1;
        break;
    case 16:
        rc_spt(6, Position, Speed);
        panduan = -1;
        break;
    case 17: // claw 夹爪
        rc_spt(7, Position, Speed);
        panduan = -1;
        break;
    default:
        break;
    }
    switch (panduan1)
    {
    case 1: // open
        rc_spt(7, 1800, 500);
        delay(20);
        panduan1 = -1;
        break;
    case 2: // close
        rc_spt(7, 0, 500);
        delay(20);
        panduan1 = -1;
        break;
    default:
        break;
    }
    delay(c[j]);
}