#include <LiquidCrystal.h>
#include <Wire.h>
#include "LSM303.h"
// SETUP ============================================
// Set up speaker on a PWM pin (digital 9, 10 or 11)
int speakerOut = 5;
int DEBUG = 1;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
LSM303 compass;
//LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768};
char report[80];
#include "tune.h"
#include "fungsi.h"
void setup() {
  attachInterrupt(1, doremi, RISING);
  pinMode(speakerOut, OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
  compass.setTimeout(50);
  if (!compass.init()){
      lcd.begin(16, 2);
      lcd.setCursor(0, 1);
      lcd.print("Failed to detect the compass.");
      Serial.println(F("Failed to detect the compass."));
      delay(20);
  }
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop() {
  digitalWrite(3,LOW);
  compass.enableDefault();
  compass.read();
  //bacaACC();
  if((compass.a.y / 10) <= -1000){
    //digitalWrite(3,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("  PLAY   MUSIC  ");
    lcd.setCursor(0, 1);
    lcd.print("================");
    if(lagu == 0){gundulpacul();}
    else if (lagu == 1){ibukartini();}
    else if (lagu == 2){durun();}
    else{lagu = 0;}
  }else if((compass.a.x / 10) >= 1000){
    //digitalWrite(3,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("      PAUSE     ");
    lcd.setCursor(0, 1);
    lcd.print("================");
  }else{
    digitalWrite(3,LOW);
    musicBox();
  }
  if(((compass.a.x / 10) <= 0)&&((compass.a.y / 10) <= 0)&&((compass.a.z / 10) <= 0)){
    digitalWrite(3,HIGH);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("GANTI GAN");
    delay(1000);
  }
}
