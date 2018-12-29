const int SETUP_TIME = 5000;
const int AUTONOMOUS_TIME = 15000;
const int STOP_TIME = 2000;

int forward1;
int backward1;
int forward2;
int backward2;
int photo1;
int photo2;
int photo3;
int photo4;
int flexleft;
int flexright;

void setup() 
{
  Serial.begin(9600);
  forward1 = 11;
  backward1 = 10;
  forward2 = 6;
  backward2 = 5;
  pinMode(forward1, OUTPUT);
  pinMode(backward1, OUTPUT);
  pinMode(forward2, OUTPUT);
  pinMode(backward2, OUTPUT);
  photo1 = A0;
  pinMode(photo1, INPUT);
  photo2 = A1;
  pinMode(photo2, INPUT);
  photo3 = A2;
  pinMode(photo3, INPUT);
  photo4 = A3;
  pinMode(photo4, INPUT);
  flexleft = A5;
  pinMode(flexleft, INPUT);
  flexright = A4;
  pinMode(flexright, INPUT);
}

void loop() 
{
  //driveForward(255);
  autonomousMode();
}

void autonomousMode()
{
  int flex1 = analogRead(flexleft);
  int flex2 = analogRead(flexright);

  if (flex1 <= 915 && flex2 <= 810) //IF BOTH FLEX SENSORS ARE NOT ACTIVE
  {
    Serial.print("Forward=");
    Serial.println("Forward");
    driveForward(255);
  }
  else if (flex1 > 915 && flex2 > 810)
  {
    Serial.print("Backward=");
    Serial.println("Backward");
    driveBackward(200);
  }
  else if (flex1 > 915) //IF LEFT FLEX SENSOR IS COMPRESSED
  {
    Serial.print("LEFT=");
    Serial.println(flex1);
    driveRight(200);
  }
  else if (flex2 > 810) //IF RIGHT FLEX IS ACTIVE
  {
    Serial.print("RIGHT=");
    Serial.println(flex2);
    driveLeft(200);
  }

}

void teleOpMode()
{
  int photoState1 = analogRead(photo1);
  int photoState2 = analogRead(photo2);
  int photoState3 = analogRead(photo3);
  int photoState4 = analogRead(photo4);

  if (photoState1 >= 750)
  {
    Serial.println("ONE ");
    driveForward(200);
  }
  else if (photoState2 >= 750)
  {
    Serial.println("TWO ");
    driveBackward(200);
  }
  else if (photoState3 >= 850)
  {
    Serial.println("THREE ");
    driveLeft(200);
  }
  else if (photoState4 >= 850)
  {
    Serial.println("FOUR ");
    driveRight(200);
  }
  else
  {
    fullStop();
  }
}

void fullStop()
{
  analogWrite(forward1, 0);
  analogWrite(backward1, 0);
  analogWrite(forward2, 0);
  analogWrite(backward2, 0);
}

void driveForward(int power)
{
  analogWrite(forward1, power);
  analogWrite(backward1, 0);
  analogWrite(forward2, power);
  analogWrite(backward2, 0);
}
void driveBackward(int power)
{
  analogWrite(forward1, 0);
  analogWrite(backward1, power);
  analogWrite(forward2, 0);
  analogWrite(backward2, power);
}
void driveRight(int power)
{
  analogWrite(forward1, power);
  analogWrite(backward1, 0);
  analogWrite(forward2, 0);
  analogWrite(backward2, power);
}
void driveLeft(int power)
{
  analogWrite(forward1, 0);
  analogWrite(backward1, power);
  analogWrite(forward2, power);
  analogWrite(backward2, 0);
}
