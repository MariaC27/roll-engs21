
#define LED_1 13
#define LED_2 11
#define LED_3 9
#define LED_4 8

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup() { //runs once
  Serial.begin(9600);  
   if(!accel.begin())
   {
      Serial.println("ADXL345 sensor not detected.");
      while(1);
   }
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  delay(2000);
  analogWrite(LED_1, 255);
  delay(2000);
  analogWrite(LED_2, 255);
  delay(2000);
  analogWrite(LED_3, 255);
  delay(2000);
  analogWrite(LED_4, 255);

}

void loop() { //runs repeatedly
   sensors_event_t event; 
   accel.getEvent(&event);
   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
   Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
}
