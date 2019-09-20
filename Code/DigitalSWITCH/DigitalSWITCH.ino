
//these global variables give names to pin numbers
const int led1 = A0;
const int button1 = A5;  //this new variable gives the name button1 to pin A5

void setup() {
  /* 
    We may need to see what our button pin is doing. We can use the Serial library to get feedback
    Sometimes this is called "Debug" code because it allows us to find bugs in a program.
    Serial must be initialized with Serial.begin(baud_rate); this enables serial communication through the USB port
    baud_rate is the speed at which the serial port is allowed to send 1s and 0s to a connected device
    standard baud_rates can be found in the serial monitor under tools. 9600 and 115200 are common baud rates
  */
  //open a serial connection for Debug output to serial monitor
  Serial.begin(9600);
  pinMode(led1, OUTPUT);

  pinMode(button1, INPUT); //this makes button1 (pin A5) a digital input!
}

void loop() {
  /*
   * we use digitalRead(buttonPin); to see the state of a digital input pin
   * it can be stored for the duration of a loop with a variable which we declare here:
   */

  int buttonRead = digitalRead(button1);
  delay(1);
  //debug output to see the current reading in the serial monitor
  Serial.print("buttonRead = ");
  Serial.println(buttonRead);

  /*
   * now we need to use the button state to set the state of the led
   * this is called a conditional and we can say it like this:
   * "If the button is pushed ( ==1)
   * then turn the LED on"
   * "else turn the led off"
   * 
   * then the code looks like this:
   */

  //if the button is pushed
  if(buttonRead == 1) {
    digitalWrite(led1, HIGH);
  }
  else {digitalWrite(led1, LOW);
  }

}
