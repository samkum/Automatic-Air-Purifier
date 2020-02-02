 
 #include <LiquidCrystal.h>
int ledPower=12;

float voMeasured=0;
float calcVoltage=0;
float dustDensity=0;
int measurePin=A5;
int fan_speed;
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define pwm 9
#define xPin 10
void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(ledPower,OUTPUT);
  pinMode(xPin,OUTPUT);
  pinMode(pwm,OUTPUT);
  digitalWrite(xPin, LOW);
}
void loop()
{  
  digitalWrite(ledPower,LOW);
 lcd.clear();
  voMeasured = analogRead(measurePin);

  delayMicroseconds(400);
  digitalWrite(ledPower,HIGH);
  
  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1;

  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }

  Serial.println("Raw Signal Value (0-1023):");
  Serial.println(voMeasured);
  //fan_speed=255;

  
   if(voMeasured>100)
  {
 fan_speed=voMeasured/4;
 analogWrite(pwm,fan_speed);
 digitalWrite(xPin,LOW);
  }
 else
 {
  digitalWrite(xPin,HIGH);
  fan_speed=0;
 }
 Serial.print("fan speed: ");
 Serial.println(fan_speed);
  Serial.println("Voltage:");
  Serial.println(calcVoltage);
  lcd.setCursor(0,0);
  lcd.print("Dust Density:");
  lcd.print(dustDensity);
  lcd.setCursor(0,1);
  lcd.print("fan speed:");
  lcd.print(fan_speed);
  Serial.println("Dust Density:");
  Serial.println(dustDensity);

  delay(1000);
}
