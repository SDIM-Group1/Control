#include <PS2X_lib.h>   
#include <Servo.h>
#include <Wire.h>

PS2X ps2x; 
Servo myservo;

//right now, the library does NOT support hot-pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

int error = 0; 
byte type = 0;
byte vibrate = 0;
int angle = 0;

boolean triangle = true;
boolean x = true;
boolean fang = true;


int PWMPin = 2; //油门信号pin角
int PWMValue = 0; //0~1000
int pedal = 0; //油门值 
int newpedal = 0;

int ML = 38;

int LF = 42;

int LB = 48;

int RF = 52;

int RB = 30;

void PWM(int PWMPin, int PWMValue){  // 模拟PWM；频率100Hz
  PWMValue += 1000;
  digitalWrite(PWMPin, HIGH);
  delayMicroseconds(PWMValue);
  digitalWrite(PWMPin, LOW);
  delayMicroseconds(10000 - PWMValue);
}

void Push(int pin){
  Stop(pin);
  digitalWrite(pin,HIGH);
  }

void Pull(int pin){
  Stop(pin);
  digitalWrite(pin+1,HIGH);
  }

void Stop(int pin){
  digitalWrite(pin, LOW);
  digitalWrite(pin+1, LOW);
  }

void setup(){
 Serial.begin(57600);
 pinMode(PWMPin, OUTPUT);
 pinMode(3, OUTPUT);
  myservo.attach(9);  // 舵机在9pin上
  
 error = ps2x.config_gamepad(13,11,10,12, false, true);   //GamePad(clock, command, attention, data, Pressures?, Rumble?) 
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
      
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
  
}

void loop(){
 if(error == 1) 
  return; 
  
 if(type == 2){ 
   
   ps2x.read_gamepad();          //read controller 
   
   if(ps2x.ButtonPressed(GREEN_FRET))
     Serial.println("Green Fret Pressed");
   if(ps2x.ButtonPressed(RED_FRET))
     Serial.println("Red Fret Pressed");
   if(ps2x.ButtonPressed(YELLOW_FRET))
     Serial.println("Yellow Fret Pressed");
   if(ps2x.ButtonPressed(BLUE_FRET))
     Serial.println("Blue Fret Pressed");
   if(ps2x.ButtonPressed(ORANGE_FRET))
     Serial.println("Orange Fret Pressed");
     

    if(ps2x.ButtonPressed(STAR_POWER))
     Serial.println("Star Power Command");
    
    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
     Serial.println("Up Strum");
    if(ps2x.Button(DOWN_STRUM))
     Serial.println("DOWN Strum");
  
 
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");

    
    if(ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE
    {
        Serial.print("Wammy Bar Position:");
        Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
 }

 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   
  
    
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {   
        if(ps2x.Button(PSB_L3))
         Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
         Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         Serial.println("R2 pressed");
        if(ps2x.Button(PSB_L1))
         Serial.println("L1 pressed");
        if(ps2x.Button(PSB_R1))
         Serial.println("R1 pressed");
        if(ps2x.Button(PSB_GREEN)){
         Serial.println("Triangle pressed");
         if(triangle == false){
          triangle = true;}
            else{
              triangle = false;
              PWM(PWMPin, 0);}
              }
         
         
    }   
         
    
    if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
         Serial.println("Circle just pressed");
         
    if(ps2x.ButtonReleased(PSB_PINK)){             //will be TRUE if button was JUST released
         Serial.println("Square just released"); 
         if(fang == true){fang =false;}else{
          fang = true;}
         }    
    
    if(ps2x.NewButtonState(PSB_BLUE)){            //will be TRUE if button was JUST pressed OR released
         Serial.println("X just changed");  
          if(x == false){Serial.print("false");
          x = true;}
            else{Serial.print("true");
              x = false;
              } 
              newpedal = pedal; 
    }
    
    if(false) // print stick values if either is TRUE
    {
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); 
    } 

    
    angle = ps2x.Analog(PSS_LX); //左摇杆x控制舵机
    //angle = map(angle, 0, 255, 2 0, 160);  //scaling the value to legal angle value
  if(fang == 1){
    myservo.write(angle);
  delay(5);}

  pedal = 127 - ps2x.Analog(PSS_RY);//右摇杆y控制螺旋桨
  pedal = map(pedal, 0, 127, 0, 999); 
  Serial.print(pedal);
  Serial.print(" ");
  if(triangle == true){PWM(PWMPin, pedal);}else{
    PWM(PWMPin, newpedal);
    Serial.print(newpedal);Serial.print(" ");
    }  // 设置油门大小0~1000  

  if(ps2x.Analog(PSS_LY) > 140){
    Pull(ML);
    }else if(ps2x.Analog(PSS_LY) < 110){
      Push(ML);}else Stop(ML);


  if(ps2x.Button(PSB_PAD_UP)){
    if(ps2x.Button(PSB_R2)){Push(RB );}else{Stop(RB);}
    if(ps2x.Button(PSB_R1)){Push(RF);}else{Stop(RF);}
    if(ps2x.Button(PSB_L2)){Push(LB);}else{Stop(LB);}
    if(ps2x.Button(PSB_L1)){Push(LF);}else{Stop(LF);}
    }else{if(ps2x.Button(PSB_PAD_DOWN)){
    if(ps2x.Button(PSB_R2)){Pull(RB);}else{Stop(RB);}
    if(ps2x.Button(PSB_R1)){Pull(RF);}else{Stop(RF);}
    if(ps2x.Button(PSB_L2)){Pull(LB);}else{Stop(LB);}
    if(ps2x.Button(PSB_L1)){Pull(LF);}else{Stop(LF);}
      }else{
        Stop(LB);
        Stop(RF);
        Stop(RB);
        Stop(LF);
      }
        }
      
  delay(5);
 }
 
 
 delay(50);
     
}