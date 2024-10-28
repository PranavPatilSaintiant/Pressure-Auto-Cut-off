#include <Arduino.h>
#line 1 "C:\\User\\Pressure Sensor\\AutoCutoff\\AutoCutoff.ino"
extern "C" {
  #include "PeakDetection.h"
}
//ADC Averaging Variables
#define NUM_SAMPLES 40
unsigned int ADC_Value;
unsigned int ADC_Average;
unsigned int BUFFER;
unsigned int BUFF_PTR;

//Variables to store Peak TImings
unsigned long p_last=0;

//Auto Cut-off
uint8_t stop_press = 0;

//MOTOR and VALVE
#define MOTOR_PIN 7 // Blue Wire
#define VALVE_PIN 8 // Green Wire

//Peak Detector Object
PeakDetection peakDetection;

int peak_status;

#line 26 "C:\\User\\Pressure Sensor\\AutoCutoff\\AutoCutoff.ino"
void setup();
#line 44 "C:\\User\\Pressure Sensor\\AutoCutoff\\AutoCutoff.ino"
void loop();
#line 102 "C:\\User\\Pressure Sensor\\AutoCutoff\\AutoCutoff.ino"
int getADC();
#line 117 "C:\\User\\Pressure Sensor\\AutoCutoff\\AutoCutoff.ino"
int ADCtoPressure(int ADC_Val);
#line 26 "C:\\User\\Pressure Sensor\\AutoCutoff\\AutoCutoff.ino"
void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  pinMode(MOTOR_PIN,OUTPUT);
  digitalWrite(MOTOR_PIN,LOW);
  pinMode(VALVE_PIN,OUTPUT);
  digitalWrite(VALVE_PIN,HIGH);

  //Peak Detector Configuration

  //Max Peak Config
  // peakDetection.begin(4, 2, 0.6);
  peakDetection.begin(6, 3, 0.6);

  //Min Peak Config
  // peakDetection.begin(8, 4, 0.8);
}

void loop() {



  
  digitalWrite(MOTOR_PIN,HIGH);
  while(getADC()<487){
    Serial.println(getADC());
  }
  p_last = millis();
  while(getADC()<850 && !stop_press)
  {
    // ADC_Average = BUFFER/NUM_SAMPLES;
    // ADC_Average = getADC();
    //Add Current Pressure Reading to Peak Detector Window
    peakDetection.add(getADC());

    //State of Current Data Point
    // int peak = peakDetection.getPeak();
    
    //What to Do after peak is Detected
    if(peakDetection.getPeak() == 1)
    { 
      int p_curr = millis();
      Serial.println(p_curr - p_last);
      if((p_curr - p_last)>1200)
      {
        stop_press = 1;
        Serial.println("Auto Cut-off at: ");
        Serial.print(ADCtoPressure(getADC()));
        digitalWrite(MOTOR_PIN,LOW);
        digitalWrite(VALVE_PIN,LOW);
        break;
      }
      p_last = p_curr;
      Serial.print("Peak ");
      // while(peakDetection.getPeak() > 0){
      //   Serial.println("Repeating");
      //   peakDetection.add(getADC());
      //   Serial.println(getADC());
      // }
    }
    else
    {
      // Serial.println(0);
      Serial.println(getADC());
    }
  }
  digitalWrite(MOTOR_PIN,LOW);
  digitalWrite(VALVE_PIN,LOW);





  while(1){}
}

int getADC() {
    int Pressure;
    BUFFER = 0;
    BUFF_PTR = 0;

    while (BUFF_PTR < NUM_SAMPLES) {
        ADC_Value = analogRead(A0);
        BUFFER += ADC_Value;
        BUFF_PTR++;
        delay(1); // Small delay between readings
    }
    ADC_Average = BUFFER / NUM_SAMPLES;
    return ADC_Average;
}

int ADCtoPressure(int ADC_Val){
    int Pressure;
    Pressure = 0.2206094242*(ADC_Val)-7.363253108;
    return Pressure;
}

