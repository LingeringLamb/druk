#include <stdlib.h>

//
// Steppers
//
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#ifndef X_CS_PIN
  #define X_CS_PIN         53
#endif

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#ifndef Y_CS_PIN
  #define Y_CS_PIN         49
#endif

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#ifndef Z_CS_PIN
  #define Z_CS_PIN         40
#endif

//
// Limit Switches
//
#define X_MIN_PIN           3
#ifndef X_MAX_PIN
  #define X_MAX_PIN         2
#endif
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#include<LiquidCrystal.h>
#define a -1.51922044997230e-06
#define b 0.00275858993083322
#define c -1.55501496673548
#define d 325.645485874563
LiquidCrystal lcd(16,17,23,25,27,29);


int i = 0;
bool kierunek = 0, kier1 = 0, kier2 = 0, kier3 = 0;
String bufor;
int k1 = 0, k2 = 0, k3 = 0;
bool czy_mam_odp                     =0;

void setup() {
  Serial.begin(115200);

  // X
  
  pinMode (X_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN, LOW);
  pinMode (X_DIR_PIN, OUTPUT);
  //digitalWrite(X_DIR_PIN, HIGH);
  pinMode(X_STEP_PIN, OUTPUT);

  // Y

   pinMode (Y_ENABLE_PIN, OUTPUT);
  digitalWrite(Y_ENABLE_PIN, LOW);
  pinMode (Y_DIR_PIN, OUTPUT);
  //digitalWrite(Y_DIR_PIN, HIGH);
  pinMode(Y_STEP_PIN, OUTPUT);

  // Z

   pinMode (Z_ENABLE_PIN, OUTPUT);
  digitalWrite(Z_ENABLE_PIN, LOW);
  pinMode (Z_DIR_PIN, OUTPUT);
  //digitalWrite(Z_DIR_PIN, HIGH);
  pinMode(Z_STEP_PIN, OUTPUT);

  // KRANCOWKI

  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);

  //wybior kierunku
  digitalWrite(X_DIR_PIN, 0);
  digitalWrite(Y_DIR_PIN, 0);
  digitalWrite(Z_DIR_PIN, 0);

  lcd.begin( 20, 4 );

}

void loop() {
  // Serial.print("a\n");
  
  digitalWrite(X_STEP_PIN, HIGH);
  digitalWrite(Y_STEP_PIN, HIGH);
  digitalWrite(Z_STEP_PIN, HIGH);
  delayMicroseconds(1000);
  if ((digitalRead(X_MAX_PIN) == 0) && (k1 > 0)) 
  {
    digitalWrite(X_STEP_PIN, LOW);
    k1--;
  }
  if ((digitalRead(Y_MAX_PIN) == 0) && (k2 > 0)) 
  {
    digitalWrite(Y_STEP_PIN, LOW);
    k2--;
  }
  if ((digitalRead(Z_MAX_PIN) == 0) && (k3 > 0)) 
  {
    digitalWrite(Z_STEP_PIN, LOW);
    k3--;
  }
  
  delayMicroseconds(1000);
  
  // zmiana kierunku (oscylacje)
  /*i++;
  if ( i > 299 ) 
  {
    i=0;
    kierunek = !kierunek;
    digitalWrite(X_DIR_PIN, kierunek);
    digitalWrite(Y_DIR_PIN, kierunek);
    digitalWrite(Z_DIR_PIN, kierunek);
  }*/
  
  while (Serial.available() > 0)
  {
    bufor = Serial.readStringUntil('\n');
    sscanf(bufor.c_str(), "k1%dk2%dk3%d", &k1, &k2, &k3);
    czy_mam_odp=1;
    //Serial.println(k1);
    //Serial.println(k2);
    //Serial.println(k3);
    
    kier1 = k1 < 0; // wybor kierunku - 1 dol, 0  gora
    k1 = abs(k1); // zmiana minusa na plus, liczba krokow
    digitalWrite(X_DIR_PIN, kier1); // przypisanie kierunku

    kier2 = k2 < 0; // wybor kierunku - 1 dol, 0  gora
    k2 = abs(k2); // zmiana minusa na plus, liczba krokow
    digitalWrite(Y_DIR_PIN, kier2); // przypisanie kierunku

    kier3 = k3 < 0; // wybor kierunku - 1 dol, 0  gora
    k3 = abs(k3); // zmiana minusa na plus, liczba krokow
    digitalWrite(Z_DIR_PIN, kier3); // przypisanie kierunku

    


  }

  if(k1==0 && k2==0 && k3==0 && czy_mam_odp==1)
  {
    Serial.println("ok");
    czy_mam_odp=0;
  }
  //Serial.println(digitalRead(X_MAX_PIN));

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
