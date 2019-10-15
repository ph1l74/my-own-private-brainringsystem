int ledOne = 15;    // LED1 connected to Analog Pin 1 (A1) 
int ledTwo = 17;    // LED2 connected to Analog Pin 3 (A3) 
int ledThree = 19;  // LED3 connected to Analog Pin 5 (A5) 

int ledMonitor = 14; 

int btnOne = 4;    // BUTTON1 connected to Digital Pin 3 (A1) 
int btnTwo = 5;    // BUTTON2 connected to Digital Pin 5 (A3) 
int btnThree = 7;  // BUTTON3 connected to Digital Pin 7 (A5) 

int btnStart = 2;    // BUTTONSTART connected to Digital Pin 2 (A1) 
int btnStop = 3;    // BUTTONSTOP connected to Digital Pin 3 (A1) 

boolean timerStarted = false;

int timeLimit = 30000;
unsigned long previousMillis = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {

  unsigned long currentMillis = millis();

  if(digitalRead(btnStart)){
//    Serial.println("btnStart pressed...");
    startTimer();
    previousMillis = millis();
  }
  if (digitalRead(btnStop)){
//    Serial.println("btnStop pressed...");
    stopTimer();
    previousMillis = millis();
  }
  if(timerStarted){
    if((unsigned long)(currentMillis - previousMillis) > timeLimit){
      Serial.println(previousMillis);
    }
    else {
      Serial.println("Time passed");
      stopTimer();
    }
  } 
}

void startTimer() {
  timerStarted = true;
  Serial.println("Timer started...");
}

void stopTimer() {
  timerStarted = false;
  Serial.println("Timer stopped.");
}
