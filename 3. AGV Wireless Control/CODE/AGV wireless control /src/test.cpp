#include "test.h"

int num1;
int num2;


/*运行*/

/*void positionrun(int speed, int32_t position)
{
    // CAN_frame_t rx_frame;
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.FIR.B.RTR =CAN_no_RTR;
    tx_frame.MsgID = 0x141;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA4;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = speed;
    tx_frame.data.u8[3] = speed>>8;
    tx_frame.data.u8[4] = -position;
    tx_frame.data.u8[5] = -position>>8;
    tx_frame.data.u8[6] = -position>>16;
    tx_frame.data.u8[7] = -position>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
    tx_frame.MsgID = 0x142;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA4;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = speed;
    tx_frame.data.u8[3] = speed>>8;
    tx_frame.data.u8[4] = -position;
    tx_frame.data.u8[5] = -position>>8;
    tx_frame.data.u8[6] = -position>>16;
    tx_frame.data.u8[7] = -position>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
    tx_frame.MsgID = 0x143;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA4;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = speed;
    tx_frame.data.u8[3] = speed>>8;
    tx_frame.data.u8[4] = position;
    tx_frame.data.u8[5] = position>>8;
    tx_frame.data.u8[6] = position>>16;
    tx_frame.data.u8[7] = position>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
    tx_frame.MsgID = 0x144;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA4;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = speed;
    tx_frame.data.u8[3] = speed>>8;
    tx_frame.data.u8[4] = position;
    tx_frame.data.u8[5] = position>>8;
    tx_frame.data.u8[6] = position>>16;
    tx_frame.data.u8[7] = position>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
}*/
void speedrun(int32_t speed)
{
    // CAN_frame_t rx_frame;
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.FIR.B.RTR =CAN_no_RTR;
    tx_frame.MsgID = 0x141;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA2;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = 0x00;
    tx_frame.data.u8[3] = 0x00;
    tx_frame.data.u8[4] = -speed;
    tx_frame.data.u8[5] = -speed>>8;
    tx_frame.data.u8[6] = -speed>>16;
    tx_frame.data.u8[7] = -speed>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
    tx_frame.MsgID = 0x142;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA2;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = 0x00;
    tx_frame.data.u8[3] = 0x00;
    tx_frame.data.u8[4] = -speed;
    tx_frame.data.u8[5] = -speed>>8;
    tx_frame.data.u8[6] = -speed>>16;
    tx_frame.data.u8[7] = -speed>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
    tx_frame.MsgID = 0x143;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA2;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = 0x00;
    tx_frame.data.u8[3] = 0x00;
    tx_frame.data.u8[4] = speed;
    tx_frame.data.u8[5] = speed>>8;
    tx_frame.data.u8[6] = speed>>16;
    tx_frame.data.u8[7] = speed>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
    tx_frame.MsgID = 0x144;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA2;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = 0x00;
    tx_frame.data.u8[3] = 0x00;
    tx_frame.data.u8[4] = speed;
    tx_frame.data.u8[5] = speed>>8;
    tx_frame.data.u8[6] = speed>>16;
    tx_frame.data.u8[7] = speed>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
}

void rotaterun(int32_t speed)
{
    // CAN_frame_t rx_frame;
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.FIR.B.RTR =CAN_no_RTR;
    tx_frame.MsgID = 0x141;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA2;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = 0x00;
    tx_frame.data.u8[3] = 0x00;
    tx_frame.data.u8[4] = -speed;
    tx_frame.data.u8[5] = -speed>>8;
    tx_frame.data.u8[6] = -speed>>16;
    tx_frame.data.u8[7] = -speed>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
    tx_frame.MsgID = 0x142;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA2;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = 0x00;
    tx_frame.data.u8[3] = 0x00;
    tx_frame.data.u8[4] = -speed;
    tx_frame.data.u8[5] = -speed>>8;
    tx_frame.data.u8[6] = -speed>>16;
    tx_frame.data.u8[7] = -speed>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
    tx_frame.MsgID = 0x143;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA2;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = 0x00;
    tx_frame.data.u8[3] = 0x00;
    tx_frame.data.u8[4] = -speed;
    tx_frame.data.u8[5] = -speed>>8;
    tx_frame.data.u8[6] = -speed>>16;
    tx_frame.data.u8[7] = -speed>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
    tx_frame.MsgID = 0x144;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0xA2;
    tx_frame.data.u8[1] = 0x00;
    tx_frame.data.u8[2] = 0x00;
    tx_frame.data.u8[3] = 0x00;
    tx_frame.data.u8[4] = -speed;
    tx_frame.data.u8[5] = -speed>>8;
    tx_frame.data.u8[6] = -speed>>16;
    tx_frame.data.u8[7] = -speed>>24;
    ESP32Can.CANWriteFrame(&tx_frame);
    delay(10);
}

/*发送指令读取电机运行时的数据
 */
/*int read_rd(int id)
{

    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.FIR.B.RTR =CAN_no_RTR;
    for (int i = 1; i < 5; i++)
    {
        tx_frame.MsgID = 0x140 + i;
        tx_frame.FIR.B.DLC = 1;
        tx_frame.data.u8[0] = 0x9C;
        ESP32Can.CANWriteFrame(&tx_frame);
        delay(1);
        CAN_frame_t rx_frame;
        xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS);
        if ( tx_frame.MsgID == rx_frame.MsgID-0x100)
        {
            rxmotortemp[i] = rx_frame.data.u8[1];
            rxmotortur[i] = rx_frame.data.u8[2]|(int16_t) rx_frame.data.u8[3]<<8;
            rxmotorspeed[i] = rx_frame.data.u8[4]|(int16_t) rx_frame.data.u8[5]<<8;
            rxmotorposition[i] = rx_frame.data.u8[6]|(int16_t) rx_frame.data.u8[7]<<8;
        }
    }
}*/


/*void reset(int id)
{
    // CAN_frame_t rx_frame;
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.MsgID = 0x140 + id;
    tx_frame.FIR.B.DLC = 1;
    tx_frame.data.u8[0] = 0x76;
    ESP32Can.CANWriteFrame(&tx_frame);
}*/

void STOP()
{
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.FIR.B.RTR = CAN_no_RTR;
    for (uint i = 1; i < 5; i++)
    {
        tx_frame.MsgID = 0x140 + i;
        tx_frame.FIR.B.DLC = 1;
        tx_frame.data.u8[0] = 0x80;
        ESP32Can.CANWriteFrame(&tx_frame);
        delay(10);
    }
}