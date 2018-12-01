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
int maxY = 31;
int minY = 0;

//Change 64 to a non-magic number and edit rest of the code + change 64 to (64 x 4 screens = 256)
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
  
  initAllScreens();

  Serial.begin(115200);
  Serial.println("start");
  nunchuck1.begin();
}

void loop() {
  nunchuck1.readData();
  //clearAllScreens();
  
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
    valFoodX = random(0,maxX);
    valFoodY = random(0,maxY);
    GrowSnake();
  }
  
  for(int i = 0; i < 64; i++)
  {
    if(myPositionX[i] == -1 ){break;}
    drawAt(myPositionX[i],myPositionY[i]);
  }
   
  drawAt(valFoodX, valFoodY);
  
 delay(20);
}

void GrowSnake()
{
  clearAllScreens();
  if(snakeLength < 63)
  {
    Serial.println("Snake Grows");
    snakeLength++;
    myPositionX[snakeLength] = myPositionX[snakeLength - 1];
    myPositionY[snakeLength] = myPositionY[snakeLength - 1];
  } 
}

void UpdateAllPositions()
{
  clearAllScreens();
  for(int i = 63; i > 0; i--)
  {
    if(myPositionX[i] != -1 ){
      myPositionX[i] = myPositionX[i - 1];
      myPositionY[i] = myPositionY[i - 1];
   }
  }
}

void drawAt(int x, int y){
 int whichScreen = 3 - floor(float(y)/8.0)  ;
 int yPos = y%8;
 lc.setLed(whichScreen,x,yPos,true);
}

void initAllScreens(){
 lc.shutdown(0,false);
 lc.shutdown(1,false);
 lc.shutdown(2,false);
 lc.shutdown(3,false);

 lc.setIntensity(0,1);
 lc.setIntensity(1,1);
 lc.setIntensity(2,1);
 lc.setIntensity(3,1);

 clearAllScreens();
}

void clearAllScreens(){
 lc.clearDisplay(0);
 lc.clearDisplay(1);
 lc.clearDisplay(2);
 lc.clearDisplay(3);
}
