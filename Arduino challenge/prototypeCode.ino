#include <Servo.h>
#include <LedControl.h>

int lever;
int preLever=1;
int preSv=145;
Servo mSv;

int DIN = 10;
int CS =  9;
int CLK = 8;
LedControl lc=LedControl(DIN,CLK,CS,0);

int num=-1;
int row=0;
int column=0;
byte go[8] ={0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff};

void setup() {
  pinMode(3, OUTPUT);
  digitalWrite(3, 1);
  
  pinMode(5,INPUT);
  mSv.attach(6);
  mSv.write(0);
  Serial.begin(9600);

  lc.shutdown(0,false);       
  lc.setIntensity(0,5);
  lc.clearDisplay(0);    
  
  digitalWrite(5, 1);

}

void loop() {

  lever=digitalRead(5);
  Serial.print(lever);
  if(preLever==1 && lever==0){
    lc.setRow(0,row,go[column]);
    if(mSv.read()==0){
        mSv.write(145);
        num++;
        row=num/8;
        column=(num%8);
      }
     else if(mSv.read()==145){
        mSv.write(0);
        num++;
        row=num/8;
        column=(num%8);
      }
     preSv=mSv.read();
    }
  preLever=lever;
  delay(50);
}
