//Otto Makey V0
//Derived from OttoHumanoid V10 author unknown
//Alex Just-Alex 2023


#ifndef OttoMakey_h
#define OttoMakey_h

#ifdef ARDUINO_ARCH_ESP32
#include <ESP32Servo.h>
#else
#include <Servo.h>
#endif
#include <Oscillator.h>
#include <EEPROM.h>

#include "Otto_sounds.h"
#include "Otto_gestures.h"

//-- Constants
#define FORWARD     1
#define BACKWARD    -1
#define LEFT        1
#define RIGHT       -1
#define SMALL       5
#define MEDIUM      15
#define BIG         30
#define RED_L    0
#define RED_R    1
#define BLUE     2
#define GREEN    3

class OttoMakey
{
  public:

    //-- Otto initialization
    void initMakey(int LL, int RL, int LF, int RF,int LA, int RA, int HD, bool load_calibration, int Buzzer);
    void initMAKEY_LEDs(int LED_rl, int LED_rr,int LED_g,int LED_b);
    //-- Attach & detach functions
    void attachServos();
    void detachServos();

    //-- Oscillator Trims
    void setTrims(int LL, int RL, int LF, int RF,int LA, int RA, int HD);
    void saveTrimsOnEEPROM();

    //-- LED eyes
    void OttoMakey::setEye(int eye, int intensity);
    void OttoMakey::restoreEyes();
    void OttoMakey::redLeftEye();
    void OttoMakey::redRighEye();
    void OttoMakey::redEyes();
    void OttoMakey::greenEyes();
    void OttoMakey::blueEyes();
    void OttoMakey::purpleEyes();
    void OttoMakey::orangeEyes();
    void OttoMakey::turqEyes();
    void OttoMakey::whiteEyes();
    void OttoMakey::noEyes();

    //-- Predetermined Motion Functions
    void _moveServos(int time, int  servo_target[]);
    void oscillateServos(int A[7], int O[7], int T, double phase_diff[7], float cycle);

    //-- HOME = Otto at rest position
    void home();
    bool getRestState();
    void setRestState(bool state);
    
    //-- Predetermined Motion Functions
    void jump(float steps=1, int T = 2000);

    void walk(float steps=4, int T=1000, int dir = FORWARD);
    void turn(float steps=4, int T=2000, int dir = LEFT);
    void bend (int steps=1, int T=1400, int dir=LEFT);
    void shakeLeg (int steps=1, int T = 2000, int dir=RIGHT);

    void updown(float steps=1, int T=1000, int h = 20);
    void swing(float steps=1, int T=1000, int h=20);
    void tiptoeSwing(float steps=1, int T=900, int h=20);
    void jitter(float steps=1, int T=500, int h=20);
    void ascendingTurn(float steps=1, int T=900, int h=20);

    void moonwalker(float steps=1, int T=900, int h=20, int dir=LEFT);
    void crusaito(float steps=1, int T=900, int h=20, int dir=FORWARD);
    void flapping(float steps=1, int T=1000, int h=20, int dir=FORWARD);
    void armsup();
    void armsdown();
    void armwave(int dir =RIGHT);

    //-- Sounds
    void _tone (float noteFrequency, long noteDuration, int silentDuration);
    void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
    void sing(int songName);
    
    
    //-- Gestures
    void playGesture(int gesture);
    Oscillator servo[7];

  private:
   
    int servo_pins[7];
    int servo_trim[7];
    int servo_position[7];
    int set_A[7];
    int set_O[7];
    double set_phase_diff[7];

    int pinBuzzer;
    int pinLEDrl;
    int pinLEDrr;
    int pinLEDg;
    int pinLEDb;    
    int redLeftIntensity;
    int redRightIntensity;
    int greenIntensity;
    int blueIntensity;

    unsigned long final_time;
    unsigned long partial_time;
    float increment[7];

    bool isOttoResting;

    void _execute(int A[7], int O[7], int T, double phase_diff[7], float steps);

};

#endif