#include "LedControl.h"
#include <WiiChuck.h>
Accessory nunchuck1;
LedControl lc = LedControl(12,11,10,4); //

int ROWS = 8;
int COLUMNS = 8;
int matrix_state[8][32];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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

int buttonState = 0;
int valX = 4;
int valY = 4;

int maxX = 7;
int minX = 0;
int maxY = 7;
int minY = 0;


void loop() {

  if(nunchuck1.getJoyX()>170){
    if(valX<maxX)
    valX++;
  } 
  else if (nunchuck1.getJoyX()<100){
    if(valX>minX)
    valX--;
  }

  if(nunchuck1.getJoyY()>170){
    if(valY<maxY)
    valY++;
  } 
  else if (nunchuck1.getJoyY()<100){
    if(valY>minY)
    valY--;
  }
  

  /*
  if(random(-1,1))
  {
    if(random(-1,1))
    {
      valX++;
    }else {
      valX--;
    }
  }
  else {
    if(random(-1,1))
    {
      valY++;
    }else {
      valY--;
    }
  }
  */
  //valX = (nunchuck1.getJoyX()-127)/8;
  //valY = (nunchuck1.getJoyY()-127)/8;
  
  lc.setLed(0,valX,valY,true); 
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
 nunchuck1.printInputs();

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
