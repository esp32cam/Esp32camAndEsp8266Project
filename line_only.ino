/* 
 * เป็น Code ของ Algorithm สำหรับสั่งการให้ NodeMCU ESP8266 
 * ทำการส่งแจ้งเตือนเข้าไปในไลน์ของเจ้าของ เมื่อมีคนยกสิ่งของออกจากแท่นวาง
 * ลิขสิทธิ์การแข่งขันสิ่งประดิษฐ์ทางวิทยาศาสตร์ ม.ปลาย โรงเรียนห้องสอนศึกษา ในพระอุปถัมภ์ฯ 
 * ผู้จัดทำ 1.นายธนาวรรธน์ ลิ้มวรากุล 2.พงศภัค คงแจ 
 * ครูที่ปรึกษา นายสาธิต ชุมของ
 */

#include <TridentTD_LineNotify.h>

#define SSID        "Sbox" //ID ของ Wifi ที่ใช้เชื่อมต่อ
#define PASSWORD    "999999999" //PASSWORD ของ Wifi ที่ใช่เชื่อมต่อ
#define LINE_TOKEN  "fAaE9BYoyMkAxVynoCqbfWe7Nee9p4ZodjlZ0Ky8Ij6"



void setup() {
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
  

  // เรียก Line Token
  LINE.setToken(LINE_TOKEN);
}

void loop() 
{

  LINE.setToken(LINE_TOKEN);
  
  // ให้ Line แสดงข้อความแจ้งเตือน
  LINE.notify("แจ้งเตือน!!!!สินค้าของท่านได้ถูกยกออกจากแท่นวาง!!!"); //แจ้งเตือนด้วยข้อความ
  LINE.notifySticker("แจ้งเตือน!!!!สินค้าของท่านได้ถูกยกออกจากแท่นวาง!!!",4,273); //แจ้งเตือนด้วยสติกเกอร์ไลน์        
  LINE.notifyPicture("https://i.ibb.co/3d1w8bv/Warning-Design-Your-Own.jpg"); //แจ้งเตือนด้วยภาพ

 

  delay(1);
}
