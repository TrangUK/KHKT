#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
const int trig = 8;  // Chân trig nối với chân số 8
const int echo = 7;  // Chân echo nối với chân số 7
const int relay = 6; // Chân điều khiển relay
unsigned long thoigian;  // Thời gian là kiểu số nguyên
int khoangcach;          // Khoảng cách là kiểu số nguyên
int khoangcachtruoc = 0; // Khởi tạo khoảng cách trước là 0
LiquidCrystal_I2C lcd(0x27,16,2); // LCD 16x2, địa chỉ I2C là 0x27
void setup() {
  Serial.begin(9600); // Mở cổng Serial ở 9600
  pinMode(trig, OUTPUT); // Chân trig là chân xuất
  pinMode(echo, INPUT);  // Chân echo là chân nhập
  pinMode(relay, OUTPUT); // Chân điều khiển relay là chân xuất
  lcd.init();       // Khởi động LCD
  lcd.backlight();  // Bật đèn nền
  lcd.setCursor(3,0); 
  lcd.print("SLOW DOWN!"); 
}
void loop() {
  // Phát xung từ chân trig, có độ rộng là 10ms
  digitalWrite(trig, LOW);
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);
  // Nhận xung phản xạ tại chân echo
  thoigian = pulseIn(echo, HIGH);
  // Tính khoảng cách đến vật thể (đơn vị là cm)
  khoangcach = int(thoigian / 2 / 29.412);
  // Kiểm tra các điều kiện khoảng cách
  if (khoangcach < 15) {
    // Khi khoảng cách nhỏ hơn 15 cm
    lcd.setCursor(0,1);
    lcd.print("Distance cm:<15 ");
    digitalWrite(relay, HIGH); // TẮT relay
  } 
  else if (khoangcach < khoangcachtruoc && khoangcach <= 40) {
    // Khi khoảng cách trong khoảng 15-40 cm và nhỏ hơn khoảng cách trước đó
    lcd.setCursor(0,1);
    lcd.print("Distance cm:<");
    lcd.print(khoangcach);
    lcd.print("   ");
    digitalWrite(relay, LOW); // Bật relay
  } 
  else {
    // Khi xe đi xa hoặc nằm ngoài phạm vi
    lcd.setCursor(0,1);
    lcd.print("  Out of range   ");
    digitalWrite(relay, HIGH); // Tắt relay
  }
  // Cập nhật khoảng cách trước
  khoangcachtruoc = khoangcach;
  delay(500); // Giảm độ nhạy cảm biến
}

