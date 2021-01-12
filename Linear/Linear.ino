void setup() {
  // put your setup code here, to run once:
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);

}
int MLH = 22;
int MLL = 23;//主推杆

int LFH = 24;
int LFL = 25;

int LBH = 26;
int LBL = 27;

int RFH = 28;
int RFL = 29;

int RBH = 30;
int RBL = 31;

void Push(int pin){
  digitalWrite(pin,HIGH);
  }

void Pull(int pin){
  digitalWrite(pin,HIGH);
  }

void Stop(int pinA, int pinB){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  }

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(22,HIGH);//推杆推出
  delay(1000);
  digitalWrite(22,LOW);//停止
  delay(1000);
  digitalWrite(MLH+1,HIGH);//推杆回收
  delay(1000);
  digitalWrite(23,LOW);//停止
  delay(1000);
  

}
