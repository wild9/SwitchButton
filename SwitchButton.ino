
// Creates a debounced switch state(High Low)controlled by a momentary contact - microswitches etc 
// Member functions are provided to tell you if the button has been pressed but you have not read/acted on this yet,
// the button has been held and you havnt read/acted on this yet and how long it has been held for.
// A number of
class switchButton
{ 
 unsigned long previousMillis = 0;
 int delayMillis = 200;
 int pin;
 int lastReading = LOW;
 int numberOfStates;
 unsigned long holdStart = 0;
 int holdThreshold = 1000;
 
 public:
  unsigned long holdTime = 0;
  int state = 1;
  bool pressedNotActed = false;
  bool heldNotActed = false;
   
    // Create instance of switchButton
switchButton(int whichPin,int HowManyStates){
  pin = whichPin;
  numberOfStates = HowManyStates;
  };
    


    // Reads digital pin and decides on state
void update(){
    int reading = digitalRead(pin);
	// if the button has been pressed ignore more presses for a few milliseconds to debounce
  
  if (reading == LOW && lastReading == LOW)
  	{
    if (holdStart == 0)
    	{
    		holdStart = millis();
          	holdTime = 0;
    	}
    
    else
    	{
      		holdTime = millis() - holdStart;
    	}
    
    
  	}
  
  else
  	{
 		holdStart = 0;
  	}
  if (holdTime >= holdThreshold && reading == HIGH && lastReading == LOW)
    	{
      		heldNotActed = true;
      		
            
    	}
  
  if (reading == HIGH && lastReading == LOW && millis() - previousMillis > delayMillis && holdTime < holdThreshold) {
    	pressedNotActed = true;
    	previousMillis = millis();  
    	// Change state
    	if (state < numberOfStates){
       		state++;
      		}
      	else{
      		state = 1;
      		}
  }
  lastReading = reading;
}
  
  
    // Returns True if the button has been pressed and this is the first time it has been read
  bool pressed(){
    
    bool returnvalue = pressedNotActed;
    pressedNotActed = false;
    return returnvalue;
    
  };
  // Returns True if the button has been held and this is the first time it has been read
 bool held(){
    
    bool returnvalue = heldNotActed;
    heldNotActed = false;
    return returnvalue;
    
  };
  
  //returns the number of seconds a button has been held for if it has been held longer than the hold threshhold
  int heldFor(){
    int returnValue = 0;
   
    if (heldNotActed == true && holdStart == 0)
    {
    returnValue = (holdTime / 1000);
    heldNotActed = false;
    }
    
    return returnValue;
  };

       
};


////////////////////////////////////////////////////////////////















// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledPin = 13;
switchButton button1(3,5);
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  // initialize the digital pin as an output.
  pinMode(3,INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
  button1.update();
  if (button1.state == 1) {
        digitalWrite(ledPin, HIGH);
      Serial.println("LED ON");
      }
  else{
    	digitalWrite(ledPin, LOW);
      Serial.println("LED OFF");
}
    Serial.println(button1.state);
  //Serial.println(button1.holdTime);
  Serial.println(button1.heldNotActed);
  Serial.println(button1.heldFor());
}
