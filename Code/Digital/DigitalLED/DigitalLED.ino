/* Here we declare variables to store data in our program
 * variables use a little bit of memory to store a little bit of data of different types
 * data types (int, long, float, double, uint_16, char, string etc.) determine what kind of data is stored in memory
 * 
 * there are two types of memory: program and dynamic
 * program memory stores all of the compiled code you write and other things you want to place there
 * it says static until the uC is reprogrammed (from the upload button in this case)
 * dynamic memory stores information for the short term and it can change over the course of a program
 * variables have a SCOPE which is like visibility to parts of the program
 * if a variable is declared outside of any brackets or braces its scope is GLOBAL
 * global variables consume dynamic memory for the entire run of a program 
 * global variables have a set type but their values can change (unless declared const - constant)
 * if a variable is declared inside a set of curly braces {} that varible is can only be used by code that is also in the braces
 * after the code in the braces has run the memory for that varible can be used by another part of a program
 * that memory is dynamic; it is volitile. 
 */

//these global variables give names to pin numbers
const int led1 = A0;

//these global variables control timing
int onDelay = 500;
int offDelay = 250;

// put setup code here, to run once when the uC is powered on:
void setup() {
  /* 
   *  pinMode is a function we need to call. Function calls usually look like this: function();
   *  Anything placed in the () is called an argument
   *  The pinMode() function takes two arguments: an integer and a keyword
   *  led1 is an integer global variable and OUTPUT is a keyword
   *  We could also use INPUT or INPUT_PULLUP as keywords to change how the pin functions.
   *  
   *  You will also notice that setup() above and loop() below are also functions. 
   *  However setup() and loop() have a declaration in front of them (void)
   *  Just like the variable type (int) above, void is also a type
   *  Just like we declared variables above we are declaring setup() and loop() only with a void type...
   *  Void means a function does not return a value. If a function is declared with a data type it can also return a value.
   *  We now know the structure for declaring and calling both variables and functions.
  */
  pinMode(led1, OUTPUT);
}

// put other code here, to run repeatedly:
void loop() {
  //digitalWrite() uses two arguments (int pin# and digital state (HIGH/LOW || 1/0)) to control a digital output
  digitalWrite(led1, HIGH);
  //delay uses one argument (int milliseconds) to pause the program for a short period of time
  delay(onDelay);
  digitalWrite(led1, LOW);
  //delay can be problematic when programs become more complex becuase nothing else can happen during a delay...
  delay(offDelay);
}
