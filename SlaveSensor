#include <CapacitiveSensor.h>
#include <Servo.h>
#define COM_PIN 3
#define ANGRY_T 100
#define SAD_T 200
#define FEAR_T 300
#define DISGUST_T 400
#define HAPPY_T 500

//Create Sensor objects
CapacitiveSensor   csNose = CapacitiveSensor(8,9);        //SendPin: 3, ReceivePin:2
CapacitiveSensor   csRL = CapacitiveSensor(12,13);
CapacitiveSensor   csBack = CapacitiveSensor(4,5);
CapacitiveSensor   csFront = CapacitiveSensor(6,7); 
CapacitiveSensor   csHead = CapacitiveSensor(10,11);

//Variables
int dy=15;
int sensitivity=80;
int act = 1;
int jan =1500;
unsigned long previousMillis = 0;
unsigned long interval = 10000;
bool blink = true;
bool rdy = true;

void setup()                    
{
  Serial.begin(115200);
//Setting up the sensors
  csNose.set_CS_AutocaL_Millis(0xFFFFFFFF); 
  csRL.set_CS_AutocaL_Millis(0xFFFFFFFF);
  csFront.set_CS_AutocaL_Millis(0xFFFFFFFF);
  csHead.set_CS_AutocaL_Millis(0xFFFFFFFF);
  csNose.set_CS_AutocaL_Millis(0xFFFFFFFF);
  csBack.set_CS_AutocaL_Millis(0xFFFFFFFF);

  //Setup port for comms
  pinMode(COM_PIN, OUTPUT);
   
}

void loop()                    
{

  unsigned long currentMillis = millis();

 
//Declare variables for sensor status  
    long status1 =  csNose.capacitiveSensor(30);
    long status2 =  csRL.capacitiveSensor(30);
    long status3 =  csFront.capacitiveSensor(30);
    long status4 =  csHead.capacitiveSensor(30);
    long status5 = csBack.capacitiveSensor(30);
    
//Shows the values of the sensors

    Serial.print("Nose: ");
    Serial.println(status1); 
    Serial.println("---------"); 
    Serial.print("RL: ");
    Serial.println(status2);
    Serial.println("---------");
    Serial.print("Front: ");
    Serial.println(status3);
    Serial.println("---------"); 
    Serial.print("Head: ");
    Serial.println(status4);
    Serial.println("---------");
    Serial.print("Back: ");
    Serial.println(status5);
    Serial.println("---------");



//Angry
    if(status1 > (sensitivity-30)){

        rdy = false;
        digitalWrite(COM_PIN, HIGH);
        delay(ANGRY_T);
        digitalWrite(COM_PIN, LOW);
        act = 1;      
    }
    
//Disgust    
    else if(status2 > (sensitivity)){
        rdy = false;
        digitalWrite(COM_PIN, HIGH);
        delay(DISGUST_T);
        digitalWrite(COM_PIN, LOW);
        act = 1;
    }
 
//Happy
     else if(status4 > sensitivity){
        rdy = false;
        digitalWrite(COM_PIN, HIGH);
        delay(HAPPY_T);
        digitalWrite(COM_PIN, LOW);
        act = 1;
    }
//Surprise and Fear
       else if(status3 > ((sensitivity))){
        rdy = false;
        digitalWrite(COM_PIN, HIGH);
        delay(FEAR_T);
        digitalWrite(COM_PIN, LOW);
        act = 1;

    }
//Sad
       else if(status5 > (sensitivity-30)){
        rdy = false;
        digitalWrite(COM_PIN, HIGH);
        delay(SAD_T);
        digitalWrite(COM_PIN, LOW);
        act = 1;
    }
    digitalWrite(COM_PIN, LOW);

    delay(200);                             
}
