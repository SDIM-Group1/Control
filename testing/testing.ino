#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define joyX A0
int PWMPin = 2; //2~13
int PWMValue = 0; //0~1000
int pedal = 0;

LiquidCrystal_I2C lcd(0x27,16,2);

void PWM(int PWMPin, int PWMValue){  // 模拟PWM；频率100Hz
  PWMValue += 1000;
  digitalWrite(PWMPin, HIGH);
  delayMicroseconds(PWMValue);
  digitalWrite(PWMPin, LOW);
  delayMicroseconds(10000 - PWMValue);
}



void setup(){
  lcd.init();
  lcd.backlight(); // 打开背光
  pinMode(PWMPin, OUTPUT);
  Serial.begin(9600);

  for(int i = 0; i <= 220; i++){  // 循环220次，时间两秒多；油门最大，模拟量程标定
    PWM(PWMPin, 1000);
  }
 
  for(int i = 0; i <= 110; i++){  // 循环110次，时间一秒多；油门最小
    PWM(PWMPin, 0);
  }

}



void loop(){
  pedal = analogRead(joyX);
  if(pedal > 999){ 
    pedal = 999;
    }
  PWM(PWMPin, pedal);  // 设置油门大小0~1000  
   lcd.setCursor(0,0);
  lcd.print("Motor Speed:");
  lcd.setCursor(0,1);
  lcd.print(pedal);
  delay(100);
  Serial.print(pedal);
}
