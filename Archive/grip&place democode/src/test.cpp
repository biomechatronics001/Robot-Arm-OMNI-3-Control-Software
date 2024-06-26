#include "test.h"


//1轴到达1号位置
void Motor1_p1()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x57;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x0A;
  tx_frame.data.u8[1] = 0xD7;
  tx_frame.data.u8[2] = 0x63;
  tx_frame.data.u8[3] = 0x3F;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//2轴到达1号位置
void Motor2_p1()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x97;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0xCC;
  tx_frame.data.u8[1] = 0xCC;
  tx_frame.data.u8[2] = 0x26;
  tx_frame.data.u8[3] = 0xC2;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0x40;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//3轴到达1号位置
void Motor3_p1()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0xD7;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x7A;
  tx_frame.data.u8[1] = 0x14;
  tx_frame.data.u8[2] = 0x98;
  tx_frame.data.u8[3] = 0x42;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//4轴到达1号位置
void Motor4_p1()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x117;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0x00;
  tx_frame.data.u8[3] = 0xC1;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//5轴到达1号位置
void Motor5_p1()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x157;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x7A;
  tx_frame.data.u8[1] = 0x14;
  tx_frame.data.u8[2] = 0x86;
  tx_frame.data.u8[3] = 0x42;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//6轴到达90°位置
void Motor6_p90()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x197;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0xB4;
  tx_frame.data.u8[3] = 0x42;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//6轴到达0°位置
void Motor6_zero()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x197;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0x00;
  tx_frame.data.u8[3] = 0x00;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}


//夹爪张开
void Motor7_open()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x1D7;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x80;
  tx_frame.data.u8[2] = 0xBB;
  tx_frame.data.u8[3] = 0x44;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xFA;
  tx_frame.data.u8[7] = 0x43;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//夹爪闭合
void Motor7_close()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x1D7;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0x00;
  tx_frame.data.u8[3] = 0x00;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xFA;
  tx_frame.data.u8[7] = 0x43;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//1轴到达2号位置
void Motor1_p2()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x57;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0xAE;
  tx_frame.data.u8[1] = 0xC7;
  tx_frame.data.u8[2] = 0xAB;
  tx_frame.data.u8[3] = 0xC2;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//2轴到达2号位置
void Motor2_p2()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x97;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0x5C;
  tx_frame.data.u8[3] = 0xC2;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0x40;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//3轴到达2号位置
void Motor3_p2()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0xD7;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x14;
  tx_frame.data.u8[1] = 0xAE;
  tx_frame.data.u8[2] = 0x4F;
  tx_frame.data.u8[3] = 0x42;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//4轴到达2号位置
void Motor4_p2()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x117;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0x00;
  tx_frame.data.u8[3] = 0xC1;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//5轴到达2号位置
void Motor5_p2()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x157;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0xA3;
  tx_frame.data.u8[1] = 0x70;
  tx_frame.data.u8[2] = 0xA0;
  tx_frame.data.u8[3] = 0x42;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}


//1轴到达0
void Motor1_zero()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x57;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0x00;
  tx_frame.data.u8[3] = 0x00;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//2轴到达0
void Motor2_zero()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x97;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0x00;
  tx_frame.data.u8[3] = 0x00;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0x40;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//3轴到达0
void Motor3_zero()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0xD7;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0x00;
  tx_frame.data.u8[3] = 0x00;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//4轴到达0
void Motor4_zero()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x117;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0x00;
  tx_frame.data.u8[3] = 0x00;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//5轴到达0
void Motor5_zero()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x157;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x00;
  tx_frame.data.u8[1] = 0x00;
  tx_frame.data.u8[2] = 0x00;
  tx_frame.data.u8[3] = 0x00;
  tx_frame.data.u8[4] = 0x00;
  tx_frame.data.u8[5] = 0x00;
  tx_frame.data.u8[6] = 0xA0;
  tx_frame.data.u8[7] = 0x40;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//1轴使能
void Motor1_enable()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x43;
  tx_frame.FIR.B.DLC = 1;
  tx_frame.data.u8[0] = 0x01;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//2轴使能
void Motor2_enable()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x83;
  tx_frame.FIR.B.DLC = 1;
  tx_frame.data.u8[0] = 0x01;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//3轴使能
void Motor3_enable()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0xC3;
  tx_frame.FIR.B.DLC = 1;
  tx_frame.data.u8[0] = 0x01;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//4轴使能
void Motor4_enable()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x103;
  tx_frame.FIR.B.DLC = 1;
  tx_frame.data.u8[0] = 0x01;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//5轴使能
void Motor5_enable()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x143;
  tx_frame.FIR.B.DLC = 1;
  tx_frame.data.u8[0] = 0x01;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//6轴使能
void Motor6_enable()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x183;
  tx_frame.FIR.B.DLC = 1;
  tx_frame.data.u8[0] = 0x01;
  ESP32Can.CANWriteFrame(&tx_frame);
}

//7轴使能
void Motor7_enable()
{
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.MsgID = 0x1C3;
  tx_frame.FIR.B.DLC = 1;
  tx_frame.data.u8[0] = 0x01;
  ESP32Can.CANWriteFrame(&tx_frame);
}