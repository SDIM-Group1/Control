int PWMPin = 2; //2~13
int PWMValue = 0; //0~1000

void PWM(int PWMPin, int PWMValue){  // 模拟PWM；频率100Hz
  PWMValue += 1000;
  digitalWrite(PWMPin, HIGH);
  delayMicroseconds(PWMValue);
  digitalWrite(PWMPin, LOW);
  delayMicroseconds(10000 - PWMValue);
}

void setup(){

  pinMode(PWMPin, OUTPUT);

  for(int i = 0; i <= 220; i++){  // 循环220次，时间两秒多；油门最大，模拟量程标定
    PWM(PWMPin, 1000);
  }

  for(int i = 0; i <= 110; i++){  // 循环110次，时间一秒多；油门最小
    PWM(PWMPin, 0);
  }

}

void loop(){
  
  PWM(PWMPin, 100);  // 设置油门大小0~1000  
  delay(1000);
  
}
