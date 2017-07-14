
// Creates a debounced switch state(High Low)controlled by a momentary contact - microswitches etc 
// A member function is also provided to tell you if the button has been pressed but you have not read/acted on this yet
class switchButton
{ 
 unsigned long previousMillis = 0;
 unsigned long delayMillis = 200;
 int pin;
 int lastReading = LOW;
 public:
  
  int state = HIGH;
  bool pressedNotActed = false;
   
    // Create instance of switchButton
switchButton(int whichPin){
  pin = whichPin;
  };
   
   // Reads digital pin and decides on state
void update(){
    int reading = digitalRead(pin);
	// if the button has been pressed ignore more presses for a few milliseconds to debounce
    if (reading == LOW && lastReading == HIGH && millis() - previousMillis > delayMillis) {
    	pressedNotActed = true;
    	previousMillis = millis();  
    	// Change state
    	if (state == HIGH){
       		state = LOW;
      		}
      	else{
      		state = HIGH;
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
};


