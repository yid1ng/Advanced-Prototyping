
//these global variables give names to pin numbers
const int led1 = A0;
const int button1 = A5;

//these varibles control the led state
int led1State = 0;  //bool is either true or fales (1 or 0)

//these global variables will track what the last read of the switch was and the current state
int buttonReadPre = 0;
int buttonState;

//this global variable will mark when the button changes
unsigned long buttonTime;

void setup() {
  //open a serial connection for Debug output to serial monitor
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(button1, INPUT);
  digitalWrite(led1, led1State);
}

void loop() {
  /*
   * That works, but its buggy. Why? Switches have a tendency to "bounce"
   * Switches bounce becuase they are mechanical and the metal contacts don't make perfect contact
   * 
   * To fix our buggy switch we need to make sure we really meant to push the switch
   * There are a lot of ways to do this. One simple way is to time the swtich when it changes
   * 
   * There are two new global variables to keep track of time the button state and the previous button state
   * A third will keep track of when the button state changes
   */

  int buttonRead = digitalRead(button1);
  delay(1);

  //if the button changes
  if(buttonRead != buttonReadPre) {
    //start the timer
    buttonTime = millis(); //millis(); returns the time since the program started...
  }

  //now we we check to see if the elapsed time is greater than a threshold
  int debounceTime = millis() - buttonTime; //current time minus start time is elapsed time...
  
  //if the debounce time is or more than 50ms...
  if (debounceTime >= 50) {
    
    //if the buttonRead is different than the buttonState
    if(buttonRead != buttonState) {
      //buttonState should now be the same as the read...
      buttonState = buttonRead;

      //if the button state is also now high...
      if(buttonState == 1){
        //go ahead and toggle the ledState
        led1State = !led1State;
      }
    }
  }

//write the ledstate
digitalWrite(led1, led1State);

//save the buttonRead as buttonReadPre
buttonReadPre = buttonRead;

}
