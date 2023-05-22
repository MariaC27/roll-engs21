// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include "LSM6DS3.h"
#include "Wire.h"
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define PIN        5 // for LEDs

#define NUMPIXELS 12 

int buttonPin = 0; 
int pinBuzzer = 3; //onboard buzzer
int extBuzzer = 7;
// the onboard buzzer on the XIAO expansion board is A3 (set to 3)
// external grover buzzer plugged into A7 (set to 7)

int buttonState = 0;  
int startState = 0;

LSM6DS3 myIMU(I2C_MODE, 0x6A); 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 5000 // 5 seconds for 12 pixels = 1 minute for roller circle

void setup() {
  pixels.begin();
  // pinMode(extBuzzer, OUTPUT); //external buzzer
  pinMode(pinBuzzer, OUTPUT);// onboard buzzer
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  Serial.begin(9600);
  while (!Serial);
  if (myIMU.begin() != 0) {
      Serial.println("Device error");
  } else {
      Serial.println("Device OK!");
  }

  pinMode(buttonPin, INPUT); // initialize button as input - changed to INPUT_PULLUP for new button


}


void greenSequence(){
  // buzzer goes off when green sequence starts
  digitalWrite(extBuzzer, HIGH);
  delay(1000);
  digitalWrite(extBuzzer, LOW);
  delay(1000);
  // loop which turns on green pixels in sequence
  int i=0;
  while (/*buttonState == 0 &&  */ i<NUMPIXELS){ // while button is not pressed and pixels left
    Serial.println(i);

    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.show(); 
    i = i + 1;
    // check button state each time
    // buttonState = digitalRead(buttonPin);
    // Serial.print("green sequence button state: ");
    // Serial.println(buttonState); // if button state becomes 1, exists while and for loops
    delay(DELAYVAL); // Pause before next pass through loop
  }

  pixels.clear(); // after exiting while loop

  // logic to find out of string finished or not:
  // if (i == NUMPIXELS - 1) {
  //   return true; // reached the end
  // } else{
  //   return false;
  // }
  
}

void redSequence(){
  // Serial.print("red sequence button state: ");
  // Serial.println(buttonState);
  // buzzer goes off when red sequence starts
  digitalWrite(extBuzzer, HIGH);
  delay(1000);
  digitalWrite(extBuzzer, LOW);
  delay(1000);
  // loop that turns on all red pixels at once
  int i=0;
  while (buttonState == 0 && i<NUMPIXELS){ 
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    i = i + 1;
    // buttonState = digitalRead(buttonPin); // check button state
    // Serial.println(buttonState); 
  }
    
  delay(15000); // stays red for 15 seconds
  pixels.clear(); // Set all pixel colors to 'off'
}



void loop() {


  buttonState = digitalRead(buttonPin); // read state of on/off button to start
  Serial.print("Button state: ");
  Serial.println(buttonState);
  //Accelerometer and Gyro
  // Serial.print("\nAccelerometer:\n");
  // Serial.print(" X1 = ");
  // Serial.println(myIMU.readFloatAccelX(), 4);
  // Serial.print(" Y1 = ");
  // Serial.println(myIMU.readFloatAccelY(), 4);
  // Serial.print(" Z1 = ");
  // Serial.println(myIMU.readFloatAccelZ(), 4);
  // Serial.print("\nGyro:\n");
  // Serial.print(" X1 = ");
  // Serial.println(myIMU.readFloatGyroX(), 4);
  // Serial.print(" Y1 = ");
  // Serial.println(myIMU.readFloatGyroY(), 4);
  // Serial.print(" Z1 = ");
  // Serial.println(myIMU.readFloatGyroZ(), 4);
  // not rolling: gyro x and y are within abs 5 of zero
  // rolling: gyro x and y not within abs 5 of 0

  
  if (buttonState == 1){
    greenSequence();
    redSequence();
  }

  
  
 
}
