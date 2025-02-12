// HPIK Engine Gen3 Arduino code

int Trigger = 11;     // Trigger input
int Solenoid =  10;      // Solenoid output
int FullAuto = 7;
int val = 0;
int buttonState = 0;         // Read pushbutton state
int Delay = A1; // Solenoid delay port
int val2  = 0; // Delay rule
int RPS = A0; // RPS Adjustment
int val3 = 0; // RPS rule
boolean OnceAlreadyShot = false;

void setup() {
  pinMode(Solenoid, OUTPUT); // Define solenoid output
  pinMode(Trigger, INPUT);  // Define pushbutton input trigger
  pinMode(FullAuto, INPUT);    // Define Full auto input button
 
}

void loop() {
  
  buttonState = digitalRead(Trigger); // Reading trigger 
  
  if (buttonState == HIGH) {        // If pressed, state is HIGH
    val = digitalRead(FullAuto);       // Full auto state. Activate Full auto
  
  
    if (val == HIGH) {                // If pressed
      
      val2 = analogRead(Delay);       // Delay pot time
      val2 = map(val2, 0, 1023, 10, 100); // Remapping 0-100
      val3 = analogRead(RPS);             // Reading Full auto adjustment
      val3 = map(val3, 0, 1023, 30, 150); // Full auto speed
      digitalWrite(Solenoid, HIGH);  // Solenoid open
      delay (val2);
      digitalWrite(Solenoid, LOW);  // Solenoid closed
      delay (val3);                     //debounce delay always to the end!
    }                                 // In other case, single fire
    else if (!OnceAlreadyShot) {      //shoot once, if not already shot
      val2 = analogRead(Delay);       // reading delay
      val2 = map(val2, 0, 1023, 10, 100); // remapping delay input
      digitalWrite(Solenoid, HIGH);  // solenoid open
      delay (val2);
      digitalWrite(Solenoid, LOW);   // solenoid closed
      delay (100);
      OnceAlreadyShot = true;         //Shot once
    }
  }
  else
  {
    OnceAlreadyShot = false;          //restore to the beginning
  }
}
