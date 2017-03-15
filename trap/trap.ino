/*
Adafruit Arduino - Lesson 3. RGB LED
*/
#include <Servo.h>

int triggerPin = 2;
int ledPinA = 3;
int ledPinB = 5;
int ledPinC = 6;
int servoPin = 7;

Servo servo;
int angle = 0;   // servo position in degrees
bool tripped = false;

class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPinA;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time
 
  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated
 
  // Constructor - creates a Flasher 
  // and initializes the member variables and state

  public:
  Flasher(int pin, long on, long off)
  {
    ledPinA = pin;
    pinMode(ledPinA, OUTPUT);     

    OnTime = on;
    OffTime = off;

    ledState = LOW; 
    previousMillis = 0;
  }
  
  void update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPinA, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPinA, ledState);   // Update the actual LED
    }
  }
};

Flasher blink1(ledPinA, 100, 400);
Flasher blink2(ledPinB, 150, 600);
Flasher blink3(ledPinC, 50, 300);

void setup()
{
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinC, OUTPUT);
  servo.attach(servoPin);
  pinMode(triggerPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(triggerPin), caught, CHANGE);
}

void loop()
{
  if (tripped == true) {
    servo.write(180);
  } else {
    servo.write(0);
  }
  if (tripped == true) {
    digitalWrite(ledPinA, HIGH);
    digitalWrite(ledPinB, HIGH);
    digitalWrite(ledPinC, HIGH);
  } else {
    blink1.update();
    blink2.update();
    blink3.update();
  }
}

void caught()
{
  tripped = true;
}

