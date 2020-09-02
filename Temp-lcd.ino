#include <LiquidCrystal.h>
#include <dht.h>
 
LiquidCrystal lcd(9, 10, 5, 7, 6, 8);
int greenPin = A5;
dht sensor;
 
void setup()
{
  lcd.begin(16,2); //16 by 2 character display
}
 
void loop()
{
  delay(1000); //wait a sec (recommended for DHT11)
  sensor.read11(greenPin);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humidity = ");
  lcd.print(sensor.humidity);
  lcd.setCursor(0,1);
  lcd.print("Temp = ");
  lcd.print(sensor.temperature);

}  
