/* we have now gone online! a whole new universe of button pushing potential!
    the adafruit.io service requires the adafruit.io library! Install it from the library manager!
    the library is configured from config.h
    we will also need all of the rest of the stuff we had in our two led sketch
    this is essentially a copy and paste kind of job!
*/

#include "config.h"

// set up the 'fancyLight' feed
AdafruitIO_Feed *fancyLight = io.feed("fancyLight");

//these global variables give names to pin numbers
const int led1 = A0;
const int led2 = A1;
const int button1 = A5;

//these constants will give names to the modes of the system
const int modeOff = 0;
const int modeLow = 1;
const int modeHigh = 2;
const int modeFlash = 3;

//this global variable will set the current mode
int lightMode = modeOff;

//this global variable will track time for flashing the leds
unsigned long flashTime;
unsigned long lastFlash;

//these varibles control the led state
int led1State = 0;  //bool is either true or fales (1 or 0)
int led2State = 0;

//these global variables will track what the last read of the switch was and the current state
int buttonReadPre = 0;
int buttonState;

//this global variable will mark when the button changes
unsigned long buttonTime;

void setup() {
  //open a serial connection for Debug output to serial monitor
  Serial.begin(115200);
  pinMode(led1, OUTPUT);

  //don't forget to declare the new led pin as an OUTPUT!
  pinMode(led2, OUTPUT);
  pinMode(button1, INPUT);
  digitalWrite(led1, led1State);

  //ADAFRUIT.IO CONNECTION STUFF
  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  
  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());


  // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  fancyLight->onMessage(handleMessage);

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.println(io.statusText());
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {

  //THIS IS REQUIRED TO MAKE THE ADAFRUIT.IO FEED FUNCTION WITH OUR SKETCH!!!
  io.run();

  int buttonRead = digitalRead(button1);
  delay(1);

  if (buttonRead != buttonReadPre) {
    buttonTime = millis(); //millis(); returns the time since the program started...
  }

  int debounceTime = millis() - buttonTime; //current time minus start time is elapsed time...

  if (debounceTime >= 50) {
    if (buttonRead != buttonState) {
      buttonState = buttonRead;
      if (buttonState == 1) {

        //changed this to iterate through modes
        lightMode += 1; //+= is an iterator that adds the right hand operator to the left and saves it

        //we need to make sure we don't set the light mode to more than 3...
        //if it is more than 3
        if (lightMode > 3) {

          //cycle it back to 0
          lightMode = 0;
        }
      }
    }
  }

  //if the lightMode is modeOff (0)...
  if (lightMode == modeOff) {

    //set both leds to off
    led1State = 0;
    led2State = 0;
  }

  //otherwise if it is modeLow (1)...
  else if (lightMode == modeLow) {

    //set the first led on and the second off
    led1State = 1;
    led2State = 0;
  }

  //otherwise if it is modeHigh (2)...
  else if (lightMode == modeHigh) {
    //set both leds on
    led1State = 1;
    led2State = 1;
  }

  //otherwise if it is modeFlash
  else if (lightMode == modeFlash) {

    //check to see if the flash time is higher than 100ms
    if (flashTime >= 100) {

      //and toggle the mode of both leds if it is
      led1State = !led1State;
      led2State = !led2State;
      //and reset the lastFlash time
      lastFlash = millis();
    }
  }

  //no matter what happens update the flashTime
  flashTime = millis() - lastFlash;

  //write both of the ledstates
  digitalWrite(led1, led1State);
  digitalWrite(led2, led2State);

  //save the buttonRead as buttonReadPre
  buttonReadPre = buttonRead;
}

//this is a handler function and it will execute automatically whenever there is a message from the FEED!!
//FEEED THE BEAST!!!
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");

  if (data->toPinLevel() == HIGH) {
    Serial.println("HIGH");
    lightMode += 1;
    if (lightMode > 3) {
      lightMode = 0;
    }
  }
  else
    Serial.println("LOW");
}
