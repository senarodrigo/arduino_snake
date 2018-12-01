#include "LedControl.h"
#include <WiiChuck.h>
Accessory nunchuck1;
LedControl lc = LedControl(12,11,10,4); //

int buttonState = 0;
int valX = 4;
int valY = 4;

int valFoodX = 6;
int valFoodY = 6;

int maxX = 7;
int minX = 0;
int maxY = 7;
int minY = 0;

int myPositionX [64];
int myPositionY [64];

int snakeLength = 0;

int ROWS = 8;
int COLUMNS = 8;
int matrix_state[8][32];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  myPositionX[0]= valX;
  myPositionY[0]= valY;

  for(int i = 1; i<64; i++)
  {
    myPositionX [i] = -1;
    myPositionY [i] = -1;
  }
  
  lc.shutdown(0,false);
  lc.setIntensity(0,0.1);
  lc.clearDisplay(0);
  //lc.setLed(0,1,1,1);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  Serial.begin(115200);
  Serial.println("start");
  nunchuck1.begin();
}

void loop() {

  if(nunchuck1.getJoyX()>170){
    if(myPositionX[0] < maxX)
    {
      UpdateAllPositions();
      myPositionX[0]++;
    }   
  } 
  else if (nunchuck1.getJoyX()<100){
    if(myPositionX[0] > minX)
    {
      UpdateAllPositions();
      myPositionX[0]--;
    }   
  }

  if(nunchuck1.getJoyY()>170){
    if( myPositionY[0] < maxY)
    {
      UpdateAllPositions();
       myPositionY[0]++;
    }
     
  } 
  else if (nunchuck1.getJoyY()<100){
    if( myPositionY[0]>minY)
    {
      UpdateAllPositions();
      myPositionY[0]--;
    }
  }
  
  if(myPositionX[0] == valFoodX &&  myPositionY[0] == valFoodY){
    valFoodX = random(0,8);
    valFoodY = random(0,8);
    GrowSnake();
  }
  
  for(int i = 0; i < 64; i++)
  {
    if(myPositionX[i] == -1 ){break;}
    lc.setLed(0,myPositionX[i],myPositionY[i],true);
    Serial.println("On ");
    Serial.println(i);
  }
   
  lc.setLed(0,valFoodX, valFoodY,true);
  //now the Led at row 0, second from the left side
  //lc.setLed(0,0,1,true);
  int randNumber = random(0, 1); 
  //delay(1000); 
  
  delay(10);

  lc.clearDisplay(0);
  //switch the first Led off (second one stays on) 
  //lc.setLed(0,2,7,false); 
  
  // put your main code here, to run repeatedly:
  //if(buttonState){
    //val0++;
  //}
  //else {
    //val0--;
  //}
  //led_matrix.setLed(0,val0,val0,val0);


  //WiiChuck
 nunchuck1.readData();
 //nunchuck1.printInputs();

 nunchuck1.getJoyX();
 nunchuck1.getJoyY();

 nunchuck1.getRollAngle();
 nunchuck1.getPitchAngle();
 nunchuck1.getAccelX();
 nunchuck1.getAccelY();
 nunchuck1.getAccelZ();

 nunchuck1.getButtonC();
 nunchuck1.getButtonZ();
}

void GrowSnake()
{
  if(snakeLength < 63)
  {
    Serial.println("Snake Grows");
    snakeLength++;
    myPositionX[snakeLength] = myPositionX[snakeLength - 1];
    myPositionY[snakeLength] = myPositionY[snakeLength - 1];
  } 
}

void UpdateAllPositionsX()
{
  for(int i = 1; i < 63; i++)
  {
    if(myPositionX[i] == -1 ){break;}
    myPositionX[i] = myPositionX[i - 1];
  }
}

void UpdateAllPositions()
{
  for(int i = 1; i < 63; i++)
  {
    if(myPositionX[i] == -1 ){break;}
    myPositionX[i] = myPositionX[i - 1];
    myPositionY[i] = myPositionY[i - 1];
  }
}
