#include <Servo.h>
#define HOLD 4294967295
#define OKAY 16761405
#define NECK 7
#define RL_NOSE 13
#define UD_NOSE 12
#define UD_LEFT 5
#define UD_RIGHT 3
#define LR_LEFT 2
#define LR_RIGHT 4
#define LEFT_TURN 11
#define LEFT_BLINK 8
#define LR_DELTA 30
#define UD_DELTA 15
#define RIGHT_BLINK 9
#define RIGHT_TURN 10
#define NEUTRAL_UD_RIGHT 110 //More = up
#define NEUTRAL_UD_LEFT 145
#define NEUTRAL_LR_RIGHT 55 //More = left (TUK perspective)
#define NEUTRAL_LR_LEFT 70
#define ANGRY_LEFT_TURN 140 //Former 120
#define ANGRY_RIGHT_TURN 60
#define SAD_LEFT_TURN 70
#define SAD_RIGHT_TURN 150
#define SAD_UD_NOSE 110
#define SURPRISE_UD_NOSE 50
#define DISGUST_LEFT_BLINK 60
#define DISGUST_RIGHT_BLINK 80
#define DISGUST_RL_NOSE 60
#define DISGUST_UD_NOSE 70
#define LEFT_BLINK_MOVEMENT 100
#define RIGHT_BLINK_MOVEMENT 160
#define COM_PIN 6
#define ANGRY_T 99000
#define SAD_T 298000
#define FEAR_T 198000
#define DISGUST_T 397000
#define HAPPY_T 496000
#define DELTA 10000
#define INTERVAL 3000
#define IDLE_COUNT 12 //How often the idle action will be taken till timeout
#define STANDBY_COUNT 12
#define LEFTTURN_NORMAL 120 //LINKES AUGE TURN Former: 100
#define LEFTTURN_IB 140 //Former: 105 
#define LEFTTURN_OB 30
#define RIGHTTURN_NORMAL 100
#define RIGHTTURN_IB 60
#define RIGHTTURN_OB 150
#define LEFTBLINK_NORMAL 120
#define LEFTBLINK_IB 10
#define LEFTBLINK_OB 110
#define RIGHTBLINK_NORMAL 60
#define RIGHTBLINK_IB 160
#define RIGHTBLINK_OB 20
#define UDNOSE_NORMAL 80
#define UDNOSE_IB 110
#define UDNOSE_OB 20
#define RLNOSE_NORMAL 50
#define RLNOSE_IB 80
#define RLNOSE_OB 0
#define NECK_NORMAL 85
#define NECK_IB 40
#define NECK_OB 130
#define NECK_SWING_DELAY 15
#define NOSE_WIGGLE_DELAY 10
#define NOSE_SWING_DELAY 50
#define NOSE_NOD_DELAY 15
#define MOVEMENT_DELAY 30

Servo ud_left;
Servo ud_right;
Servo lr_left;
Servo lr_right;
Servo ServoRightTurn;
Servo ServoLeftTurn;
Servo ServoRightBlink;
Servo ServoLeftBlink;

Servo neck;
Servo udNose;
Servo rlNose;

int jan = 700;
int pos = 0, pos2 = 0, prev_command, go = 1, idleCount = 0, sleep = 0, start =1, plus =0;
unsigned long lastActive = 0;

void setup() {
  
  Serial.begin(9600);

  neck.attach(NECK);
  udNose.attach(UD_NOSE);
  rlNose.attach(RL_NOSE);
  ud_left.attach(UD_LEFT);
  ud_right.attach(UD_RIGHT);
  lr_left.attach(LR_LEFT);
  lr_right.attach(LR_RIGHT);
  ServoRightTurn.attach(RIGHT_TURN);
  ServoLeftTurn.attach(LEFT_TURN);
  ServoRightBlink.attach(RIGHT_BLINK);
  ServoLeftBlink.attach(LEFT_BLINK);
  lastActive = millis();


}

void loop() {

  
  //Neutralpositionen
  if(idleCount < STANDBY_COUNT) {
    
   go_neutral();
   ServoLeftTurn.write(LEFTTURN_NORMAL); //NORMAL
   ServoRightTurn.write(RIGHTTURN_NORMAL);//NORMAL
   ServoLeftBlink.write(LEFTBLINK_NORMAL); //NORMAL weniger: tiefer
   ServoRightBlink.write(RIGHTBLINK_NORMAL);//NORMAL  mehr: tiefer
   udNose.write(UDNOSE_NORMAL);
   rlNose.write(RLNOSE_NORMAL);
   neck.write(NECK_NORMAL);

  if(start == 1){
    close_eyes();
    start = 0;
    sleep = 1;
    idleCount = STANDBY_COUNT;
  }
   
  }

   if(millis() - lastActive > INTERVAL) {
    idleCount++;
    if(idleCount < IDLE_COUNT) {
      switch(random(1,15)) {
        case 1:
          nose_wiggle();
            break;
        case 2:
        //  nose_nod();
          break;
        case 3:
          look_left();
          look_left_back();
          break;
        case 4:
        case 5:
          neck_swing();
          break;
        case 6:
          look_right();
          look_right_back();
          break;
        case 8:
          nose_wiggle();
          break;
        case 7:
          look_up();
          break;
        case 9:
          look_down();
          break;
        case 10:
          //nose_nod();
          break;
        case 11:
          blink_left();
          break;
        case 12:
         // nose_swing();
          break;
        case 13:
          blink_right();
          break;
      }
    } else if(idleCount == STANDBY_COUNT) {
        close_eyes();
        sleep = 1; 
    }
    lastActive = millis();
   }

  
   long em_val = pulseIn(COM_PIN, HIGH);
////   Serial.println(em_val);
   
//ANGRY
   if((ANGRY_T-DELTA <= em_val) && (em_val <= ANGRY_T+DELTA)) {
    if(sleep == 1){
      wake_up();
      sleep = 0;
    }else{
    idleCount = 0;
      lastActive = millis();
      go_neutral();
      ServoLeftTurn.write(ANGRY_LEFT_TURN); //ANGRY
      ServoRightTurn.write(ANGRY_RIGHT_TURN); //ANGRY
      delay(400);
      nose_wiggle(); 
      delay(jan);
      lastActive = millis();
    }      
   }
//SAD
   if((SAD_T-DELTA <= em_val) && (em_val <= SAD_T+DELTA)) {
    if(sleep == 1){
      wake_up();
      sleep = 0;
    }else{
    idleCount = 0;
      lastActive = millis();
      look_inward();
      ServoLeftTurn.write(SAD_LEFT_TURN); //SAD
      ServoRightTurn.write(SAD_RIGHT_TURN); //SAD
      udNose.write(SAD_UD_NOSE);     
      delay(jan);
      lastActive = millis(); 
    }
   }
//FEAR  SURPRISE
   if((FEAR_T-DELTA <= em_val) && (em_val <= FEAR_T+DELTA)) {
    if(sleep == 1){
      wake_up();
      sleep = 0;
    }else{
    idleCount = 0;
      lastActive = millis(); 
  /*      
       int ud_l, ud_r;
  for (ud_l = NEUTRAL_UD_LEFT, ud_r = NEUTRAL_UD_RIGHT, pos = 0; pos < UD_DELTA; pos++) {
    ud_left.write(ud_l + pos);
    ud_right.write(ud_r + pos);
    delay(10);
  }
  */       
      ServoRightBlink.write(RIGHTBLINK_OB);
      ServoLeftBlink.write(LEFTBLINK_OB);
      udNose.write(SURPRISE_UD_NOSE);
      neck_swing();           
      delay(jan);
      lastActive = millis();
      
    }
   }   
//DISGUST   
   if((DISGUST_T-DELTA <= em_val) && (em_val <= DISGUST_T+DELTA)) {
    if(sleep == 1){
      wake_up();
      sleep = 0;
    }else{
    idleCount = 0;
      go_neutral();
      lastActive = millis();
      ServoLeftBlink.write(DISGUST_LEFT_BLINK);
      ServoRightBlink.write(DISGUST_RIGHT_BLINK);
     rlNose.write(DISGUST_RL_NOSE);
     udNose.write(DISGUST_UD_NOSE), 
      delay(jan);
      lastActive = millis();
    }
   }
//HAPPY
   if((HAPPY_T-DELTA <= em_val) && (em_val <= HAPPY_T+DELTA)) {
    if(sleep == 1){
      wake_up();
      sleep = 0;
    }else{
    idleCount = 0;
      go_neutral();
      lastActive = millis();
       for (pos = 25; pos <= 160; pos += 1) {
        ServoRightBlink.write(pos);
        ServoLeftBlink.write(150-pos);
        
           udNose.write(80+plus);
          if(plus < 20){
            plus++;
          }
       
        delay(15);
      }
    }
    delay(200);
    ServoLeftBlink.write(LEFTBLINK_NORMAL); //NORMAL weniger: tiefer
    ServoRightBlink.write(RIGHTBLINK_NORMAL);//NORMAL  mehr: tiefer 
    udNose.write(UDNOSE_NORMAL);
    delay(jan);
    plus=0;
    lastActive = millis();
   }
   
}

void go_neutral() {
  lr_left.write(NEUTRAL_LR_LEFT);
  ud_left.write(NEUTRAL_UD_LEFT);
  lr_right.write(NEUTRAL_LR_RIGHT);
  ud_right.write(NEUTRAL_UD_RIGHT);
}

void look_left() {
  int lr_l, lr_r;
  for (lr_l = NEUTRAL_LR_LEFT, lr_r = NEUTRAL_LR_RIGHT, pos = 0; pos < LR_DELTA; pos++) {
    lr_left.write(lr_l + pos);
    lr_right.write(lr_r + pos);
    delay(MOVEMENT_DELAY);
  }
}


void look_left_back() {
  int lr_l, lr_r;
  for (lr_l = NEUTRAL_LR_LEFT, lr_r = NEUTRAL_LR_RIGHT, pos = LR_DELTA; pos > 0; pos--) {
    lr_left.write(lr_l + pos);
    lr_right.write(lr_r + pos);
    delay(MOVEMENT_DELAY);
  }
}

void close_eyes() {
   for (pos = 25; pos <= 160; pos += 1) {
        ServoRightBlink.write(pos);
        ServoLeftBlink.write(170-pos);
        delay(MOVEMENT_DELAY);
      }
}

void look_right() {
  int lr_l, lr_r;
  for (lr_l = NEUTRAL_LR_LEFT, lr_r = NEUTRAL_LR_RIGHT, pos = 0; pos < LR_DELTA; pos++) {
    lr_left.write(lr_l - pos);
    lr_right.write(lr_r - pos);
    delay(MOVEMENT_DELAY);
  }
}

void look_right_back(){
   int lr_l, lr_r;
  for (lr_l = NEUTRAL_LR_LEFT, lr_r = NEUTRAL_LR_RIGHT, pos = LR_DELTA; pos > 0; pos--) {
    lr_left.write(lr_l - pos);
    lr_right.write(lr_r - pos);
    delay(MOVEMENT_DELAY);
  }
}

void look_up() {
  int ud_l, ud_r;
  for (ud_l = NEUTRAL_UD_LEFT, ud_r = NEUTRAL_UD_RIGHT, pos = 0; pos < UD_DELTA; pos++) {
    ud_left.write(ud_l + pos);
    ud_right.write(ud_r + pos);
    delay(MOVEMENT_DELAY);
  }
}

void look_up_down() {
  int ud_l, ud_r;
  for (ud_l = NEUTRAL_UD_LEFT, ud_r = NEUTRAL_UD_RIGHT, pos = 0; pos < UD_DELTA; pos++) {
    ud_left.write(ud_l + pos);
    ud_right.write(ud_r + pos);
    delay(MOVEMENT_DELAY);
}
}

void blink_left() {
  ServoLeftBlink.write(LEFT_BLINK_MOVEMENT);
}

void blink_right() {
  ServoRightBlink.write(RIGHT_BLINK_MOVEMENT);
}

void look_down() {
  int ud_l, ud_r;
  for (ud_l = NEUTRAL_UD_LEFT, ud_r = NEUTRAL_UD_RIGHT, pos = 0; pos < 10; pos++) {
    ud_left.write(ud_l - pos);
    ud_right.write(ud_r - pos);
    delay(MOVEMENT_DELAY);
  }
}

void look_inward() {
  int ud_l = NEUTRAL_UD_LEFT, ud_r = NEUTRAL_UD_RIGHT, lr_l = NEUTRAL_LR_LEFT, lr_r = NEUTRAL_LR_RIGHT;
  for(pos=0; pos < 15; pos++) {
    ud_left.write(ud_l+5 - pos);
    ud_right.write(ud_r - pos);
    lr_right.write(lr_r + pos);
    lr_left.write(lr_l - pos);
    delay(MOVEMENT_DELAY);
  }
}

void nose_swing(){      //rotates the nose
 for(int i =RLNOSE_NORMAL;i< 80;i++){
  rlNose.write(i);
  delay(NOSE_SWING_DELAY);
 }

 for(int i =80;i>0;i--){
  rlNose.write(i);
  delay(NOSE_SWING_DELAY);
 }

 rlNose.write(RLNOSE_NORMAL);
}

void nose_nod(){       //moves the nose up and down
 for(int i =UDNOSE_NORMAL;i> UDNOSE_OB+20;i--){
  udNose.write(i);
  delay(NOSE_NOD_DELAY);
 }

 for(int i =UDNOSE_OB+20;i>UDNOSE_IB-30;i++){
  udNose.write(i);
  delay(NOSE_NOD_DELAY);
 }

}

void nose_wiggle(){

 for(int i =RLNOSE_NORMAL;i<60;i++){
  rlNose.write(i);
  delay(NOSE_WIGGLE_DELAY);
 }

  for(int i =60;i>40;i--){
  rlNose.write(i);
  delay(NOSE_WIGGLE_DELAY);
 }

   for(int i =40;i<RLNOSE_NORMAL;i++){
  rlNose.write(i);
  delay(NOSE_WIGGLE_DELAY);
 }
 
}

void neck_swing(){        // rotates the neck
  for(int i =NECK_NORMAL;i< 130;i++){
  neck.write(i);
  delay(NECK_SWING_DELAY);
 }

 for(int i =130;i> 40;i--){
  neck.write(i);
  delay(NECK_SWING_DELAY);
 }

for(int i=40;i<NECK_NORMAL;i++){
  neck.write(i);
  delay(NECK_SWING_DELAY);
}

 neck.write(NECK_NORMAL);
}

void wake_up(){
  ServoRightBlink.write(20);
      ServoLeftBlink.write(LEFTBLINK_OB);
      udNose.write(50);           
      delay(jan);
      lastActive = millis();
      neck_swing();
      go_normal();
}

void go_normal(){
    go_neutral();
   ServoLeftTurn.write(LEFTTURN_NORMAL); //NORMAL
   ServoRightTurn.write(RIGHTTURN_NORMAL);//NORMAL
   ServoLeftBlink.write(LEFTBLINK_NORMAL); //NORMAL weniger: tiefer
   ServoRightBlink.write(RIGHTBLINK_NORMAL);//NORMAL  mehr: tiefer
   udNose.write(UDNOSE_NORMAL);
   rlNose.write(RLNOSE_NORMAL);
   neck.write(NECK_NORMAL);
}


