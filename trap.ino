/* Leprechaun Trap

  This script puts on a twinkling LED show while waiting for a momentary
  switch/button to be triggered and throw in interrupt. Then it reverses
  a servo angle and sets the LEDs on indefinitly.

  The circuit:
    * Momentary switch/button attached to pin 2 from +5V
    * Servo attached to pin 7
    * LEDs in series attached to pins 3, 5, and 6

  https://joao-s-martins.github.io/leprechaun-trap
  https://github.com/Joao-S-Martins/leprechaun-trap
  https://circuits.io/circuits/4252213-leprechaun-trap

  License:
  Creative Commons Attribution 4.0 International Public License (CC-BY 4.0)

*/
#include <Servo.h>  // library to handle servo functionality

const int triggerPin = 2; // the momentary switch is connected to pin 2 so that it can trigger interrupts
const int ledPinA = 3;    // the pin for moderatly paced LEDs
const int ledPinB = 5;    // the pin for slower paced LEDs
const int ledPinC = 6;    // the pin for faster paced LEDs
const int servoPin = 7;   // the servo pin

Servo servo;                  // the servo that controls the trap door
const int openAngle = 0;      // servo position when trap is open
const int closedAngle = 180;  // servo position when trap is closed
bool tripped = false;         // state of the trap; false when empty, true when there is a leprechaun inside

class Flasher
{
  // initialized when object is constructed
  int ledPin;   // the number of the LED pin
  long OnTime;  // milliseconds of on-time
  long OffTime; // milliseconds of off-time
 
  // current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis; // will store the last time the LED was updated
 
  /* Constructor
    Creates a Flasher and initializes the member variables and state
  */
  public:
  Flasher(int pin, long on, long off)
  {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);

    OnTime = on;
    OffTime = off;

    ledState = LOW;
    previousMillis = 0;
  }
  
  /* update
    Turns the LED on or off based on time passed
  */
  void update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();

    // if it's on and time to turn it off
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      off();  // turn it off
      previousMillis = currentMillis;  // remember the time
    }
    // if it's off and time to turn it on
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      on();  // turn it on
      previousMillis = currentMillis;   // remember the time
    }
  }

  /* on
  Turns the LED on.
  */
  void on()
  {
    ledState = HIGH;  // set state to on
    digitalWrite(ledPin, ledState);   // update the actual LED
  }

  /* off
  Turns the LED off.
  */
  void off()
  {
    ledState = LOW;  // set state to off
    digitalWrite(ledPin, ledState);   // update the actual LED
  }
};

Flasher blink1(ledPinA, 50, 400); // create the moderate blinker
Flasher blink2(ledPinB, 50, 500); // create the slower blinker
Flasher blink3(ledPinC, 50, 300); // create the faster blinker

void setup()
{
  pinMode(ledPinA, OUTPUT); // set initial LED pin mode
  pinMode(ledPinB, OUTPUT); // set initial LED pin mode
  pinMode(ledPinC, OUTPUT); // set initial LED pin mode
  servo.attach(servoPin);   // attached the servoPin for servo use
  pinMode(triggerPin, INPUT_PULLUP);  // set the pin for the trap trigger
  attachInterrupt(digitalPinToInterrupt(triggerPin), caught, CHANGE); // set the changing of the triggerPin to throw an interrupt and have that interrupt handled by the caught function.
}

void loop()
{
  // if the trap state shows it should contain a leprechaun
  if (tripped == true) {
    servo.write(closedAngle);
    blink1.on();
    blink2.on();
    blink3.on();
  } else {
    // waiting for a leprechaun
    servo.write(openAngle);
    blink1.update();
    blink2.update();
    blink3.update();
  }
}

/* caught
  Changes the state of this script by setting tripped to true
*/
void caught()
{
  tripped = true;
}
