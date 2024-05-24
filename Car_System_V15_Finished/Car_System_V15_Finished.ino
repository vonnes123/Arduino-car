#include "DHT11.h"

//declaring all the parts from the arduino
const int LED_RED = 4;
const int LED_GREEN = 5;
const int LED_BLUE = 6;
const int LED_YELLOW = 7;
const int RIGHT_BUTTON = 8;
const int LEFT_BUTTON = 9;
const int POTPIN = 14;
const int LDR_IN = 16;

//seting up the light treshold for the headlights
const int LIGHT_THRESHOLD = 400;

//seting up the states of the buttons
int lastLeftButtonState;
int leftButtonState;
int lastRightButtonState;
int rightButtonState;
const int DEBOUNCE_DELAY = 50;
int lastLeftFlickerableState = LOW;
unsigned long lastLeftDebounceTime = 0;
int lastRightFlickerableState = LOW;
unsigned long lastRightDebounceTime = 0;

//seting up the variables for the two blinking lights
int blueLedState = LOW;
int greenLedState = LOW;
int redLedState = LOW;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
const long interval = 400;
bool blinkBlue = false;
bool blinkGreen = false;

//seting up the potentiometer
int poteAngle;

//seting up booleans for directions of movement
bool goingToTheLeft = false;
bool goingToTheRight = false;

//setting up the timer for the temperature
const long temperatureInterval = 5000;
unsigned long previousMillisTemperature = 0;

//seting up the 2 modes of operation
char modeRead = 'N';
int mode = 1;
int changeModeCount = 1;

//seting up the headlights
bool lastHeadlightState = false;
bool headlightState;
unsigned long previousMillisLight = 0;
int lastBrightness;

//seting up the movements of the car system
bool lastMovement = false;
bool movement;
bool extremeLeftTurn = false;
bool extremeRightTurn = false;

void setup() {
  //initializing the components
  Serial.begin(9600);
  pinMode(LED_RED, INPUT_PULLUP);
  pinMode(LED_GREEN, INPUT_PULLUP);
  pinMode(LED_BLUE, INPUT_PULLUP);
  pinMode(LED_YELLOW, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(LDR_IN, INPUT);

  //now this is not part of the assignment but I had a problem with the arduino where all the lights turn on when I start it so i turn them off in the setup
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_YELLOW, LOW);
}

void leftButton() {
  //reference for the debouncing button: https://arduinogetstarted.com/tutorials/arduino-button-debounce
  //we use the left button for turning On and Off the left light
  leftButtonState = digitalRead(LEFT_BUTTON);

  if (leftButtonState != lastLeftFlickerableState) {
    //we reset the debounce timer
    lastLeftDebounceTime = millis();
    //we save the the last flickerable state
    lastLeftFlickerableState = leftButtonState;
  }
  //we check for debouncing
  if ((millis() - lastLeftDebounceTime) > DEBOUNCE_DELAY) {
    //we check if the left button was pressed
    if (lastLeftButtonState == HIGH && leftButtonState == LOW) {
      if (blinkBlue == true)
      {
        //left light is OFF
        Serial.println((String)"L" + "Left light turned Off");
        blinkBlue = false;
        digitalWrite(LED_BLUE, LOW);
      } else {
        //left light is ON
        Serial.println((String)"L" + "Left light is On");
        blinkBlue = true;
        blinkGreen = false;
        digitalWrite(LED_GREEN, LOW);
      }
    }
    lastLeftButtonState = leftButtonState;
  }
}

void rightButton() {
  //reference for the debouncing button: https://arduinogetstarted.com/tutorials/arduino-button-debounce
  //we use the right button to turn On and Off the right light
  rightButtonState = digitalRead(RIGHT_BUTTON);

  if (rightButtonState != lastRightFlickerableState) {
    //we reset the debouncing timer
    lastRightDebounceTime = millis();
    //we save the the last flickerable state
    lastRightFlickerableState = rightButtonState;
  }
  //we check for debouncing
  if ((millis() - lastRightDebounceTime) > DEBOUNCE_DELAY) {
    //we check if the right button was pressed
    if (lastRightButtonState == HIGH && rightButtonState == LOW) {
      if (blinkGreen == true)
      {
        //the right light is Off
        Serial.println((String)"L" + "Right light turned Off");
        blinkGreen = false;
        digitalWrite(LED_GREEN, LOW);
      } else {
        //the right light is On
        Serial.println((String)"L" + "Right light is On");
        blinkGreen = true;
        blinkBlue = false;
        digitalWrite(LED_BLUE, LOW);
      }
    }
    lastRightButtonState = rightButtonState;
  }
}

int poteValue() {
  //we get values from the potentiometer for the steering wheel
  int poteValue = analogRead(POTPIN);
  int number;
  number = map(poteValue, 0, 1000, 1, 140);
  return number;
}

float temperature () {
  //we get the temprature and we print it every 5 seconds
  unsigned long currentMillisTemperature = millis();

  if (currentMillisTemperature - previousMillisTemperature >= temperatureInterval) {
    previousMillisTemperature = currentMillisTemperature;
    float temperature = DHT11.getTemperature();
    Serial.println((String)"T" + temperature);
  }
}

void headlights() {
  //we check if it is dark enough for the headlights
  int brightness = analogRead(LDR_IN);
  unsigned long currentMillis = millis();
  if (brightness < LIGHT_THRESHOLD) {
    if (currentMillis - previousMillisLight >= 1000) {
      previousMillisLight = currentMillis;
      if (brightness < LIGHT_THRESHOLD) {
        //headlights are On
        lastHeadlightState = headlightState;
        headlightState = true;
        digitalWrite(LED_YELLOW, HIGH);
        if (lastHeadlightState != headlightState) {
          //we print that the headlights are on
          Serial.println((String)"H" + "ON");
        }
      }
    }
  }
  else {
    //we check if the headlights need to be turned Off
    if (currentMillis - previousMillisLight >= 1000) {
      previousMillisLight = currentMillis;
      if (brightness >= LIGHT_THRESHOLD) {
        //we turn off the headlights
        digitalWrite(LED_YELLOW, LOW);
        lastHeadlightState = headlightState;
        headlightState = false;
        if (lastHeadlightState != headlightState) {
          //we print that the headlights are off
          Serial.println((String)"H" + "OFF");
        }
      }
    }
  }
}
void exitAlarmMode() {
  //we turn off all the lights after exiting alarm mode so none of them get stuck turned On
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
}
void printLeftOrRight() {
  //we check if we are moving to the left or the right
  if (poteAngle < 61) {
    lastMovement = movement;
    movement = true;
    if (lastMovement != movement) {
      //we print that we are moving to the left
      Serial.println((String)"M" + "Left");
    }
  } else if (poteAngle > 80) {
    lastMovement = movement;
    movement = false;
    if (lastMovement != movement) {
      //we print that we are moving to the right
      Serial.println((String)"M" + "Right");
    }
  }
}
void loop() {
  //we call all our methods
  leftButton();
  rightButton();
  poteValue();
  temperature();
  headlights();

  poteAngle = poteValue();
  printLeftOrRight();

  //we check in what moe we are right now
  modeRead = Serial.read();
  if (modeRead == 'N') {
    //we are in normal mode
    mode = 1;
    if (changeModeCount == 2) {
      exitAlarmMode();
    }
  } else if (modeRead == 'H') {
    //we are in hazardous mode
    mode = 2;
  }
  //we check if we are going straight
  if (poteAngle > 60 && poteAngle < 81) {
    extremeRightTurn = false;
    extremeLeftTurn = false;
  }
  if (mode == 1) {
    //we enter normal mode
    if (blinkBlue == true)
    {
      //we check if the blue light is blinking
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if (blueLedState == LOW) {
          blueLedState = HIGH;
        } else {
          blueLedState = LOW;
        }
        digitalWrite(LED_BLUE, blueLedState);
      }
    }
    if (blinkGreen == true)
    {
      //we check if the green light is blinking
      unsigned long currentMillis2 = millis();
      if (currentMillis2 - previousMillis2 >= interval) {
        previousMillis2 = currentMillis2;
        if (greenLedState == LOW) {
          greenLedState = HIGH;
        } else {
          greenLedState = LOW;
        }
        digitalWrite(LED_GREEN, greenLedState);
      }
    }
    if (poteAngle < 61) {
      //we check if we are going to the left
      goingToTheLeft = true;
      extremeRightTurn = false;
    }
    if (goingToTheLeft == true)
    {
      if (poteAngle > 60 && poteAngle <= 90)
      {
        //we check if are going straight after we went left
        extremeRightTurn = false;
        blinkBlue = false;
        goingToTheLeft = false;
        digitalWrite(LED_BLUE, LOW);
      }
    }
    if (blinkBlue == true && poteAngle > 90 && extremeRightTurn == false)
    {
      //we check if we went too much to the right with our left light on and if we did that the left light is turned off
      blinkBlue = false;
      digitalWrite(LED_BLUE, LOW);
      extremeRightTurn = true;
    }
    else if (blinkBlue == true && poteAngle > 90 && extremeRightTurn == true) {
      //we can start our lights once again if we now need to go to the left
      if (poteAngle > 60 && poteAngle <= 90)
      {
        extremeRightTurn = false;
        blinkBlue = false;
        goingToTheLeft = false;
        digitalWrite(LED_BLUE, LOW);
      }
    }
    if (poteAngle > 80) {
      //we check if we are going to the right
      goingToTheRight = true;
      extremeLeftTurn = false;
    }
    if (goingToTheRight == true) {
      //we check if are going straight after we went right
      if (poteAngle < 81 && poteAngle >= 50) {
        blinkGreen = false;
        goingToTheRight = false;
        digitalWrite(LED_GREEN, LOW);
        extremeLeftTurn = false;
      }
    }
    if (blinkGreen == true && poteAngle < 50 && extremeLeftTurn == false) {
      //we check if we went too much to the left with our right light on and if we did that the right light is turned off
      blinkGreen = false;
      digitalWrite(LED_GREEN, LOW);
      extremeLeftTurn = true;
    } else if (blinkGreen == true && poteAngle < 50 && extremeLeftTurn == true)
    {
      //we can start our lights once again if we now need to go to the left
      if (poteAngle < 81 && poteAngle >= 50) {
        blinkGreen = false;
        goingToTheRight = false;
        digitalWrite(LED_GREEN, LOW);
        extremeLeftTurn = false;
      }
    }
  } else if (mode == 2)
  {
    //we enter hazardous mode and the left,right and red light blink
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (blueLedState == LOW && greenLedState == LOW && redLedState == LOW) {
        blueLedState = HIGH;
        greenLedState = HIGH;
        redLedState = HIGH;
      } else {
        blueLedState = LOW;
        greenLedState = LOW;
        redLedState = LOW;
      }
      digitalWrite(LED_BLUE, blueLedState);
      digitalWrite(LED_GREEN, greenLedState);
      digitalWrite(LED_RED, redLedState);
      changeModeCount = 2;
    }
  }
}
