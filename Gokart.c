#include <SimpleTimer.h> //   http://playground.arduino.cc/Code/SimpleTimer   
#include <FancyLED.h> //  http://playground.arduino.cc/Code/SimpleTimer 
#include <Servo.h> // default arduino servo library
#include <UTFT.h> //  http://playground.arduino.cc/Code/SimpleTimer >

extern uint8_t BigFont[];
const int throttlePin = A11; 
Servo esc;
const int escPWRSwitch=16;
const int escPWR=A13;
 volatile byte revolutions;
 unsigned int rpm;
 unsigned long timeold;
float voltage;
const int voltagePin=A9;
float current;
const int currentPin=A10;
UTFT myGLCD(ITDB32S,38,39,40,41);
long previousMillis = 0;  
long interval = 300;
SimpleTimer timer;
FancyLED left_1 = FancyLED(8, HIGH);
FancyLED left_2 = FancyLED(6, HIGH);
FancyLED right_1 = FancyLED(11, HIGH);
FancyLED right_2 = FancyLED(7, HIGH);
FancyLED brake_1 = FancyLED(3, HIGH);
FancyLED brake_2 = FancyLED(10, HIGH);
FancyLED brake_ind = FancyLED(44, HIGH);
const int joystick = A14;
int gear = 0;
int throttle = 34;
long indicatorInterval;
int leftIndicatorF;
int rightIndicatorF;
 // R - 11,7 (L - 8,6)
int indicatorState;
void setup()
{
esc.attach(45);
 pinMode(escPWR, OUTPUT);
 pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
 pinMode(A3, OUTPUT);
 pinMode(A4, OUTPUT);
 pinMode(A5, OUTPUT);
 pinMode(A6, OUTPUT);
 pinMode(A12, OUTPUT);</p><p> digitalWrite(escPWR, HIGH);
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.setFont(BigFont);
left_1.turnOff();
left_2.turnOff();
right_1.turnOff();
right_2.turnOff();
leftIndicatorF = timer.setInterval(450, leftIndicatorFunct);
rightIndicatorF = timer.setInterval(450, rightIndicatorFunct);
timer.disable(rightIndicatorF);
timer.disable(leftIndicatorF);</p><p>  myGLCD.clrScr();
  myGLCD.fillScr(255, 0, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  
  ///// If override button is held during startup, enter "basic mode" - only throttle and display are functional
  int basic_test = digitalRead(14);
  if (basic_test == HIGH)
  {
    myGLCD.print("BASIC MODE", CENTER, CENTER);
        pinMode(13, OUTPUT);</p><p>    digitalWrite(13, HIGH);
    basic();
  }
}
 
void loop()
{
//////////
  current = ((analogRead(currentPin)));
  /////////
  voltage = (analogRead(voltagePin)) * (0.02441)  ;
//////////
 if (digitalRead(escPWRSwitch) == HIGH) {
   digitalWrite(escPWR, LOW);
}
  else {
   digitalWrite(escPWR, HIGH);
}
///////////</p><p>throttle = analogRead(throttlePin);
throttle = map(throttle, 0, 1023, 0, 179);</p><p>if (gear > 0)
{
  if (throttle > 35)
  {
throttle = map(throttle, 0, 179, 35, ((140 / 8) * gear)+40);
  }
 
}
else if (gear == 0)
{
throttle = 34;
}
else if (gear == -1)
{
throttle = 34;</p><p>}
else if (gear == -2)
{
throttle = 0;
}</p><p>if (analogRead(A8) > 1000)
{
esc.write(throttle);
}
else
{
esc.write(34);
}</p><p>//////////////
    unsigned long currentMillis = millis();
 int joystick_val = analogRead(joystick);</p><p>  if(currentMillis - previousMillis > interval) {
if (joystick_val < 1000)
{
if (830 < joystick_val)
{
  //up
 
  
  
  if (gear < 8 && gear > 0)
  {
    
    gear++;
  }
      else if (gear != 8)
  {
    gear = 1;
  }</p><p>}
else if (680 < joystick_val)
{
  //down
  if (gear > 1)
  {
  gear--;
  }
}
else if (350 < joystick_val)
{
  //left (reverse)
  gear = -1;
}</p><p>else if (70 < joystick_val)
{
  //right
  if (gear == 0)
  {
  gear = -2;
  }
else {
  gear = 0;
}
}}
  }
//////////////
if (gear == 1)
{
   digitalWrite(A3, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A6, LOW);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A12, LOW);
  digitalWrite(A5, LOW);</p><p>}
else if (gear == 2)
{
    digitalWrite(A3, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A6, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A12, LOW);
  digitalWrite(A5, HIGH);</p><p>}
else if (gear == 3)
{
  digitalWrite(A3, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A6, HIGH);
  digitalWrite(A4, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A12, HIGH);
  digitalWrite(A5, HIGH);</p><p>}
else if (gear == 4)
{
  digitalWrite(A3, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A6, HIGH);
  digitalWrite(A4, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A12, HIGH);
  digitalWrite(A5, HIGH);</p><p>}
else if (gear == 5)
{
  digitalWrite(A3, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A6, HIGH);
  digitalWrite(A4, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A12, HIGH);
  digitalWrite(A5, LOW);</p><p>}
else if (gear == 6)
{
  digitalWrite(A3, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A6, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A12, HIGH);
  digitalWrite(A5, LOW);</p><p>}
else if (gear == 7)
{
  digitalWrite(A3, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A6, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A12, HIGH);
  digitalWrite(A5, HIGH);</p><p>}
else if (gear == 8)
{
  digitalWrite(A3, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A6, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A12, HIGH);
  digitalWrite(A5, HIGH);</p><p>}
else if (gear == 0)
{
  digitalWrite(A3, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A6, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A12, HIGH);
  digitalWrite(A5, LOW);</p><p>}
else if (gear == -2)
{
  digitalWrite(A3, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A6, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A12, LOW);
  digitalWrite(A5, HIGH);</p><p>}
else if (gear == -1)
{
  digitalWrite(A3, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A6, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A12, HIGH);
  digitalWrite(A5, HIGH);</p><p>}</p><p>//////////////
if (analogRead(A15) > 1000)
{
  digitalWrite(12, HIGH);
    digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(9, HIGH);
}
else if (analogRead(A15) < 10)
{
  digitalWrite(12, LOW);
    digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(9, LOW);
}
else
{
  analogWrite(12, 128);
    analogWrite(4, 128);
  analogWrite(5, 128);
  analogWrite(9, 128);
}</p><p>//////////////
if (digitalRead(15) == HIGH)
{
  timer.enable(rightIndicatorF);
  timer.enable(leftIndicatorF);
  indicatorState = 1;
}
else if (timer.isEnabled(leftIndicatorF) && timer.isEnabled(rightIndicatorF) && digitalRead(15) == LOW)
{
    timer.disable(rightIndicatorF);
  timer.disable(leftIndicatorF);
  left_1.turnOff();
left_2.turnOff();
right_1.turnOff();
right_2.turnOff();
indicatorState = 0;
}
else if ((analogRead(A7) > 1000 || analogRead(A7) < 10) && indicatorInterval == 0)
{
  indicatorInterval = millis();
}</p><p>if (millis() - indicatorInterval > 250 && indicatorInterval != 0)
{
if (analogRead(A7) > 990)
{
  
  timer.toggle(leftIndicatorF);
  if (!timer.isEnabled(leftIndicatorF))
   {
    left_1.turnOff();
   left_2.turnOff();
   indicatorState = 0;
   }
   else
   {  indicatorState = 2;
   }
  timer.disable(rightIndicatorF);
right_1.turnOff();
right_2.turnOff();</p><p>}
else if (analogRead(A7) < 30)
{
 
  timer.toggle(rightIndicatorF);</p><p>   if (!timer.isEnabled(rightIndicatorF))
   {
    right_1.turnOff();
    right_2.turnOff();
      indicatorState = 0;</p><p>   }
     else
   {  indicatorState = 3;
   }
  timer.disable(leftIndicatorF);
    left_1.turnOff();
left_2.turnOff();</p><p>}
indicatorInterval = 0;
}
timer.run();
//////////////
if (throttle < 35 || digitalRead(16) == LOW || analogRead(A8) < 1000)
{
  brake_1.turnOn();
  brake_2.turnOn();
  brake_ind.turnOn();
}
else
{
    brake_1.turnOff();
  brake_2.turnOff();
    brake_ind.turnOff();</p><p>}
////////////</p><p>  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;   
  myGLCD.printNumF(voltage, 3, CENTER, 10);
  if (digitalRead(16) == HIGH)
  {
  myGLCD.print("ESC ON ", CENTER, 40);
  }
  else
  {
      myGLCD.print("ESC OFF", CENTER, 40);
  }
  if (analogRead(A8) > 1000)
  {
      myGLCD.print("ACTIVE", CENTER, 70);
  }
  else
  {
      myGLCD.print("      ", CENTER, 70);
  }
  if (analogRead(A15) > 1000)
  {
      myGLCD.print("HEADLIGHTS 100%", CENTER, 100);
  }
  else if (analogRead(A15) < 10)
  {
   myGLCD.print("HEADLIGHTS OFF ", CENTER, 100);
  }
  else
  {
          myGLCD.print("HEADLIGHTS 50% ", CENTER, 100);
  }
  /////////
  if (indicatorState == 1)
  {
          myGLCD.print("HAZARDS", CENTER, 170);
          
  }
  else if (indicatorState == 2)
  {
          myGLCD.print("<------", CENTER, 170);
  }
  else if (indicatorState == 3)
  {
          myGLCD.print("------>", CENTER, 170);
  }
    else if (indicatorState == 0)
  {
          myGLCD.print("       ", CENTER, 170);
  }
  if (voltage < 18.5)
  {
              myGLCD.print("LV WARNING", CENTER, 200);
  }
  else
  {
                  myGLCD.print("          ", CENTER, 200);
  }
  
  myGLCD.printNumI(throttle, CENTER, 140, 3);
    myGLCD.printNumI(gear, CENTER, 240, 3);</p><p>  myGLCD.printNumF(current, 3, CENTER, 280);
  }
  ////////////
}</p><p>void leftIndicatorFunct() 
{
  left_1.toggle();
  left_2.toggle();
}</p><p>void rightIndicatorFunct() 
{
  right_1.toggle();
  right_2.toggle();
}</p><p>void basic() {
  //////basic mode for testing purpose
   digitalWrite(escPWR, LOW);</p><p>  while (true)
  {
    throttle = analogRead(throttlePin);</p><p>throttle = map(throttle, 0, 1023, 0, 179);
  myGLCD.printNumI(throttle, CENTER, 140, 3);</p><p>esc.write(throttle);
  }
}</p>