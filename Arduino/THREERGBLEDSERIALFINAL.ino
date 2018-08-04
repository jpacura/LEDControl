//PIN ASSIGNMENTS
int RGB1RED = 8;
int RGB1GREEN = 9;
int RGB1BLUE = 10;
int RGB2RED = 5;
int RGB2GREEN = 6;
int RGB2BLUE = 7;
int RGB3RED = 2;
int RGB3GREEN = 3;
int RGB3BLUE = 4;
//PIN ASSIGNMENTS

//SERIAL VARIABLES
int state = 0;
int r1 = 255;
int g1 = 255;
int b1 = 255;
int r2 = 255;
int g2 = 255;
int b2 = 255;
int r3 = 255;
int g3 = 255;
int b3 = 255;
//SERIAL VARIABLES

void setup()
{
  pinMode(RGB1RED, OUTPUT);
  pinMode(RGB1GREEN, OUTPUT);
  pinMode(RGB1BLUE, OUTPUT);
  pinMode(RGB2RED, OUTPUT);
  pinMode(RGB2GREEN, OUTPUT);
  pinMode(RGB2BLUE, OUTPUT);
  pinMode(RGB3RED, OUTPUT);
  pinMode(RGB3GREEN, OUTPUT);
  pinMode(RGB3BLUE, OUTPUT);

  Serial.begin(9600);
  
  startupblink();
}

void loop()
{
  if(Serial.available() > 0)
  {
    state = Serial.parseInt();

    if(state == 1)
    {
      //STATE 1 SETS ALL LED COLORS TO SERIAL INPUT
      r1 = Serial.parseInt();
      g1 = Serial.parseInt();
      b1 = Serial.parseInt();
      r2 = Serial.parseInt();
      g2 = Serial.parseInt();
      b2 = Serial.parseInt();
      r3 = Serial.parseInt();
      g3 = Serial.parseInt();
      b3 = Serial.parseInt();

      analogWrite(RGB1RED, 255);
      analogWrite(RGB1GREEN, 255);
      analogWrite(RGB1BLUE, 255);
      analogWrite(RGB2RED, 255);
      analogWrite(RGB2GREEN, 255);
      analogWrite(RGB2BLUE, 255);
      analogWrite(RGB3RED, 255);
      analogWrite(RGB3GREEN, 255);
      analogWrite(RGB3BLUE, 255);
      delay(250);
      analogWrite(RGB1RED, 255-r1);
      analogWrite(RGB1GREEN, 255-g1);
      analogWrite(RGB1BLUE, 255-b1);
      analogWrite(RGB2RED, 255-r2);
      analogWrite(RGB2GREEN, 255-g2);
      analogWrite(RGB2BLUE, 255-b2);
      analogWrite(RGB3RED, 255-r3);
      analogWrite(RGB3GREEN, 255-g3);
      analogWrite(RGB3BLUE, 255-b3);
    }
    else if(state==2)
    {
      //STATE 2 REPORTS THE CURRENT LED COLORS
      String d = ","; //DELIMETER CHARACTER
      String out = String(r1) + d + String(g1) + d + String(b1) + d + String(r2) + d + String(g2) + d + String(b2) + d + String(r3) + d + String(g3) + d + String(b3);
      delay(500);
      Serial.println(out);
    }
  }
}

void startupblink()
{
  analogWrite(RGB1RED, 0);
  analogWrite(RGB1GREEN, 255);
  analogWrite(RGB1BLUE, 255);
  analogWrite(RGB2RED, 0);
  analogWrite(RGB2GREEN, 255);
  analogWrite(RGB2BLUE, 255);
  analogWrite(RGB3RED, 0);
  analogWrite(RGB3GREEN, 255);
  analogWrite(RGB3BLUE, 255);
  delay(250);
  analogWrite(RGB1RED, 255);
  analogWrite(RGB1GREEN, 0);
  analogWrite(RGB1BLUE, 255);
  analogWrite(RGB2RED, 255);
  analogWrite(RGB2GREEN, 0);
  analogWrite(RGB2BLUE, 255);
  analogWrite(RGB3RED, 255);
  analogWrite(RGB3GREEN, 0);
  analogWrite(RGB3BLUE, 255);
  delay(250);
  analogWrite(RGB1RED, 255);
  analogWrite(RGB1GREEN, 255);
  analogWrite(RGB1BLUE, 0);
  analogWrite(RGB2RED, 255);
  analogWrite(RGB2GREEN, 255);
  analogWrite(RGB2BLUE, 0);
  analogWrite(RGB3RED, 255);
  analogWrite(RGB3GREEN, 255);
  analogWrite(RGB3BLUE, 0);
  delay(250);
  analogWrite(RGB1RED, 0);
  analogWrite(RGB1GREEN, 0);
  analogWrite(RGB1BLUE, 0);
  analogWrite(RGB2RED, 0);
  analogWrite(RGB2GREEN, 0);
  analogWrite(RGB2BLUE, 0);
  analogWrite(RGB3RED, 0);
  analogWrite(RGB3GREEN, 0);
  analogWrite(RGB3BLUE, 0);
}

