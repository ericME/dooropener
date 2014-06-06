/*
Door Opener
-----------
Detects daylight and opens a door
Designed for a chicken coop, but could really be for anything.
by Eric Rouse
*/

int dirPin = 4;
int stepPin = 3;
int daylightPin = 8;
int lightDetectedPin = 13;
int spr = 1600; //steps per rev
int val = 0;
float fwd_revs = 5.5;
float rev_revs = 4.5;
int fwd_speed = 450;
int rev_speed = 100;
bool door_open = false;
bool m_fwd = true;
bool m_rev = false;

void setup()
{
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(daylightPin, INPUT);
  pinMode(lightDetectedPin,OUTPUT);
  Serial.begin(9600);

}

void step(boolean dir, int steps, int stepDelay)
{
  if (stepDelay < 80) stepDelay = 80;
  if (stepDelay > 5000) stepDelay = 5000;
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i=0;i<steps;i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
}

void loop()
{

  //if it is daylight and the door isn't open, open the door
  if (digitalRead(daylightPin) == LOW && door_open == false){
    digitalWrite(lightDetectedPin, HIGH);
    Serial.write("forward\n\r");
    step(m_fwd,spr*fwd_revs, fwd_speed);
    door_open = true;
    
  }
  //if it isn't daylight and the door is open, shut the door
  if(digitalRead(daylightPin) == HIGH && door_open == true){
    digitalWrite(lightDetectedPin, LOW);
    Serial.write("reverse\n\r");
    step(m_rev,spr*rev_revs, rev_speed);
    door_open = false;
    
    
  }

  //only check every half hour or so
  delay(1800000);
  
  
}
