//-- Otto Makey V0
//Derived from OttoHumanoid V10 author unknown
//Alex Just-Alex 2023

//Unlike Otto Humanoid this uses the deafult Rx and Tx for bluetooth communication so... 
// BLUETOOTH MODULE MUST BE DISCONNECTED WHEN UPLOADING CODE!

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "OttoMakey.h"
OttoMakey Otto;   //This is Otto!
//----------------------------------------------------------------------


///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////
int T=1000;              //Initial duration of movement
int moveId=0;            //Number of movement
int moveSize=15;         //Asociated with the height of some movements
String serialCmd = "";
char cmdType;
int arg1 = 0;
int arg2 = 0;
int arg3 = 0;

#define PIN_LL 2 // left leg, servo[0]
#define PIN_RL 3 // right leg, servo[1]
#define PIN_LF 4 // left foot, servo[2]
#define PIN_RF 5 // right foot, servo[3]
#define PIN_LA 6 // Left arm, servo[4]
#define PIN_RA 7 // Right arm, servo[5]
#define PIN_HD 8 // Head /servo[6]
#define PIN_LED_rl 9  //Left red LED
#define PIN_LED_rr 10 //right red LED
#define PIN_LED_g 11 //green LEDs
#define PIN_LED_b 12 //blue LEDS
#define PIN_Buzzer  13 //buzzer

void setup() {
  Serial.println("setup");
  Otto.initMakey(PIN_LL, PIN_RL, PIN_LF, PIN_RF, PIN_LA, PIN_RA, PIN_HD, false, PIN_Buzzer);
  Otto.initMAKEY_LEDs(PIN_LED_rl, PIN_LED_rr, PIN_LED_g, PIN_LED_b);
  Otto.setEye(PIN_LED_rl, 10);
  Serial.begin(9600); // Default communication rate of the Bluetooth module  
 
int homes[7]={90, 90, 90, 90, 140, 30, 90}; //All the servos at rest position
Otto._moveServos(500,homes);   //Move the servos in half a second
Otto.setEye(PIN_LED_rr, 10);
Otto.sing(S_connection);
for(int i =0;i<6;i++)
{
  Otto.setEye(PIN_LED_g, i);
  delay(50);
}
Otto.setEye(PIN_LED_rl, 0);
Otto.setEye(PIN_LED_rr, 0);
Otto.sing(S_happy);
}

void loop() {
    if(Serial.available() > 0){ // Checks whether data is comming from the serial port
      serialCmd = Serial.readString();//.read(); // Reads the data from the serial port
      getArguments(serialCmd);
      
      switch(cmdType) {
        case 'S':
          receiveStop();
          break;
        case 'M':
          receiveMovement();
          break;
        case 'H':
          receiveGesture();
          break;
        case 'K':
          receiveSing();
          break;
        case 'E':
          Serial.println("eyes");
          if (arg1 != 0 && arg2 != 0) {Otto.setEye(arg1, arg2);}
          break;
        case 'X':
          Serial.println("TEST");
          Otto.servo[arg1].SetPosition(arg2);
          break;
        default:
          Otto.whiteEyes();
          Serial.print("unknown command: ");
          Serial.println(cmdType);
          receiveStop();  
          break;
        }
    } 
    else //nothing in serial buffer
    {
      delay(50);
    }
    if (Otto.getRestState()==false){  
      move(moveId);
    }  

} //end of loop

void getArguments(String commandStr)
{
      int lastChar = commandStr.length() - 1;

      // Split the commandStr by a pre-defined delimiter 
      int delimiter, delimiter_1, delimiter_2, delimiter_3;

      delimiter = commandStr.indexOf(" ");
      if (delimiter == -1) delimiter_1 = -1;
      else delimiter_1 = commandStr.indexOf(" ", delimiter + 1);
      if (delimiter_1 == -1)
      {
        delimiter_1 = lastChar;
        delimiter_2 = -1;
      }
      else delimiter_2 = commandStr.indexOf(" ", delimiter_1 +1);
      if (delimiter_2 == -1)
      {
        delimiter_2 = lastChar;
        delimiter_3 = lastChar;
      }
      else delimiter_3 = commandStr.indexOf(" ", delimiter_2 +1);
      if (delimiter_3 == -1) delimiter_3 = lastChar;

      cmdType = commandStr[0];//.substring(0, delimiter); 
      String arg1s = "";
      if (delimiter_1 > delimiter) arg1s = commandStr.substring(delimiter + 1, delimiter_1);
      String arg2s = "";
      if (delimiter_2 > delimiter_1) arg2s = commandStr.substring(delimiter_1 + 1, delimiter_2);
      String arg3s =  "";
      if (delimiter_3 > delimiter_2) arg3s = commandStr.substring(delimiter_2 + 1, delimiter_3);

    char argc1[arg1s.length()+1];
    arg1s.toCharArray(argc1,arg1s.length()+1);
    if (argc1 != NULL && arg1s != "") {arg1=atoi(argc1);}
    else arg1 = 0;
    char argc2[arg2s.length()+1];
    arg2s.toCharArray(argc2,arg2s.length()+1);
    if (argc2 != NULL && arg2s != "") {arg2=atoi(argc2);}
    else arg2 = 0;
    char argc3[arg3s.length()+1];
    arg3s.toCharArray(argc3,arg3s.length()+1);
    if (argc3 != NULL && arg3s != "") {arg3=atoi(argc3);}
    else arg3 = 0;

}

void receiveStop(){
    moveId = 0;
    sendAck();
    Otto.home();
    sendFinalAck();
}

//-- Function to receive movement commands
void receiveMovement(){

    sendAck();

    if (Otto.getRestState()==true){
        Otto.setRestState(false);
    }
    //Definition of Movement Bluetooth commands
    //M  MoveID  T   MoveSize  
    moveId=arg1;
    T = arg2;
    if (T==0)  T=1000;
    moveSize=arg3;
    if (moveSize==0) moveSize =15;
}



//-- Function to execute the right movement according to the movement command received.
void move(int moveId){

  bool manualMode = false;

  switch (moveId) {
    case 0:
      Otto.home();
      break;
    case 1: //M 1 1000 
      Otto.walk(1,T,1);
      break;
    case 2: //M 2 1000 
      Otto.walk(1,T,-1);
      break;
    case 3: //M 3 1000 
      Otto.turn(1,T,1);
      break;
    case 4: //M 4 1000 
      Otto.turn(1,T,-1);
      break;
    case 5: //M 5 1000 30 
      Otto.updown(1,T,moveSize);
      break;
    case 6: //M 6 1000 30
      Otto.moonwalker(1,T,moveSize,1);
      break;
    case 7: //M 7 1000 30
      Otto.moonwalker(1,T,moveSize,-1);
      break;
    case 8: //M 8 1000 30
      Otto.swing(1,T,moveSize);
      break;
    case 9: //M 9 1000 30 
      Otto.crusaito(1,T,moveSize,1);
      break;
    case 10: //M 10 1000 30 
      Otto.crusaito(1,T,moveSize,-1);
      break;
    case 11: //M 11 1000 
      Otto.jump(1,T);
      break;
    case 12: //M 12 1000 30 
      Otto.flapping(1,T,moveSize,1);
      break;
    case 13: //M 13 1000 30
      Otto.flapping(1,T,moveSize,-1);
      break;
    case 14: //M 14 1000 20
      Otto.tiptoeSwing(1,T,moveSize);
      break;
    case 15: //M 15 500 
      Otto.bend(1,T,1);
      break;
    case 16: //M 16 500 
      Otto.bend(1,T,-1);
      break;
    case 17: //M 17 500 
      Otto.shakeLeg(1,T,1);
      break;
    case 18: //M 18 500 
      Otto.shakeLeg(1,T,-1);
      break;
    case 19: //M 19 500 20
      Otto.jitter(1,T,moveSize);
      break;
    case 20: //M 20 500 15
      Otto.ascendingTurn(1,T,moveSize);
      break;
     case 21: //M 21
      Otto.armsup();
      break;
    case 22: //M 22 right arm
      Otto.armwave(1);
      break;
    case 23: //M 23 left arm
      Otto.armwave(-1);
      break;
    case 24: //M 24
      Otto.armsdown();
      break;
    default:
        manualMode = true;
      break;
  }

  if(!manualMode){
    sendFinalAck();
  }  

}// end of move function


//-- Function to receive gesture commands
void receiveGesture(){

    //sendAck & stop if necessary
    sendAck();
    Otto.home(); 

    //Definition of Gesture Bluetooth commands
    //H  GestureID  
    int gesture = 0;
    gesture=arg1;
    if (gesture == 0) delay(2000);

    switch (gesture) {
      case 1: //H 1 
        Otto.playGesture(OttoHappy);
        break;
      case 2: //H 2 
        Otto.playGesture(OttoSuperHappy);
        break;
      case 3: //H 3 
        Otto.playGesture(OttoSad);
        break;
      case 4: //H 4 
        Otto.playGesture(OttoSleeping);
        break;
      case 5: //H 5  
        Otto.playGesture(OttoFart);
        break;
      case 6: //H 6 
        Otto.playGesture(OttoConfused);
        break;
      case 7: //H 7 
        Otto.playGesture(OttoLove);
        break;
      case 8: //H 8 
        Otto.playGesture(OttoAngry);
        break;
      case 9: //H 9  
        Otto.playGesture(OttoFretful);
        break;
      case 10: //H 10
        Otto.playGesture(OttoMagic);
        break;  
      case 11: //H 11
        Otto.playGesture(OttoWave);
        break;   
      case 12: //H 12
        Otto.playGesture(OttoVictory);
        break; 
      case 13: //H 13
        Otto.playGesture(OttoFail);
        break;         
      default:
        break;
    }

    sendFinalAck();
}

//-- Function to receive sing commands
void receiveSing(){

    //sendAck & stop if necessary
    sendAck();
    Otto.home(); 

    //Definition of Sing Bluetooth commands
    //K  SingID    
    int sing = 0;
    sing=arg1;
    if (sing == 0)  delay(2000);

    switch (sing) {
      case 1: //K 1 
        Otto.sing(S_connection);
        break;
      case 2: //K 2 
        Otto.sing(S_disconnection);
        break;
      case 3: //K 3 
        Otto.sing(S_surprise);
        break;
      case 4: //K 4 
        Otto.sing(S_OhOoh);
        break;
      case 5: //K 5  
        Otto.sing(S_OhOoh2);
        break;
      case 6: //K 6 
        Otto.sing(S_cuddly);
        break;
      case 7: //K 7 
        Otto.sing(S_sleeping);
        break;
      case 8: //K 8 
        Otto.sing(S_happy);
        break;
      case 9: //K 9  
        Otto.sing(S_superHappy);
        break;
      case 10: //K 10
        Otto.sing(S_happy_short);
        break;  
      case 11: //K 11
        Otto.sing(S_sad);
        break;   
      case 12: //K 12
        Otto.sing(S_confused);
        break; 
      case 13: //K 13
        Otto.sing(S_fart1);
        break;
      case 14: //K 14
        Otto.sing(S_fart2);
        break;
      case 15: //K 15
        Otto.sing(S_fart3);
        break;    
      case 16: //K 16
        Otto.sing(S_mode1);
        break; 
      case 17: //K 17
        Otto.sing(S_mode2);
        break; 
      case 18: //K 18
        Otto.sing(S_mode3);
        break;   
      case 19: //K 19
        Otto.sing(S_buttonPushed);
        break;                      
      default:
        break;
    }
    sendFinalAck();

}




//-- Function to send Ack comand (A)
void sendAck(){

  delay(30);

  Serial.print(F("&&"));
  Serial.print(F("A"));
  Serial.println(F("%%"));
  Serial.flush();
}

//-- Function to send final Ack comand (F)
void sendFinalAck(){

  delay(30);

  Serial.print(F("&&"));
  Serial.print(F("F"));
  Serial.println(F("%%"));
  Serial.flush();
}
