/*
Door Opener
Detects daylight and opens a door
by Eric Rouse
*/

int dirPin = 7;
int stepperPin = 10;
int daylightPin = 4;
int daydetectPin = 11;
int spr = 1600; //steps per rev
bool door_open = false;
bool m_fwd = true;
bool m_rev = false;

void setup()
{
  pinMode(dirPin, OUTPUT);
  pinMode(stepperPin, OUTPUT);
  pinMode(daylightPin, INPUT);
  pinMode(daydetectPin,OUTPUT);

}

void step(boolean dir, int steps)
{
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i=0;i<steps;i++){
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(100);
  }
}

void loop()
{

  //if it's daylight and the door isn't open, open the door
  if (digitalRead(daylightPin) == LOW && door_open == false){
    digitalWrite(daydetectPin, HIGH);
    step(m_fwd,spr*5);
    door_open = true;
  }
  //if it isn't daylight and the door is open, shut the door
  if(digitalRead(daylightPin) == HIGH && door_open == true){
    digitalWrite(daydetectPin, LOW);
    step(m_rev,spr*5);
    door_open = false;    
  }

  //only check every half hour or so
  delay(1000);

}
