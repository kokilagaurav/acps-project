#define LOCK_PIN 8     // Pin connected to door lock mechanism (relay or motor driver)
#define LED_GREEN 12   // Pin for success indicator LED
#define LED_RED 13     // Pin for denial indicator LED

String inputString = "";      // String to hold incoming data
boolean stringComplete = false;  // Whether the string is complete

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize output pins
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // Initial state: door locked
  digitalWrite(LOCK_PIN, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
}

void loop() {
  if (stringComplete) {
    if (inputString.indexOf("open_gate") != -1) {
      openDoor();
      Serial.println("ACCESS_GRANTED");  // Changed confirmation message
    } 
    else if (inputString.indexOf("close_gate") != -1) {
      closeDoor();
      Serial.println("ACCESS_DENIED");  // Changed confirmation message
    }
    else {
      Serial.println("INVALID_COMMAND");  // Error message
    }
    
    inputString = "";
    stringComplete = false;
  }
}

// Serial event handler
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    // Look for newline as command terminator
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void openDoor() {
  digitalWrite(LOCK_PIN, HIGH);  
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);   
  Serial.println("UNLOCKED");
  delay(120000);  // Changed to 2 minutes (120000ms)                
  closeDoor();                  
}

void closeDoor() {
  digitalWrite(LOCK_PIN, LOW);   
  digitalWrite(LED_GREEN, LOW); 
  digitalWrite(LED_RED, HIGH);   
  Serial.println("LOCKED");
}
