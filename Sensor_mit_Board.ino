#include "mpr121.h"
#include <Wire.h>
#define COM_PIN 3
#define ANGRY_T 100
#define SAD_T 200
#define FEAR_T 300
#define DISGUST_T 400
#define HAPPY_T 500

#define TOU_THRESH_HEAD  0x02   //Touch threshold
#define REL_THRESH_HEAD  0x05  //Release threshold
#define TOU_THRESH_NOSE  0x01
#define REL_THRESH_NOSE  0x04
#define TOU_THRESH_LEFT  0x03
#define REL_THRESH_LEFT  0x08
#define TOU_THRESH_RIGHT 0x03
#define REL_THRESH_RIGHT 0x08
#define TOU_THRESH_FRONT 0x03
#define REL_THRESH_FRONT 0x08
#define TOU_THRESH_BACK  0x03
#define REL_THRESH_BACK  0x08

#define TOU_THRESH 0xFF
#define REL_THRESH 0xFF

#define ANGRY_PIN 1
#define SAD_PIN 4
#define HAPPY_PIN 0
#define DISGUST_PIN 2
#define SURPRISE_PIN 3
#define FEAR_PIN 5


//Variables
char blueToothVal = 'z';           //value sent over via bluetooth
int act = 1;
bool rdy = true;
int irqpin = 2;  // Digital 2
boolean touchStates[12]; //to keep track of the previous touch states

void setup()                    
{
  pinMode(irqpin, INPUT);
  digitalWrite(irqpin, HIGH); //enable pullup resistor
 
  Serial.begin(9600);
  Wire.begin();

  mpr121_setup();


  //Setup port for comms
  pinMode(COM_PIN, OUTPUT);
   
}

void loop()                    
{

  unsigned long currentMillis = millis();



  if(Serial.available())
  {//if there is data being recieved
    blueToothVal=Serial.read(); //read it
  }

  readTouchInputs();
    
    digitalWrite(COM_PIN, LOW);
    delay(200);  
    blueToothVal = 'z';                           
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

void sens_angry(){
  rdy = false;
        digitalWrite(COM_PIN, HIGH);
        delay(ANGRY_T);
        digitalWrite(COM_PIN, LOW);
        act = 1;
        Serial.println("Angry");
        blueToothVal = 'z';   
}

void sens_sad(){
  rdy = false;
        digitalWrite(COM_PIN, HIGH);
        delay(SAD_T);
        digitalWrite(COM_PIN, LOW);
        act = 1;
        Serial.println("Sad");
        blueToothVal = 'z';
}

void sens_fear(){
  rdy = false;
        digitalWrite(COM_PIN, HIGH);
        delay(FEAR_T);
        digitalWrite(COM_PIN, LOW);
        act = 1;
        Serial.println("Surprise");
        blueToothVal = 'z';
}

void sens_happy(){
  rdy = false;
        digitalWrite(COM_PIN, HIGH);
        delay(HAPPY_T);
        digitalWrite(COM_PIN, LOW);
        act = 1;
        Serial.println("Happy");
        blueToothVal = 'z'; 
}

void sens_disgust(){
  rdy = false;
        digitalWrite(COM_PIN, HIGH);
        delay(DISGUST_T);
        digitalWrite(COM_PIN, LOW); 
        act = 1;
        blueToothVal == 'z';
        Serial.println("Disgust");
}

void mpr121_setup(void){

  set_register(0x5A, ELE_CFG, 0x00); 
  
  // Section A - Controls filtering when data is > baseline.
  set_register(0x5A, MHD_R, 0x01);
  set_register(0x5A, NHD_R, 0x01);
  set_register(0x5A, NCL_R, 0x00);
  set_register(0x5A, FDL_R, 0x00);

  // Section B - Controls filtering when data is < baseline.
  set_register(0x5A, MHD_F, 0x01);
  set_register(0x5A, NHD_F, 0x01);
  set_register(0x5A, NCL_F, 0xFF);
  set_register(0x5A, FDL_F, 0x02);
  
  // Section C - Sets touch and release thresholds for each electrode
  set_register(0x5A, ELE0_T, TOU_THRESH_HEAD);
  set_register(0x5A, ELE0_R, REL_THRESH_HEAD);
 
  set_register(0x5A, ELE1_T, TOU_THRESH_NOSE);
  set_register(0x5A, ELE1_R, REL_THRESH_NOSE);
  
  set_register(0x5A, ELE2_T, TOU_THRESH_LEFT);
  set_register(0x5A, ELE2_R, REL_THRESH_LEFT);
  
  set_register(0x5A, ELE3_T, TOU_THRESH_RIGHT);
  set_register(0x5A, ELE3_R, REL_THRESH_RIGHT);
  
  set_register(0x5A, ELE4_T, TOU_THRESH_FRONT);
  set_register(0x5A, ELE4_R, REL_THRESH_FRONT);
  
  set_register(0x5A, ELE5_T, TOU_THRESH_BACK);
  set_register(0x5A, ELE5_R, REL_THRESH_BACK);
  
  set_register(0x5A, ELE6_T, TOU_THRESH);
  set_register(0x5A, ELE6_R, REL_THRESH);
  
  set_register(0x5A, ELE7_T, TOU_THRESH);
  set_register(0x5A, ELE7_R, REL_THRESH);
  
  set_register(0x5A, ELE8_T, TOU_THRESH);
  set_register(0x5A, ELE8_R, REL_THRESH);
  
  set_register(0x5A, ELE9_T, TOU_THRESH);
  set_register(0x5A, ELE9_R, REL_THRESH);
  
  set_register(0x5A, ELE10_T, TOU_THRESH);
  set_register(0x5A, ELE10_R, REL_THRESH);
  
  set_register(0x5A, ELE11_T, TOU_THRESH);
  set_register(0x5A, ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(0x5A, FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(0x5A, ELE_CFG, 0x0C);  // Enables all 12 Electrodes
  
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*set_register(0x5A, ATO_CFG0, 0x0B);
  set_register(0x5A, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(0x5A, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  set_register(0x5A, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V
  
  set_register(0x5A, ELE_CFG, 0x0C);
  
}


boolean checkInterrupt(void){
  return digitalRead(irqpin);
}


void set_register(int address, unsigned char r, unsigned char v){
    Wire.beginTransmission(address);
    Wire.write(r);
    Wire.write(v);
    Wire.endTransmission();
}

void readTouchInputs(){
  if(!checkInterrupt()){
    
    //read the touch state from the MPR121
    Wire.requestFrom(0x5A,2); 
    
    byte LSB = Wire.read();
    byte MSB = Wire.read();
    
    uint16_t touched = ((MSB << 8) | LSB); //16bits that make up the touch states

    
    for (int i=0; i < 12; i++){  // Check what electrodes were pressed
      if(touched & (1<<i)){
      
        if(touchStates[i] == 0){
          //pin i was just touched
          Serial.print("pin ");
          Serial.print(i);
          Serial.println(" was just touched");
         if((i == ANGRY_PIN) || (blueToothVal == 'a')){
        sens_angry();   
    }
    
//Disgust    
    else if((i == DISGUST_PIN) || (blueToothVal == 'd')){
        sens_disgust();
    }
 
//Happy
     else if((i == HAPPY_PIN)  || (blueToothVal == 'h')){
        sens_happy();
    }
//Surprise and Fear
       else if((i == FEAR_PIN)|| (blueToothVal == 'f')){
        sens_fear();
    }
//Sad
       else if((i == SAD_PIN)|| (blueToothVal == 's')){
        sens_sad();
    }
      else if ((i == SURPRISE_PIN)){
        sens_happy();
      }
          
        
        }else if(touchStates[i] == 1){
          //pin i is still being touched
        }  
      
        touchStates[i] = 1;      
      }else{
        if(touchStates[i] == 1){
          Serial.print("pin ");
          Serial.print(i);
          Serial.println(" is no longer being touched");
          
          
          //pin i is no longer being touched
       }
        
        touchStates[i] = 0;
      }
    
    }
    
  }
}

