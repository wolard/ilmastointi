/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "DHT.h"

#include <LiquidCrystal_I2C.h>
//#include "Si7021.h"

//Si7021 si7021;

//#include "Adafruit_Si7021.h"
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd(0x27,20,4);

//Adafruit_Si7021 sensor = Adafruit_Si7021();
// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13
int fanvalue=10;


#define DHTPIN2 3  // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTPIN1 2 
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
void setup()
{
//Serial.begin(9600);


TCCR2B = TCCR2B & B11111000 | B00000110;
lcd.init();                      // initialize the lcd
lcd.backlight();
 //sensor.begin();
//test
  dht2.begin();

  // initialize LED digital pin as an output.
  pinMode(11, OUTPUT);
  analogWrite(11, fanvalue);
}

void loop()
{

  delay(200);
   //Start at character 4 on line 0

  //sisälämpötila
  //float hud1 = (si7021.measureHumidity());
  float hud1 = dht1.readHumidity();
  float h = hud1/100;
  
  //float temp1 = (si7021.getTemperatureFromPreviousHumidityMeasurement());
   float temp1 = dht1.readTemperature();
    float t= temp1+273.15;
  // Read temperature as Celsius

delay(300);
  float hud2 = dht2.readHumidity();
  float h2 = hud2/100;

  float temp2 = dht2.readTemperature();
    float t2 = temp2+273.15;
 float hum=(1320.65/t)*h*pow(10,(7.4475*(t-273.14)/(t-39.44)));
  float hum2=(1320.65/t2)*h2*pow(10,(7.4475*(t2-273.14)/(t2-39.44)));

lcd.setCursor(0,0);



lcd.print("ulko: ");
lcd.print(temp2);
lcd.print("C ");
lcd.print(hud2);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("sisa: ");
lcd.print(temp1);
lcd.print("C ");
lcd.print(hud1);
lcd.print("%");
lcd.setCursor(0,2);
lcd.print("tuuletin:");
  // turn the LED off by making the voltage LOW

int fanpower = map(fanvalue, 0, 255, 0, 100);
lcd.print(fanpower);
lcd.print("%");
if ((hum-hum2>1.5)&&(fanvalue<255))
{
fanvalue++;
analogWrite(11, fanvalue);

}
else if  ((hum-hum2<1.5)&&(fanvalue>10))
{
  fanvalue--;
  analogWrite(11, fanvalue);
}
   // wait for a second

}
