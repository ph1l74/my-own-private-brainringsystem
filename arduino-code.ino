int ledOne = 15;   // LED1 connected to Analog Pin 1 (A1)
int ledTwo = 16;   // LED2 connected to Analog Pin 2 (A2)
int ledThree = 17; // LED3 connected to Analog Pin 3 (A3)
int ledFour = 18;  // LED4 connected to Analog Pin 4 (A4)
int ledFive = 19;  // LED5 connected to Analog Pin 5 (A5)

int ledMonitor = 14; // LEDSTART connected to Analog Pin 0 (A0)

int btnOne = 4;   // BUTTON1 connected to Digital Pin 4 (D4)
int btnTwo = 5;   // BUTTON2 connected to Digital Pin 5 (D5)
int btnThree = 6; // BUTTON3 connected to Digital Pin 6 (D6)
int btnFour = 7;  // BUTTON4 connected to Digital Pin 7 (D7)
int btnFive = 8;  // BUTTON5 connected to Digital Pin 8 (D8)

int btnStart = 2; // BUTTONSTART connected to Digital Pin 2 (D2)
int btnStop = 3;  // BUTTONSTOP connected to Digital Pin 3 (D3)

boolean timerStarted = false; // Timer Start flag

int delayForLED = 20;             // IN MSECS
unsigned long timeLimit = 300000; // IN MSECS
unsigned long previousMillis = 0;

void setup()
{
  Serial.begin(9600);

  // LED sequential lighting.
  analogWrite(ledOne, 255);
  delay(delayForLED);
  analogWrite(ledOne, 0);
  delay(delayForLED);
  analogWrite(ledTwo, 255);
  delay(delayForLED);
  analogWrite(ledTwo, 0);
  delay(delayForLED);
  analogWrite(ledThree, 255);
  delay(delayForLED);
  analogWrite(ledThree, 0);
  delay(delayForLED);
  analogWrite(ledFour, 255);
  delay(delayForLED);
  analogWrite(ledFour, 0);
  delay(delayForLED);
  analogWrite(ledFive, 255);
  delay(delayForLED);
  analogWrite(ledFive, 0);
  delay(delayForLED);
  analogWrite(ledFour, 255);
  delay(delayForLED);
  analogWrite(ledFour, 0);
  delay(delayForLED);
  analogWrite(ledThree, 255);
  delay(delayForLED);
  analogWrite(ledThree, 0);
  delay(delayForLED);
  analogWrite(ledTwo, 255);
  delay(delayForLED);
  analogWrite(ledTwo, 0);
  delay(delayForLED);
  analogWrite(ledOne, 255);
  delay(delayForLED);
  analogWrite(ledOne, 0);
  Serial.println(timeLimit);
}

void loop()
{

  if (digitalRead(btnStart) && !timerStarted)
  {
    startTimer();
    previousMillis = millis();
  }
  if (timerStarted)
  {
    if ((unsigned long)(millis() - previousMillis) < timeLimit)
    {

      checkButtons();
    }
    else
    {
      stopTimer();
      Serial.println("Time passed");
    }
  }
}

void checkButtons()
{
  if (digitalRead(btnOne))
  {
    stopTimer();
    analogWrite(ledOne, 255);
    Serial.print("Player one pressed in ");
    Serial.print((millis() - previousMillis) / 1000);
    Serial.println(" sec.");
  }
  else if (digitalRead(btnTwo))
  {
    stopTimer();
    analogWrite(ledTwo, 255);
    Serial.print("Player two pressed in ");
    Serial.print((millis() - previousMillis) / 1000);
    Serial.println(" sec.");
  }
  else if (digitalRead(btnThree))
  {
    stopTimer();
    analogWrite(ledThree, 255);
    Serial.print("Player three pressed in ");
    Serial.print((millis() - previousMillis) / 1000);
    Serial.println(" sec.");
  }
  else if (digitalRead(btnFour))
  {
    stopTimer();
    analogWrite(ledFour, 255);
    Serial.print("Player four pressed in ");
    Serial.print((millis() - previousMillis) / 1000);
    Serial.println(" sec.");
  }
  else if (digitalRead(btnFive))
  {
    stopTimer();
    analogWrite(ledFive, 255);
    Serial.print("Player five pressed in ");
    Serial.print((millis() - previousMillis) / 1000);
    Serial.println(" sec.");
  }
}

void startTimer()
{
  timerStarted = true;
  turnOffLights();
  analogWrite(ledMonitor, 255);
  Serial.println("status:timer_started");
}

void stopTimer()
{
  timerStarted = false;
  analogWrite(ledMonitor, 0);
  Serial.println("status:timer_stopped");
}

void turnOffLights()
{
  analogWrite(ledOne, 0);
  analogWrite(ledTwo, 0);
  analogWrite(ledThree, 0);
  analogWrite(ledFour, 0);
  analogWrite(ledFive, 0);
}
