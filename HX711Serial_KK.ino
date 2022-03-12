
#include <SoftwareSerial.h>
SoftwareSerial toESP(7,8); //Rx Tx
#include "HX711.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        2 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 32 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 64 // Time (in milliseconds) to pause between pixels
// HX711.DOUT	- pin #A1
// HX711.PD_SCK	- pin #A0

int Buzzle1 = 10;

HX711 scale(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library

void setup() {
  
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(38400);
  Serial.println("HX711 Demo");

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided 
						// by the SCALE parameter (not set yet)  

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
						// by the SCALE parameter set with set_scale

  Serial.println("Readings:");
   pinMode(Buzzle1, OUTPUT); // กำหนดขาทำหน้าที่ให้ขา 2 เป็น OUTPUT
  digitalWrite(Buzzle1, LOW);
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units()*-1, 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10)*-1, 1);

  if (scale.get_units(10)*-1 >= 0.1) {
     pixels.clear(); // Set all pixel colors to 'off'
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.
    digitalWrite(Buzzle1, LOW);
    delay(DELAYVAL); // Pause before next pass through loop
    
  // Danger! Shut down the system.
}
  // Danger! Shut down the system.
}

else { // temperature < 60
   pixels.clear(); // Set all pixel colors to 'off'
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(150,0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.
    digitalWrite(Buzzle1, HIGH);
    delay(DELAYVAL); // Pause before next pass through loop
   
  // Danger! Shut down the system.
}
  // Safe! Continue usual tasks.
}
  
   


  scale.power_down();			        // put the ADC in sleep mode
  delay(20);
  scale.power_up();

  
}
