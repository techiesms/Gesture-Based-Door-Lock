/**************************************************
Gesture Based Door Unlock Projec by techiesms (Sachin Soni)

  Hardware Connections:
  Arduino Pin  3D Gesture Sensor-mini  Board  Function
  GND          GND              Ground
  3.3V-5V      VCC              Power
  A5           SCL              I2C Clock
  A4           SDA              I2C Data
  D7           D                Digital port

***************************************************/
#include <DFRobot_Gesture.h>
#include <Wire.h>


int i = 0;
int testPin = 2;
int relay = 3;
int buzzer = 4;
unsigned char cmd;

int code[4] = {0, 0, 0, 0};
int password[4] = {2, 3, 2, 4}; // LEft Down Left Right
bool wrong_password = 0;
DFRobot_Gesture myGesture;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  pinMode(testPin, INPUT);
  pinMode(relay,OUTPUT);
  pinMode(buzzer,OUTPUT);

  digitalWrite(relay,HIGH);
  Serial.println("Door Locked");
  Serial.write("3D Gesture sensor is now running....\r\n");
}


void loop()
{

  if (digitalRead(testPin) == 0)
  {

    myGesture.I2C1_MasterRead(md.buf, 26, 0x42); //The address is:0x42
    cmd = myGesture.mgcProcMsg();     //process the message
    if (cmd != GI_NOGESTURE )
    {
      switch (cmd)
      {

        case GI_FLICK_R:
          digitalWrite(buzzer,HIGH);
          delay(10);
          digitalWrite(buzzer,LOW);
          Serial.println("RIGHT");
          code[i] = 1;
          i++;
          
          break;

        case GI_FLICK_L:
          digitalWrite(buzzer,HIGH);
          delay(10);
          digitalWrite(buzzer,LOW);
          Serial.println("LEFT");
          code[i] = 2;
          i++;
          break;

        case GI_FLICK_D:
          digitalWrite(buzzer,HIGH);
          delay(10);
          digitalWrite(buzzer,LOW);
          Serial.println("DOWN");
          code[i] = 3;
          i++;
          break;

        case GI_FLICK_U:
          digitalWrite(buzzer,HIGH);
          delay(10);
          digitalWrite(buzzer,LOW);
          Serial.println("UP");
          code[i] = 4;
          i++;
          break;
        case GI_AIRWHEEL_CW://Clockwise in circles
          Serial.println("CW");
          break;

        case GI_AIRWHEEL_CCW://Counterclockwise circles
          Serial.println("CCW");
          break;

        default: break;
      }

      if (i > 3)
      {
        Serial.println("Checking");
        for (int k = 0; k < 4; k++)
        {
          if (code[k] == password[k])
          {
            //Serial.println("true");
            
          }
          else
          {
            wrong_password = 1;
            break;
          }
        }
        if (wrong_password)
        {
          Serial.println("Wrong Password");
          for(int j=0;j<3;j++)
          {
          digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          delay(100);
          }
          i = 0;
          for (int k = 0; k < 4; k++)
          code[k] = 0;
          wrong_password = 0;
          delay(1000);
        }
        else 
        {
          Serial.println("Right Password");
          digitalWrite(buzzer,HIGH);
          delay(1500);
          digitalWrite(buzzer,LOW);
          i = 0;
          for (int k = 0; k < 4; k++)
          code[k] = 0;
          delay(500);
          digitalWrite(relay,LOW);
          Serial.println("Door Unlocked for 5 seconds...");
          delay(5000);
          digitalWrite(relay,HIGH);
          Serial.println("Door Locked");
          
        }
      }


    }
  }

  else  {};

}
