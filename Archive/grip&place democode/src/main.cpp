#include "test.h"

CAN_device_t CAN_cfg;             // CAN Config (CAN配置)
unsigned long previousMillis = 0; // will store last time a CAN Message was send (将存储最后一次发送的CAN消息)
const int interval = 2;        // interval at which send CAN Messages (milliseconds) (发送CAN消息的时间间隔(毫秒))
const int rx_queue_size = 10;     // Receive Queue size (接收队列大小)

void setup()
{
  pinMode(PIN_5V_EN, OUTPUT);
  digitalWrite(PIN_5V_EN, HIGH);

  pinMode(CAN_SE_PIN, OUTPUT);
  digitalWrite(CAN_SE_PIN, LOW);

  Serial.begin(115200);
  CAN_cfg.speed = CAN_SPEED_1000KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_27;
  CAN_cfg.rx_pin_id = GPIO_NUM_26;
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  // Init CAN Module (初始化CAN模块)
  ESP32Can.CANInit();

  // put your setup code here, to run once: (将您的设置代码放在此处，运行一次：)
  //让所有电机使能

  Motor1_enable();
  delay(15);
  Motor2_enable();
  delay(15);
  Motor3_enable();
  delay(15);
  Motor4_enable();
  delay(15);
  Motor5_enable();
  delay(15);
  Motor6_enable();
  delay(15);
  Motor7_enable();

}

void loop()
{

  //到位置1夹
  delay(15);
  Motor7_open();
  delay(15);
  Motor5_p1();
  delay(1000);

  Motor1_p1();
  delay(15);
  Motor2_p1();
  delay(15);
  Motor3_p1();
  delay(15);
  Motor4_p1();
  delay(15);
  Motor6_p90();
  delay(4000);

  Motor7_close();
  delay(2000);

  //2回到位置0
  Motor2_zero();
  delay(2000);


  //到位置2放下
  Motor5_p2();
  delay(15);
  Motor1_p2();
  delay(15);

  Motor2_p2();
  delay(15);
  Motor3_p2();
  delay(15);
  Motor4_p2();
  delay(15);
  Motor6_p90();
  delay(5000);

  Motor7_open();
  delay(2000);

  //回到位置0
  Motor2_zero();
  delay(15);
  // Motor3_zero();
  delay(1000);

  Motor1_zero();
  delay(15);
  Motor4_zero();
  delay(15);
  Motor5_zero();
  delay(15);
  Motor6_zero();
  delay(15);
  Motor7_close();
  delay(4000);


  //到位置2夹
  Motor7_open();
  delay(15);
  Motor5_p2();
  delay(15);
  Motor1_p2();
  delay(2000);

  Motor2_p2();
  delay(15);
  Motor3_p2();
  delay(15);
  Motor4_p2();
  delay(15);
  Motor5_p2();
  delay(15);
  Motor6_p90();
  delay(4000);

  Motor7_close();
  delay(2000);

  //2回到位置0
  Motor2_zero();
  delay(2000);

  //到位置1放
  Motor5_p1();
  delay(1000);

  Motor1_p1();
  delay(15);
  Motor2_p1();
  delay(15);
  Motor3_p1();
  delay(15);
  Motor4_p1();
  delay(15);
  Motor6_p90();
  delay(5000);

  Motor7_open();
  delay(2000); 

  //回到位置0
  Motor2_zero();
  delay(15);
  // Motor3_zero();
  delay(1000);

  Motor1_zero();
  delay(15);
  Motor4_zero();
  delay(15);
  Motor5_zero();
  delay(15);
  Motor6_zero();
  delay(15);
  Motor7_close();
  delay(4000);

}