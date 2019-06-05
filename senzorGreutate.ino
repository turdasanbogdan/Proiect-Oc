// (c) Michael Schoeffler 2017, http://www.mschoeffler.de
#include <HX711_ADC.h> 
#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LiquidCrystal_I2C library
HX711_ADC LoadCell(4, 5); // parameters: dt pin, sck pin<span data-mce-type="bookmark" style="display: inline-block; width: 0px; overflow: hidden; line-height: 0;" class="mce_SELRES_start"></span>
LiquidCrystal_I2C lcd(0x27, 16,2 ); // 0x27 is the i2c address of the LCM1602 IIC v1 module (might differ)
const float ma50;//=6.5;
const float mi50;//=5;
const float ma10;//=4.9;
const float mi10;//=3.5;
const float ma5;//=3.4;
const float mi5;//=2.6;
const float ma1;//=2.55;
const float mi1;//=1;
const float ServoPin=9;
const float Trigger=3;
const float Echo=2;
int sum;
NewPing sonar(Trigger, Echo,30);
Servo servo;

void setup() {
  int sum=0;
  LoadCell.begin(); // start connection to HX711
  LoadCell.start(2000); // load cells gets 2000ms of time to stabilize
  LoadCell.setCalFactor(1); // calibration factor for load cell => strongly dependent on your individual setup
  lcd.init(); // begins connection to the LCD module
  lcd.backlight(); // turns on the backlight
  servo.attach(ServoPin);
}
void loop1()
{
 //LoadCell.start(2000); // load cells gets 2000ms of time to stabilize
  LoadCell.update(); // retrieves data from the load cell
  
  float i = LoadCell.getData(); // get output value
  lcd.setCursor(0, 1); // set cursor to 2nd row
  if(i>mi50&i<ma50) {lcd.print("Moneda de 50"); sum=sum+50;}
    else if(i>mi10&i<ma10) {lcd.print("Moneda de 10"); sum=sum+10;}
     else if(i>mi5&i<ma5) {lcd.print("Moneda de 5"); sum=sum+5;}
       else if(i>mi1&i<ma1) {lcd.print("Moneda de 1"); sum=sum+1;}
  lcd.setCursor(0,0);
  lcd.print("Suma: ");
  lcd.print(sum);
  
}
void loop2()
{
  int cm=sonar.ping_cm();
  servo.write(cm*1000);
  delay(250);
 }
void loop() {
  
  loop1();
  loop2();
  
}
