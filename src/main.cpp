#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>

#define DELAY            5  // Delay per loop in ms
#define button           7  // Button to switch modes (optional)

int counter = 0;
bool buttonPressed = false;

void buttonPress();
void doEncoderA();
void doEncoderB();
void doEncoderC();
void doEncoderD();

 enum PinAssignments
 {
  encoderPinA = 1,
  encoderPinB = 0,
  encoderPinC = 2,
  encoderPinD = 3,
 
 };
//This is up to your pin wiring
 
 int encoderPos[] = {0,0};
 static boolean rotating[] = {false,false};
 
 boolean A_set = false;              
 boolean B_set = false;
 boolean C_set = false;              
 boolean D_set = false;
 
void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(button), buttonPress, RISING); // Use interrupt for button press
  Keyboard.begin();
 
  pinMode(4, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderPinC, INPUT_PULLUP);
  pinMode(encoderPinD, INPUT_PULLUP);
 
  attachInterrupt(0, doEncoderC, CHANGE);
  attachInterrupt(1, doEncoderD, CHANGE);
 
  attachInterrupt(2, doEncoderA, CHANGE);
  attachInterrupt(3, doEncoderB, CHANGE);
 
}
 
void loop() {
  
  if(digitalRead(4)==LOW){
    Keyboard.press('a');
  }
  if(digitalRead(4)==HIGH){
    Keyboard.release('a');
  }
  if(digitalRead(A0)==LOW){
    Keyboard.press('b');
  }
  if(digitalRead(A0)==HIGH){
    Keyboard.release('b');
  }
  if(digitalRead(A1)==LOW){
    Keyboard.press('c');
  }
  if(digitalRead(A1)==HIGH){
    Keyboard.release('c');
  }
  if(digitalRead(A2)==LOW){
    Keyboard.press('d');
  }
  if(digitalRead(A2)==HIGH){
    Keyboard.release('d');
  }
  if(digitalRead(A3)==LOW){
    Keyboard.press('i');
  }
  if(digitalRead(A3)==HIGH){
    Keyboard.release('i');
  }
  if(digitalRead(A4)==LOW){
    Keyboard.press('f');
  }
  if(digitalRead(A4)==HIGH){
    Keyboard.release('f');
  }
  if(digitalRead(A5)==LOW){
      Keyboard.press('g');
  }
  if(digitalRead(A5)==HIGH){
    Keyboard.release('g');
  }

  //Encoder Reset
  for(int i=0;i<=1;i++)
  {
    rotating[i] = true;
    if (encoderPos[i] != 0)
    {
      if(i==0)  Mouse.move(encoderPos[i],0,0);
      if(i==1)  Mouse.move(0,encoderPos[i],0);
 
      encoderPos[i] = 0;
    }
  }
 
  delay(DELAY);
}


void doEncoderA()
{
  if( digitalRead(encoderPinA) != A_set )
  {  
    A_set = !A_set;

    if ( A_set && !B_set ){
      if(counter == 0){
        encoderPos[1] += 15;
        rotating[1] = false;  
      } else {
        encoderPos[0] += 15;
        rotating[0] = false;  
      }
    }
  }
}
 
void doEncoderB()
{
 
  if( digitalRead(encoderPinB) != B_set ) {
    B_set = !B_set;

    if( B_set && !A_set ){
      if(counter == 0){
        encoderPos[1] -= 15;
        rotating[1] = false;
      } else {
          encoderPos[0] -= 15;
          rotating[0] = false;
      }
   }
  }
}
 
void doEncoderC()
{
  if( digitalRead(encoderPinC) != C_set )
  {  
    C_set = !C_set;
 
    if ( C_set && !D_set ){
      if(counter == 0){
        encoderPos[0] -= 15;
        rotating[0] = false;
      } else {
        encoderPos[0] -= 15;
        rotating[1] = false;
      }
    }
  }
}
 
void doEncoderD()
{
  if( digitalRead(encoderPinD) != D_set ) {
    D_set = !D_set;
 
    if( D_set && !C_set ){
      if(counter == 0){
        encoderPos[0] += 15;
        rotating[0] = false;
      } else {
        encoderPos[0] += 15;
        rotating[1] = false;
      }
    }
  }
}

// button function to check if the button was pressed (optional to switch between modes)
void buttonPress()
{
   if (!buttonPressed)
   {
      counter++;
      buttonPressed = true;
   }

   delay(500); // Debouncing delay
   buttonPressed = false;
   if (counter >= 2)
   {
     counter = 0;
   }
// Serial.println(counter);
}