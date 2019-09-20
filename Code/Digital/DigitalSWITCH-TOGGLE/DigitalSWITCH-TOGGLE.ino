
//these global variables give names to pin numbers
const int led1 = A0;
const int button1 = A5;

//these varibles control the led state
bool led1State = 0;  //bool is either true or fales (1 or 0)

void setup() {
  //open a serial connection for Debug output to serial monitor
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(button1, INPUT); //this makes button1 (pin A5) a digital input!
  digitalWrite(led1, led1State);
}

void loop() {
  /*
   * Buttons are more useful when they TOGGLE things on or off
   * To toggle the LED we still read the button pin
   * but now we use it to toggle a varible on or off (1 or 0)
   * Then we use that varible to write the led state
   * There is a new global variable up above the setup() fuction
   * It will control the desired state for the LED
   */

  int buttonRead = digitalRead(button1);
  delay(1);
  //debug output to see the current reading in the serial monitor
  Serial.print("buttonRead = ");
  Serial.println(buttonRead);

  //if the button is pushed
  if(buttonRead == 1) {
    led1State = !led1State; //! will make led1State the opposite of itself
  }

digitalWrite(led1, led1State);

}
