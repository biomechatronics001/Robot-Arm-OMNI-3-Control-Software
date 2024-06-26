#include "rclib.h"

int txid;
int num1;
int num2;
int Speed;
int Position;
int panduan;
int panduan1;
float q, p;
int yanshi;
int ii, j;
int c[99];
float a1, a2, a3, a4, a5, a6, a7, a8;
float b1[99], b2[99], b3[99], b4[99], b5[99], b6[99], b7[99], b8[99];

bool can_driver_installed = false;
unsigned long wait_time = 1000;

bool rc_init()
{
#ifdef LILYGO
    pinMode(16, OUTPUT);
    digitalWrite(16, HIGH);
    pinMode(23, OUTPUT);
    digitalWrite(23, LOW);
#endif

    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX_PIN, (gpio_num_t)RX_PIN, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS(); // Look in the api-reference for other speed sets.
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    // Install TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK)
    {
        return false;
    }

    // Start TWAI driver
    if (twai_start() != ESP_OK)
    {
        return false;
    }

    // Reconfigure alerts to detect frame receive, Bus-Off error and RX queue full states
    uint32_t alerts_to_enable = TWAI_ALERT_RX_DATA | TWAI_ALERT_ERR_PASS | TWAI_ALERT_BUS_ERROR | TWAI_ALERT_RX_QUEUE_FULL;
    if (twai_reconfigure_alerts(alerts_to_enable, NULL) != ESP_OK)
    {
        return false;
    }

    // TWAI driver is now successfully installed and started
    can_driver_installed = true;
    return true;
}

// 发送指令使电机紧急停止运行并保持使能状态
void rc_estop(int id)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x01;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 0;
    twai_transmit(&txbuffer, 0);
}

/*发送指令设置电机状态-data[0]代表索引值，发送0x00是使电机失能,发送0x01是使电机使能,
0x02：将电机主控重启；0x03：将电机参数重置；0x04：将电机错误状态重置*/

void rc_set_status(int id, uint8_t suoyin)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x03;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 1;
    txbuffer.data[0] = suoyin;
    twai_transmit(&txbuffer, 0);
}

/*发送指令读取电机状态*/
int rc_read_status(int id)
{
    if (!can_driver_installed)
        return -1;

    int res = -1;

    twai_message_t txbuffer;
    twai_message_t rxbuffer;

    txbuffer.identifier = id << 6 | 0x05;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 0;
    twai_transmit(&txbuffer, 0);

    unsigned long startMillis = millis();
    while (millis() - startMillis < wait_time)
    {

        if (twai_receive(&rxbuffer, 1) == ESP_OK)
        {
            if (rxbuffer.identifier == txbuffer.identifier)
            {
                res = rxbuffer.data[0];
                break;
            }
        }
    }
    return res;
}

/*发送指令设置电机运行模式-Data[0]代表索引值，发送0x00是设置电机运行模式为力矩模式，
发送0x01是设置电机运行模式为速度模式，发送0x02是设置电机运行模式为位置模式*/
void rc_set_mode(int id, uint8_t suoyin)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x07;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 1;
    txbuffer.data[0] = suoyin;
    twai_transmit(&txbuffer, 0);
}

/*发送指令读取电机运行模式*/
int rc_read_mode(int id)
{
    if (!can_driver_installed)
        return -1;

    int res = -1;

    twai_message_t txbuffer;
    twai_message_t rxbuffer;

    txbuffer.identifier = id << 6 | 0x09;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 0;
    twai_transmit(&txbuffer, 0);

    unsigned long startMillis = millis();
    while (millis() - startMillis < wait_time)
    {

        if (twai_receive(&rxbuffer, 1) == ESP_OK)
        {
            if (rxbuffer.identifier == txbuffer.identifier)
            {
                res = rxbuffer.data[0];
                break;
            }
        }
    }
    return res;
}

/*发送指令设置电机当前位置为零点*/
void rc_set_zp(int id, uint8_t suoyin)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x0b;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 1;
    txbuffer.data[0] = suoyin;
    twai_transmit(&txbuffer, 0);
}

/*发送指令设置电机PID参数,Data[0]代表索引值，发送0x00代表设置位置环P的参数，
0x01：位置环I；0x02：位置环D；0x03：位置环斜率；0x04：位置环滤波周期；
0x05：速度环P；0x06：速度环I；0x07：速度环D；0x08：速度环斜率；0x09：速度环滤波周期；
0x0A：Q轴电流环P；0x0B：Q轴电流环I；0x0C：Q轴电流环D；0x0D：Q轴电流环斜率；0x0E：Q轴电流环滤波周期；
0x0F：D轴电流环P；0x10：D轴电流环I；0x11：D轴电流环D；0x12：D轴电流环斜率；0x13：D轴电流环滤波周期。*/
void rc_set_PID(int id, uint8_t suoyin, float shuju)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x0d;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 5;
    txbuffer.data[0] = suoyin;
    float *p2 = (float *)&txbuffer.data[1];
    *p2 = shuju;
    twai_transmit(&txbuffer, 0);
}

/*发送指令读取PID参数,Data[0]代表索引值，发送0x00是读取位置环P参数,
0x01：位置环I；0x02：位置环D；0x03：位置环斜率；0x04：位置环滤波周期；
0x05：速度环P；0x06：速度环I；0x07：速度环D；0x08：速度环斜率；0x09：速度环滤波周期；
0x0A：Q轴电流环P；0x0B：Q轴电流环I；0x0C：Q轴电流环D；0x0D：Q轴电流环斜率；0x0E：Q轴电流环滤波周期；
0x0F：D轴电流环P；0x10：D轴电流环I；0x11：D轴电流环D；0x12：D轴电流环斜率；0x13：D轴电流环滤波周期*/
float rc_read_PID(int id, uint8_t suoyin)
{
    if (!can_driver_installed)
        return -99999.0f;

    float res = -99999.0f;

    twai_message_t txbuffer;
    twai_message_t rxbuffer;

    txbuffer.identifier = id << 6 | 0x0F;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 1;
    txbuffer.data[0] = suoyin;
    twai_transmit(&txbuffer, 0);

    unsigned long startMillis = millis();
    while (millis() - startMillis < wait_time)
    {

        if (twai_receive(&rxbuffer, 1) == ESP_OK)
        {
            if (rxbuffer.identifier == txbuffer.identifier)
            {
                res = *(float *)&rxbuffer.data[0];
                break;
            }
        }
    }
    return res;
}

/*发送指令设置电机限制参数,Data[0]代表索引值，
0x01：电机温度限制；0x02：电压限制；0x03：电流限制；0x04：速度限制；
0x05：位置限制-最小值；0x06：位置限制-最大值；0x07：抱闸启动；0x08：抱闸维持；0x09：过压值；
Data[1]—Data[4]数据从低位到高位，输入转换后的十六进制数*/
void rc_set_lim(int id, uint8_t suoyin, float shuju)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x11;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 5;
    txbuffer.data[0] = suoyin;
    float *p2 = (float *)&txbuffer.data[1];
    *p2 = shuju;
    twai_transmit(&txbuffer, 0);
}

/*发送指令读取限制参数,Data[0]代表索引值，
0x01：电机温度限制；0x02：电压限制；0x03：电流限制；0x04：速度限制；
0x05：位置限制-最小值；0x06：位置限制-最大值；0x07：抱闸启动；0x08：抱闸维持；0x09：过压值；*/
float rc_read_lim(int id, uint8_t suoyin)
{
    if (!can_driver_installed)
        return -99999.0f;

    float res = -99999.0f;

    twai_message_t txbuffer;
    twai_message_t rxbuffer;

    txbuffer.identifier = id << 6 | 0x13;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 1;
    txbuffer.data[0] = suoyin;
    twai_transmit(&txbuffer, 0);

    unsigned long startMillis = millis();
    while (millis() - startMillis < wait_time)
    {

        if (twai_receive(&rxbuffer, 1) == ESP_OK)
        {
            if (rxbuffer.identifier == txbuffer.identifier)
            {
                res = *(float *)&rxbuffer.data[0];
                break;
            }
        }
    }
    return res;
}

/*发送指令使电机根据当前模式按照目标值运行,Data[0]—Data[3]数据从低位到高位，输入转换后的十六进制数*/
void rc_spr(int id, float shuju)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x15;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 4;
    float *p1 = (float *)&txbuffer.data[0];
    *p1 = shuju;
    twai_transmit(&txbuffer, 0);
}

/*位置模式下，发送指令使电机按照指定速度和限制电流参数运行到指定位置
Data[0]—Data[3]的值代表电机运行到的位置，Data[4]—Data[7]的值代表电机运行的速度*/
void rc_spt(int id, float position, float speed)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x17;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 8;
    float *p1 = (float *)&txbuffer.data[0];
    *p1 = position;
    float *p2 = (float *)&txbuffer.data[4];
    *p2 = speed;
    twai_transmit(&txbuffer, 0);
}

/*发送指令设置连续轨迹运行的位置数据参数
Data[0]—Data[1]代表索引值，00 00为设置第0号点，Data[2]—Data[5]数据从低位到高位，输入转换后的十六进制数。*/
void rc_set_ctp(int id, uint16_t suoyin, float shuju)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x19;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 6;
    uint16_t *p1 = (uint16_t *)&txbuffer.data[0];
    *p1 = suoyin;
    float *p2 = (float *)&txbuffer.data[4];
    *p2 = shuju;
    twai_transmit(&txbuffer, 0);
}

/*发送指令设置连续轨迹运行的速度数据参数
Data[0]—Data[1]代表索引值，00 00为设置第0号点，Data[2]—Data[5]数据从低位到高位，输入转换后的十六进制数。*/
void rc_set_ctv(int id, uint16_t suoyin, float shuju)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x1b;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 6;
    uint16_t *p1 = (uint16_t *)&txbuffer.data[0];
    *p1 = suoyin;
    float *p2 = (float *)&txbuffer.data[4];
    *p2 = shuju;
    twai_transmit(&txbuffer, 0);
}

/*发送指令设置连续轨迹运行的矩流数据参数
Data[0]—Data[1]代表索引值，00为设置第0号点，Data[2]—Data[5]数据从低位到高位，输入转换后的十六进制数。*/
void rc_set_ctmf(int id, u_int16_t suoyin, float shuju)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x1b;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 6;
    uint16_t *p1 = (uint16_t *)&txbuffer.data[0];
    *p1 = suoyin;
    float *p2 = (float *)&txbuffer.data[4];
    *p2 = shuju;
    twai_transmit(&txbuffer, 0);
}

/*发送指令使电机按照指定的轨迹数据运行
Data[0]—Data[1]代表索引值，00为按0号点的数据运行*/
void rc_tdr(int id, uint16_t suoyin)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x1f;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 2;
    uint16_t *p1 = (uint16_t *)&txbuffer.data[0];
    *p1 = suoyin;
    twai_transmit(&txbuffer, 0);
}
/*发送指令记录当前位置速度和矩流数据到指定的数据索引位置
Data[0]—Data[1]代表索引值，00为记录到0号点*/
void rc_record(int id, uint16_t suoyin)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x21;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 2;
    uint16_t *p1 = (uint16_t *)&txbuffer.data[0];
    *p1 = suoyin;
    twai_transmit(&txbuffer, 0);
}

/*发送指令读取电机运行时的数据
Data[0]代表索引值,0x00表示读取电机当前位置数据
0x01：当前速度；0x02：Q轴电流；0x03：Q轴电压；0x04：D轴电流；
0x05：D轴电压；0x06：当前电机温度；0x07：程序版本；
0x0A：位置+速度；0x0B：Q轴电压+Q轴电流；0x0C：D轴电压+D轴电流；*/
float rc_read_rd(int id, uint8_t suoyin)
{
    if (!can_driver_installed)
        return -99999.0f;

    float res = -99999.0f;

    twai_message_t txbuffer;
    twai_message_t rxbuffer;

    txbuffer.identifier = id << 6 | 0x23;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 1;
    txbuffer.data[0] = suoyin;
    twai_transmit(&txbuffer, 0);

    unsigned long startMillis = millis();
    while (millis() - startMillis < wait_time)
    {

        if (twai_receive(&rxbuffer, 1) == ESP_OK)
        {
            if (rxbuffer.identifier == txbuffer.identifier)
            {
                res = *(float *)&rxbuffer.data[0];
                break;
            }
        }
    }
    return res;
}

/*发送指令设置CAN ID,Data[0]代表设置的电机序号
0x01表示设置电机ID为57，0x02表示设置电机ID为97，
0x03表示设置电机ID为d7，以此类推，序号每加1，对应的ID加4（ID为十六进制）*/
void rc_set_CAN_ID(int id, uint8_t suoyin)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x25;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 1;
    txbuffer.data[0] = suoyin;
    twai_transmit(&txbuffer, 0);
}

/*发送指令还原电机参数，重启电机重新校准*/
void rc_reset(int id)
{
    if (!can_driver_installed)
        return;

    twai_message_t txbuffer;
    txbuffer.identifier = id << 6 | 0x27;
    txbuffer.flags = 0;
    txbuffer.data_length_code = 0;
    twai_transmit(&txbuffer, 0);
}

/*接收数据，通过判断接收的ID来确定是在使用哪个功能，进一步根据返回的数据，来判断显示出当前的状态
注：对于接收的数据需进行一个有效性的判断*/
