// #include "Arduino.h"
// extern "C" {
//   #include "PeakDetection.h"
// }
// //ADC Averaging Variables
// #define NUM_SAMPLES 10
// int ADC_Value;
// int ADC_Average;
// int BUFFER;
// int BUFF_PTR;

// //Peak Detector Object
// PeakDetection peakDetection;
// int ADC_Val;
// int i= 0;

// //struct to store Peak Data
// typedef struct{
//   int Max_Value;
//   int Min_Value;
//   unsigned long timestamp;
// } Datapoint;

// Datapoint Peaks[100];

// int peak_status;

// void setup() {
//   Serial.begin(9600);

//   //Peak Detector Configuration
//   //Max Peak Config
//   // peakDetection.begin(4, 2, 0.6);

//   //Min Peak Config
//   peakDetection.begin(3, 2, 0.7);
// }

// void loop() {
//     // ADC_Average = BUFFER/NUM_SAMPLES;
//     ADC_Average =getADC();

//     //Add Current Pressure Reading to Peak Detector Window
//     peakDetection.add(ADC_Average);

//     //State of Current Data Point
//     // int peak = peakDetection.getPeak();

//     //What to Do after peak is Detected
//     if(peakDetection.getPeak() == 1)
//     {
//       Datapoint peak;
//       peak.Max_Value = ADC_Average;
//       while(peakDetection.getPeak() < 0)
//       {
//         ADC_Val = getADC();
//         peakDetection.add(ADC_Val);
//       }
//       peak.Min_Value = ADC_Val;
//       peak.timestamp = millis();
//       Peaks[i] = peak;
//       i++;
//     }
//     else
//     {
//       // Serial.println(0);
//       Serial.println(getADC());
//     }
//     //Delay For Stability
//     delay(5);
// }

// int getADC() {
//     int Pressure;
//     BUFFER = 0;
//     BUFF_PTR = 0;

//     while (BUFF_PTR < NUM_SAMPLES) {
//         ADC_Value = analogRead(A0);
//         BUFFER += ADC_Value;
//         BUFF_PTR++;
//         delay(1); // Small delay between readings
//     }

//     ADC_Average = BUFFER / NUM_SAMPLES;

//     return ADC_Average;
// }

// int ADCtoPressure(int ADC_Val){
//     int Pressure;
//     // Pressure Sensor Calibration Curve
//     if (ADC_Val <= 29) {
//         Pressure = (1.176470588f * ADC_Val) - 14.11764706f;
//     } else {
//         Pressure = (0.92353996f * ADC_Val) - 7.345898933f;
//     }
//     return Pressure;
// }

// void CalculateBP(Datapoint* Peaks){
//   for(i=0;i<num_peaks;i++){
    
//   }
// }
