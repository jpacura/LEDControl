// PWM Color Control Pins
int RED = 9;
int GREEN = 11;
int BLUE = 10;
// RGB LEDs are arranged in Red, Blue, Green order

// Non-PWM LED Control Pins
const int LED[] = {5,6,7};
const int LEDCount = sizeof(LED) / sizeof(LED[0]);

// Global variables for LED Color control
int LEDColor[LEDCount][4]; // 3 colors per LED + blink variable

// Global variables for multiplexing control
int multiplexInterval = 45;
int blinkInterval = 10000;
int counter = 0;
int blinkCounter = 0;

void setup()
{
  // Set the three color pins as outputs
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // Set the LED control pins as outputs
  for(int i = 0; i < LEDCount; i++)
  {
    pinMode(LED[i], OUTPUT);
  }
  
  //Initialize LED Color double array
  for(int i = 0; i < LEDCount; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      LEDColor[i][j] = 0;
    }
  }

  setDefaultState();

  Serial.begin(9600);

  Serial.write(0);
}

void loop()
{
  serialLoop();
  
  multiplexLoop();
}

void setDefaultState()
{
  // Because we already initialized the LED array in setup()
  // We do not have to specify any 0 values here
  
  LEDColor[0][0] = 255; // Set LED 1 to Red
  LEDColor[1][1] = 255; // Set LED 2 to Green
  LEDColor[2][2] = 255; // Set LED 3 to Blue
}

void multiplexLoop()
{
  if(counter == multiplexInterval * LEDCount)
  {
    counter = 0;
  }

  if(blinkCounter == blinkInterval * 2)
  {
    blinkCounter = 0;
  }

  int turn = floor(counter / multiplexInterval);

  for(int i = 0; i < LEDCount; i++)
  {
    // Turn off all other LEDs
    if(i != turn)
    {
      digitalWrite(LED[i], LOW);
    }
  }

  // Set LED to correct color
  analogWrite(RED, 255 - LEDColor[turn][0]);
  analogWrite(GREEN, 255 - LEDColor[turn][1]);
  analogWrite(BLUE, 255 - LEDColor[turn][2]);

  // Determine if LED should be on or off for blinking
  bool blinkState = HIGH;
  if(LEDColor[turn][3]) // Should be true for non-zero integer values
  {
    if(blinkCounter >= blinkInterval)
    {
      blinkState = LOW;
    }
  }
  
  // Turn on the LED whose turn it is to be on
  digitalWrite(LED[turn], blinkState);

  counter++;
  blinkCounter++;
}

void serialLoop()
{
  if(Serial.available() > 0)
  {
    int opcode = Serial.parseInt();

    if(opcode == 0) // DO NOTHING
    {
      // Serial.parseInt() will return 0 if the serial data is not an integer
      // This will happen if letters are sent by mistake. 
      // We will do nothing here so that no unexpected output will be sent out
      // of the serial link
    }
    else if(opcode == 1) // Heartbeat opcode
    {
      Serial.println(0);
    }
    else if(opcode == 2) // Get current LED Status
    {
      for(int i = 0; i < LEDCount; i++)
      {
        for(int j = 0; j < 4; j++)
        {
          Serial.print(String(LEDColor[i][j]) + " ");
        }
        Serial.println();
      }
    }
    else if(opcode == 3) // Change LED state
    {
      // If opcode 3 is received, the next integer received will be the LED number
      // and the integer after that will be the color, and finally, the new value
      // Example "3 1 2 255" will set the second LED (index 1) Color 2 (blue) to 255
      // If you specify -1 as the LED, it will change all LEDs
      int led = Serial.parseInt();
      int col = Serial.parseInt();
      int val = Serial.parseInt();

      if(led == -1)
      {
        // Change ALL LEDs to this color
        for(int i = 0; i < LEDCount; i++)
        {
          LEDColor[i][col] = val;
        }
      }
      else
      {
        LEDColor[led][col] = val;
      }

      Serial.println(0);
    }
    else if(opcode == 4) // Turn off all LEDs
    {
      for(int i = 0; i < LEDCount; i++)
      {
        for(int j = 0; j < 4; j++)
        {
          LEDColor[i][j] = 0;
        }
      }
      Serial.println(0);
    }
    else if(opcode == 5) // Set All LED to white
    {
      for(int i = 0; i < LEDCount; i++)
      {
        for(int j = 0; j < 3; j++)
        {
          LEDColor[i][j] = 255;
        }
        LEDColor[i][3] = 0; // Do not blink
      }
      Serial.println(0);
    }
    else if(opcode == 6) // Set All LED to white blinking
    {
      for(int i = 0; i < LEDCount; i++)
      {
        for(int j = 0; j < 4; j++)
        {
          LEDColor[i][j] = 255;
        }
      }
      Serial.println(0);
    }
    else // Invalid opcode
    {
      Serial.println(-1);
    }
  }
}
