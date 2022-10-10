#include <Mouse.h>

// constant pin numbers
int VRx = A0;
int VRy = A1;
int ldr = A2;
int SW = 2;
int led = 7; 

//variables initialized at 0
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int ldr_state = 0;
int mapX = 0;
int mapY = 0;
int i = 0;

// setup function
void setup() {
  Serial.begin(9600); 
  
  pinMode(VRx, INPUT); // x direction of joystick defined as input
  pinMode(VRy, INPUT); // y direction of joystick defined as input
  pinMode(SW, INPUT_PULLUP); // button of joystick defined as pullup input
  pinMode(ldr, INPUT); // ldr defined as input
  pinMode(led, OUTPUT); // power sent to ldr defined as output
}

//loop function
void loop() {
  //variables defined as analog reading of pin
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  ldr_state = analogRead(ldr);
  // variables defined as map position of joystick
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  // turn the ldr power on
  digitalWrite(led, HIGH);
  //if button is pressed, move the scroll wheel based on the up and down movement of the joystick
  if (SW_state == 0){
    Mouse.move(0,0,-mapX/320);
  }
  //if absolute value of mapX or mapY are greater than 60 (to avoid random bugs with sensor readings), move the mouse based on joystick readings
  else if (abs(mapY) > 60 | abs(mapX)>60){
    Mouse.move(-mapY/80,mapX/80);
  }
  //if ldr is covered and counter variable i is greater than 50 (to avoid too many clicks per second), 
  if (ldr_state < 1023 & i >50){
    i = 0;
    // left click if the joystick button is not pressed, right click if the button is pressed.
    if (SW_state == 1){
      Mouse.click();
    }
    else{
      Mouse.click(MOUSE_RIGHT);
    }
  }
  i +=1;
  delay(10);
}
