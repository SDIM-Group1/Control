#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//PCF8574T模块4pin(Gnd, Vcc, SDA i2c数据, SCL i2c时钟)和Arduino接口的对应关系: Gnd -> Gnd, Vcc -> Vcc, SDA -> A4, SDL -> A5
// I2C地址, 一般为0x3F, 0x20或0x27
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.backlight(); // 打开背光
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("ZJH IS SB!!!");
  delay(1000);
}
