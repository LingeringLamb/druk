#include<LiquidCrystal.h>
#define a -1.51922044997230e-06
#define b 0.00275858993083322
#define c -1.55501496673548
#define d 325.645485874563
LiquidCrystal lcd(16,17,23,25,27,29);

void setup() {
  



  lcd.begin( 20, 4 );
}

void loop() 
{
  int temp;  
  double x, y;
  lcd.setCursor(0,0);
  lcd.print("temp = ");
  temp = analogRead(13);  
  lcd.print(temp);
  x=(double)temp;
  y=a*x*x*x + b* x*x +c*x+d;
  lcd.print(y);

  
}
