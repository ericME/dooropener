/*
Door Opener
by Eric Rouse
*/

int dirPin = 7;
int stepperPin = 10;
int daylightPin = 4;
int daydetectPin = 11;
int spr = 1600; //steps per rev
bool door_open = false;

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

  //if it's daylight, open the door
  if (digitalRead(daylightPin) == HIGH){
    digitalWrite(daydetectPin, HIGH);
    step(true,spr*5);
    door_open = true;
  }
  //if it isn't daylight and the door isn't open, shut the door
  if(digitalRead(daylightPin) == LOW && door_open == true){
    digitalWrite(daydetectPin, LOW);
    step(false,spr*5);
    door_open = false;    
  }

  
  delay(1000);

}
