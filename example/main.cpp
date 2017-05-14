#include "main.hpp"

// Outputs
const int pin_led = 13;


// Set up some StateMachine objects
// Pulse LED once for 200 ms immediately
Stimulus led(0, 200, digitalOn, digitalOff, pin_led);
// Wait 500 ms, then pulse LED 5 times for 50 ms each with 100 ms period
StimulusRepeating led_repeating(500, 50, digitalOn, digitalOff, pin_led, 100, 5);
// Take reading every 5 ms, 200 readings total, for 1 second of data
SensorRepeating sensor_repeat(0, takeReading, 5, 200);

// The setup routine runs once when you press reset or get reset from Serial port
void setup() {
  // Initialize the digital pin as an output.
  pinMode(pin_led, OUTPUT);
  // Default all output pins to LOW - for some reason they were floating high on the Due before I (Shane) added this
  digitalWrite(pin_led, LOW);

  Serial.begin(9600);
  
  led.start();
  led_repeating.start();

  sensor_repeat.start();

  }

// The loop routine runs over and over again forever
// In this loop we have our StateMachines check their states and update as necessary
// The StateMachines handle their own timing
// It's critical that this loop runs fast (< 1 ms period) so don't put anything in here that takes time to execute
void loop() {

      led.update();
      led_repeating.update();

      sensor_repeat.update();

      if (sensor_repeat.checkState()==sensor_repeat.OFF) { sendSensorData(); }

}

// These functions are called by the state machine objects
void digitalOn(int pin) {
    digitalWrite(pin, HIGH);
}

void digitalOff(int pin) {
    digitalWrite(pin, LOW);
}

// We call by reference so we can update the local variables in "reading_function" of StateMachine object
void takeReading(timems_t &time, int32_t &reading) {

    time = millis();
    // Here we just generate random data but we could instead read from an analog pin or a device connected through I2C or SPI
    reading = 5000-random(10000);  // for testing

}

void sendSensorData() {

    // You'll need to implement this yourself based on how you are interfacing with the Arduino
}
