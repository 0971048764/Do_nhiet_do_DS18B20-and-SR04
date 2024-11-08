#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define TRIG 13
#define ECHO 12
#define ONE_WIRE_BUS 9 // Chân kết nối với DS18B20 (thay đổi theo sơ đồ của bạn)

// Khởi tạo LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Khởi tạo OneWire và DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float DISTANCE;
float TEMPERATURE;

void setup() {
  lcd.init();
  lcd.backlight();
  
  // Thiết lập chân cho HCSR04
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  // Bắt đầu giao tiếp với cảm biến nhiệt độ
  sensors.begin();
}

void loop() {
  // Gọi hàm đo khoảng cách
  hamdokhoangcach();
  // Gọi hàm đo nhiệt độ
  hamdonhietdo();

  // Hiển thị khoảng cách và nhiệt độ lên LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.print(DISTANCE);
  lcd.print("cm");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(TEMPERATURE);
  lcd.print((char)223); // Ký hiệu độ (°)
  lcd.print("C");
  delay(1000);
}

void hamdokhoangcach() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  // Tính thời gian từ lúc phát hiện
  long duration = pulseIn(ECHO, HIGH);
  // Tính khoảng cách
  DISTANCE = (duration * 0.034) / 2;
}

void hamdonhietdo() {
  // Yêu cầu DS18B20 đo nhiệt độ
  sensors.requestTemperatures();
  // Đọc nhiệt độ từ DS18B20 (theo đơn vị độ C)
  TEMPERATURE = sensors.getTempCByIndex(2); 
  delay(1000);
}
