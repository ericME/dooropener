/*
Door Opener
-----------
Detects daylight and opens a door
Designed for a chicken coop, but could really be for anything.
by Eric Rouse
*/

int dirPin = 7;
int stepPin = 10;
int daylightPin = 4;
int lightDetectedPin = 11;
int spr = 1600; //steps per rev
float fwd_revs = 5.5;
float rev_revs = 4.5;
bool door_open = false;
bool m_fwd = true;
bool m_rev = false;

void setup()
{
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(daylightPin, INPUT);
  pinMode(lightDetectedPin,OUTPUT);

}

void step(boolean dir, int steps)
{
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i=0;i<steps;i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(100);
  }
}

void loop()
{

  //if it is daylight and the door isn't open, open the door
  if (digitalRead(daylightPin) == LOW && door_open == false){
    digitalWrite(lightDetectedPin, HIGH);
    step(m_fwd,spr*fwd_revs);
    door_open = true;
  }
  //demo only, remove before production
  if (digitalRead(8) == HIGH){
    for (int i = 0; i < 100; i++){
      digitalWrite(stepPin, HIGH);
      digitalWrite(dirPin, LOW);
      delay(100);
      digitalWrite(stepPin, LOW);
      digitalWrite(dirPin, HIGH);
      delay(500);
    }
  }
  delay(1000);
  
  //if it isn't daylight and the door is open, shut the door
  if(digitalRead(daylightPin) == HIGH && door_open == true){
    digitalWrite(lightDetectedPin, LOW);
    step(m_rev,spr*rev_revs);
    door_open = false;
    
  }

  //only check every half hour or so 1800000
  //delay(1800000);

}
