
/*  

echo "# Take-a-Breath" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/rkqls818/Take-a-Breath.git
git push -u origin master
 
References
Pulse Sensor Amped 1.5    by Joel Murphy and Yury Gitman   http://www.pulsesensor.com

Using a Temp Sensor by lady ada https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor 

----------------------  Notes ----------------------  ----------------------
This code:
1) Blinks an LED to User's Live Heartbeat   PIN 13
2) Fades an LED to User's Live HeartBeat    PIN 5
3) Determines BPM
4) Prints All of the Above to Serial

Read Me:
https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md
 ----------------------       ----------------------  ----------------------
*/

#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
int stressed = 12;
int calm = 11;
int extreme =10;
int sensorPin = 1;

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// SET THE SERIAL OUTPUT TYPE TO YOUR NEEDS
// PROCESSING_VISUALIZER works with Pulse Sensor Processing Visualizer
//      https://github.com/WorldFamousElectronics/PulseSensor_Amped_Processing_Visualizer
// SERIAL_PLOTTER outputs sensor data for viewing with the Arduino Serial Plotter
//      run the Serial Plotter at 115200 baud: Tools/Serial Plotter or Command+L
static int outputType = SERIAL_PLOTTER;


void setup(){
  pinMode(stressed, OUTPUT);
  pinMode(extreme, OUTPUT);
  pinMode(calm, OUTPUT);
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE,
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);

}


//  Where the Magic Happens
void loop(){

while (millis() == 10000){
  int temperature = analogRead(sensorPin);

int reading = analogRead(sensorPin);
float voltage = reading * 5.0;
 voltage /= 1024.0; 

 float temperatureC = (voltage - 0.5) * 100;



if (180 < BPM or sensorPin > temperature + 10) {
   digitalWrite(stressed, HIGH);
   delay(200);
   digitalWrite(stressed, LOW);
   delay(200);
}

 
}

    serialOutput() ;

  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
        fadeRate = 255;         // Makes the LED Fade Effect Happen
                                // Set 'fadeRate' Variable to 255 to fade LED with pulse
        serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
        QS = false;                      // reset the Quantified Self flag for next time
  }

  ledFadeToBeat();                      // Makes the LED Fade Effect Happen
  delay(20);                             //  take a break

 if (175 < BPM){

    digitalWrite(extreme, HIGH);
    digitalWrite(calm,LOW);
  }
 if (175 > BPM) {
    digitalWrite(calm, HIGH);
    digitalWrite(extreme, LOW);
 }


if (185 < BPM) {
   digitalWrite(extreme, HIGH);
   delay(100);
   digitalWrite(extreme, LOW);
   delay(100);
   
}  
}



void ledFadeToBeat(){
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }
