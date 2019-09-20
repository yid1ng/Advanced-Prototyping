
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
  Serial.begin(9600);
  pinMode(led1, OUTPUT);

  //don't forget to declare the new led pin as an OUTPUT!
  pinMode(led2, OUTPUT);
  pinMode(button1, INPUT);
  digitalWrite(led1, led1State);
}

void loop() {
  /*
     Let's add a second LED and a couple of modes!

     There are eight new global variables:
     to name a new led pin, track it state, and three modes, plus two time flash the leds without delay!
     The first major change is to make a button push toggle between modes

     Then we need to do different things with the leds depending on the value of the mode
  */

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

  /*
     now we need some new if statements to decide what to do depending on what the value of lightMode is
     these conditions are mutually exclusive so we can use if(){}else if(){}
  */

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
