
#include <HCSR04.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
const int LEDBuzzerPin=1;
const int trigPin = 2;
const int echoPin = 3;
 
UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);
void setup(){
lcd.init();
pinMode(LEDBuzzerPin,OUTPUT); 
}
 
void loop(){
lcd.backlight();
lcd.clear(); 
lcd.print("distance = ");
lcd.setCursor(0,1); 
lcd.print(distanceSensor.measureDistanceCm()+1);
lcd.print(" cm");
if((distanceSensor.measureDistanceCm()+1)<3) {
digitalWrite(LEDBuzzerPin,HIGH); // red LED lights up and buzzer starts ringing
}else
{
digitalWrite(LEDBuzzerPin,LOW); // red LED goes out and buzzer stops
}
delay(500);
}
