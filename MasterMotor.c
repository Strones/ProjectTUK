#include <Servo.h>
#define HOLD 4294967295
#define OKAY 16761405
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
#define NEUTRAL_UD_LEFT 80
#define NEUTRAL_LR_RIGHT 70 //More = left (TUK perspective)
#define NEUTRAL_LR_LEFT 80
#define COM_PIN 6
#define ANGRY_T 99000
#define SAD_T 198000
#define FEAR_T 298000
#define DISGUST_T 397000
#define HAPPY_T 496000
#define DELTA 10000
#define INTERVAL 3000
#define IDLE_COUNT 8 //How often the idle action will be taken till timeout
#define STANDBY_COUNT 12
Servo ud_left;
Servo ud_right;
Servo lr_left;
Servo lr_right;
Servo ServoRightTurn;
Servo ServoLeftTurn;
Servo ServoRightBlink;
Servo ServoLeftBlink;

int jan = 1500;
int pos = 0, pos2 = 0, prev_command, go = 1, idleCount = 0;
unsigned long lastActive = 0;

void setup() {
  Serial.begin(115200);
  //irrecv.enableIRIn();
  // put your setup code here, to run once:
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
   ServoLeftTurn.write(118); //NORMAL
   ServoRightTurn.write(100);//NORMAL
   ServoLeftBlink.write(90); //NORMAL weniger: tiefer
   ServoRightBlink.write(30);//NORMAL  mehr: tiefer
  }

   if(millis() - lastActive > INTERVAL) {
    idleCount++;
    if(idleCount < IDLE_COUNT) {
      switch(random(1,15)) {
        case 1:
        case 2:
        case 3:
          look_left();
          look_left_back();
          break;
        case 4:
        case 5:
        case 6:
          look_right();
          look_right_back();
          break;
        case 8:
        case 7:
          look_up();
          break;
        case 9:
          look_down();
          break;
        case 10:
        case 11:
          blink_left();
          break;
        case 12:
        case 13:
          blink_right();
          break;
      }
    } else if(idleCount == STANDBY_COUNT) {
        close_eyes(); 
    }
    lastActive = millis();
   }

  
   long em_val = pulseIn(COM_PIN, HIGH);
////   Serial.println(em_val);
   
//ANGRY
   if((ANGRY_T-DELTA <= em_val) && (em_val <= ANGRY_T+DELTA)) {
    idleCount = 0;
      lastActive = millis();
      go_neutral();
      ServoLeftTurn.write(160); //ANGRY
      ServoRightTurn.write(75); //ANGRY 
      delay(jan);
      lastActive = millis();    
   }
//SAD
   if((SAD_T-DELTA <= em_val) && (em_val <= SAD_T+DELTA)) {
    idleCount = 0;
      lastActive = millis();
      ServoLeftTurn.write(85); //SAD
      ServoRightTurn.write(145); //SAD
      look_inward();
      delay(jan);
      lastActive = millis(); 
   }
//FEAR   
   if((FEAR_T-DELTA <= em_val) && (em_val <= FEAR_T+DELTA)) {
    idleCount = 0;
      lastActive = millis();
      ServoRightBlink.write(0);
      ServoLeftBlink.write(120);
      look_up();
      delay(jan);
      lastActive = millis();
   }   
//DISGUST   
   if((DISGUST_T-DELTA <= em_val) && (em_val <= DISGUST_T+DELTA)) {
    idleCount = 0;
      go_neutral();
      lastActive = millis();
      ServoLeftBlink.write(110);
      ServoRightBlink.write(50); 
      delay(jan);
      lastActive = millis();
   }
//HAPPPY
   if((HAPPY_T-DELTA <= em_val) && (em_val <= HAPPY_T+DELTA)) {
    idleCount = 0;
      go_neutral();
      lastActive = millis();
      close_eyes();
      for (pos = 125; pos >= 25; pos -= 1) {
        ServoRightBlink.write(pos); 
        if(125-pos <= 85) ServoLeftBlink.write(125-pos);
        delay(15);
    }
    delay(200);
    ServoLeftBlink.write(100); //NORMAL weniger: tiefer
    ServoRightBlink.write(30);//NORMAL  mehr: tiefer 
    delay(jan);
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
    delay(30);
  }
}


void look_left_back() {
  int lr_l, lr_r;
  for (lr_l = NEUTRAL_LR_LEFT, lr_r = NEUTRAL_LR_RIGHT, pos = LR_DELTA; pos > 0; pos--) {
    lr_left.write(lr_l + pos);
    lr_right.write(lr_r + pos);
    delay(30);
  }
}

void close_eyes() {
   for (pos = 25; pos <= 120; pos += 1) {
        ServoRightBlink.write(pos);
        ServoLeftBlink.write(125-pos);
        delay(15);
      }
}

void look_right() {
  int lr_l, lr_r;
  for (lr_l = NEUTRAL_LR_LEFT, lr_r = NEUTRAL_LR_RIGHT, pos = 0; pos < LR_DELTA; pos++) {
    lr_left.write(lr_l - pos);
    lr_right.write(lr_r - pos);
    delay(30);
  }
}

void look_right_back(){
   int lr_l, lr_r;
  for (lr_l = NEUTRAL_LR_LEFT, lr_r = NEUTRAL_LR_RIGHT, pos = LR_DELTA; pos > 0; pos--) {
    lr_left.write(lr_l - pos);
    lr_right.write(lr_r - pos);
    delay(30);
  }
}

void look_up() {
  int ud_l, ud_r;
  for (ud_l = NEUTRAL_UD_LEFT, ud_r = NEUTRAL_UD_RIGHT, pos = 0; pos < UD_DELTA; pos++) {
    ud_left.write(ud_l + pos);
    ud_right.write(ud_r + pos);
    delay(30);
  }
}

void blink_left() {
  ServoLeftBlink.write(25);
}

void blink_right() {
  ServoRightBlink.write(160);
}

void look_down() {
  int ud_l, ud_r;
  for (ud_l = NEUTRAL_UD_LEFT, ud_r = NEUTRAL_UD_RIGHT, pos = 0; pos < 10; pos++) {
    ud_left.write(ud_l - pos);
    ud_right.write(ud_r - pos);
    delay(30);
  }
}

void look_inward() {
  int ud_l = NEUTRAL_UD_LEFT, ud_r = NEUTRAL_UD_RIGHT, lr_l = NEUTRAL_LR_LEFT, lr_r = NEUTRAL_LR_RIGHT;
  for(pos=0; pos < 15; pos++) {
    ud_left.write(ud_l - pos);
    ud_right.write(ud_r - pos);
    lr_right.write(lr_r + pos);
    lr_left.write(lr_l - pos);
    delay(30);
  }
}
