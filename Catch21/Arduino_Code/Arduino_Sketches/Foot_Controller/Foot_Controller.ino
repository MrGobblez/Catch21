const int modePin = 2;
const int keyPin = A0;
const int indicatorLed = 7;
const int tealButtonLED = 8;
const int redButtonLED = 9;
const int yellowButtonLED = 10;
const int blueButtonLED = 11;
const int whiteButtonLED = 12;

int previous = 0;
int keyValue = 0;
char charToSend;
char lastCharSent;
char charIn;
String stringIn = "";

void setup()
{
  Serial.begin(9600);
  pinMode(modePin, INPUT);
  pinMode(indicatorLed, OUTPUT);
  pinMode(tealButtonLED, OUTPUT);
  pinMode(redButtonLED, OUTPUT);
  pinMode(yellowButtonLED, OUTPUT);
  pinMode(blueButtonLED, OUTPUT);
  pinMode(whiteButtonLED, OUTPUT);
  
  digitalWrite(indicatorLed, HIGH);
  digitalWrite(tealButtonLED, HIGH);
  digitalWrite(redButtonLED, HIGH);
  digitalWrite(yellowButtonLED, HIGH);
  digitalWrite(blueButtonLED, HIGH);
  digitalWrite(whiteButtonLED, HIGH);
}

void loop()
{
  // Check for incomming serial data
  if (Serial.available() > 0)
    {
      charIn = Serial.read();
      stringIn += charIn;
      if (charIn == '.')
      {
        if (stringIn == "12345.")
        {
          Serial.println("F");
        }
        stringIn = "";
      }
    }
    
  // Check for pressed buttons
  keyValue = analogRead(keyPin);
  if((keyValue < (previous-5) || keyValue > (previous+5)))
  {
    if(keyValue > 10)
    {
      setKey(keyValue);
      sendChar();
    }
    previous = keyValue;
  }
  if(digitalRead(modePin) == HIGH){
    Serial.println("HIGH");
    digitalWrite(indicatorLed, HIGH);
  }
  else
  digitalWrite(indicatorLed, LOW);
  
}

void setKey(int keyValue)
{
  // Checks which button that is pressed and sets correct char
  
  // White Button
  if (keyValue>160 && keyValue<170)
  {
    charToSend = 'w';
  }
  
  // Blue Button
  else if (keyValue>200 && keyValue<210)
  {
    charToSend = 'a';
  }
  
  // Yellow Button
  else if (keyValue>250 && keyValue<260)
  {
    charToSend = 's';
  }
  
  // Red Button
  else if (keyValue>335 && keyValue<345)
  {
    charToSend = 'd';
  }
  
  // Teal Button
  else if (keyValue>505 && keyValue<515)
  {
    charToSend = '1';
  }
  
  else
  {
    charToSend = 'N';
  }
  // Block until button is released
  while (analogRead(keyPin)>10)
  {
    // Block!
  }
}

void sendChar()
{
    Serial.println(charToSend);
}
