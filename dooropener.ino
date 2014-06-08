/*
Door Opener
-----------
Detects daylight and opens a door
Designed for a chicken coop, but could really be for anything.
by Eric Rouse
*/
//declare vars
//direction pin
int dirPin = 4;
//step pin
int stepPin = 3;
//sleep pin
int sleepPin = 7;
//event that opens the door
//in this case, daylight detected
int daylightPin = 8;
//signify detection occured by turning
//on the on-board led
int lightDetectedPin = 13;
//stepper motor steps per revolution
int spr = 1600;
//number of revolutions to open
float fwd_revs = 5.5;
//number of revolutions to close
float rev_revs = 4.5;
//opening speed
int fwd_speed = 450;
//closing speed
int rev_speed = 100;
//door status flag
bool door_open = false;
//pin status for open/close
bool m_fwd = HIGH;
bool m_rev = LOW;

void setup()
{
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(daylightPin, INPUT);
  pinMode(lightDetectedPin,OUTPUT);
  pinMode(sleepPin, OUTPUT);
  Serial.begin(9600);

}

void step(boolean dir, int steps, int stepDelay)
{
  //sanitze inputs
  if (stepDelay < 80) stepDelay = 80;
  if (stepDelay > 5000) stepDelay = 5000;
  //turn on motor
  digitalWrite(sleepPin, HIGH);
  //set direction
  digitalWrite(dirPin, dir);
  delay(50);
  //step
  for (int i=0;i<steps;i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  digitalWrite(sleepPin, LOW);
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

  //only check every half hour (1800000ms) or so
  delay(1800000);
  
  
}
