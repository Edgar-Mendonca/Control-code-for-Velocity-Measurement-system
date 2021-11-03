//Developed by Edgar Mendonca
//Set distance between the two sensors: 50mm

#include<Wire.h>                                //I2C Communication library
#include <LiquidCrystal_I2C.h>                 //LCD with I2C library
LiquidCrystal_I2C lcd(0x27,16,2);             

int S1 = A2; //Analog Pin 2
int S2 = A3; //Analog Pin3

int val1; //Value Store fn1
int val2; //value Store fn2

int threshold;
unsigned long time1, time2;
float Time, Speed;


byte customChar[] = {
  B00000,
  B00100,
  B01010,
  B10001,
  B10001,
  B10001,
  B11111,
  B00000
};

void setup()
{
Serial.begin(9600);
pinMode (S1, INPUT);
pinMode (S2, INPUT);

val1 = digitalRead(S1);
val2 = digitalRead(S2);

threshold = (((val1+val2)/2)+45);

lcd.init(); 
lcd.backlight(); 
lcd.setCursor(0, 0);
lcd.clear();

lcd.createChar(0, customChar);
lcd.home();
lcd.write(0);
lcd.setCursor(1,0);
lcd.print("t=");

lcd.setCursor(0, 1);
lcd.print("V =");


}
void loop()
{
val1 = analogRead(S1);
val2 = analogRead(S2);

while(val1<=threshold)
{
  val1 = analogRead(S1);
}

while(val1>threshold)
{
  time1 = micros();
  val1 = analogRead(S1);
}

while(val2<=threshold)
{
 val2 = analogRead(S2);
}

while(val2>threshold)
{
  time2 = micros();
  val2 = analogRead(S2);
}

Time = time2 - time1;
Speed = (50000/Time);      //50mm - Distance between two sensors

Serial.print(Time);
Serial.println(Speed);

lcd.setCursor(3,0);
lcd.print(Time);
lcd.setCursor(12,0);
lcd.print("us");
lcd.setCursor(3,1);
lcd.print(Speed);
lcd.setCursor(8,1);
lcd.print("m/s");

}
