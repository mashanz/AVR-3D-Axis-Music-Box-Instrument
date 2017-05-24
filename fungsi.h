#include <Arduino.h>

void musicBox(){
  lcd.setCursor(0, 0);
  lcd.print("arah: ");
    if( (compass.heading() >= 90) && (compass.heading() < 135) ){
      lcd.print("UTARA         ");
      lcd.setCursor(0, 1);
      lcd.print("Nada: DO      ");
      n_do();
    }
    else if( (compass.heading() >= 45) && (compass.heading() < 90) ){
      lcd.print("BARAT LAUT    ");
      lcd.setCursor(0, 1);
      lcd.print("Nada: RE      ");
      n_re();
    }
    else if( (compass.heading() >= 0) && (compass.heading() < 45) ){
      lcd.print("BARAT         ");
      lcd.setCursor(0, 1);
      lcd.print("Nada: MI      ");
      n_mi();
    }
    else if( (compass.heading() >= 315) && (compass.heading() < 359) ){
      lcd.print("BARAT DAYA    ");
      lcd.setCursor(0, 1);
      lcd.print("Nada: FA      ");
      n_fa();
    }
    else if( (compass.heading() >= 270) && (compass.heading() < 315) ){
      lcd.print("SELATAN        ");
      lcd.setCursor(0, 1);
      lcd.print("Nada: SO      ");
      n_so();
    }
    else if( (compass.heading() >= 225) && (compass.heading() < 270) ){
      lcd.print("TENGGARA      ");
      lcd.setCursor(0, 1);
      lcd.print("Nada: LA      ");
      n_la();
    }
    else if( (compass.heading() >= 180) && (compass.heading() < 225) ){
      lcd.print("TIMUR         ");
      lcd.setCursor(0, 1);
      lcd.print("Nada: SI      ");
      n_si();
    }
    else if( (compass.heading() >= 135) && (compass.heading() < 180) ){
      lcd.print("TIMUR LAUT    ");
      lcd.setCursor(0, 1);
      lcd.print("Nada: doo     ");
      n_Do();
    }
    else{
      lcd.print("Entahlah      ");
      lcd.setCursor(0, 1);
      lcd.print("Nada: Senyap  ");  
    }
}

void bacaACC(){
  snprintf(report, sizeof(report), "A: %6d %6d %6d    M: %6d %6d %6d",
  compass.a.x, compass.a.y, compass.a.z,
  compass.m.x, compass.m.y, compass.m.z);
  lcd.setCursor(0, 0);
  lcd.print("x:");lcd.print(compass.a.x / 10);lcd.print("   ");
  lcd.setCursor(8, 0);
  lcd.print("y:");lcd.print(compass.a.y / 10);lcd.print("   ");
  lcd.setCursor(0, 1);
  lcd.print("z:");lcd.print(compass.a.z / 10);lcd.print("   ");  
}
void bacaMag(){
  lcd.setCursor(0, 0);
  lcd.print("arah: ");
  lcd.print(compass.heading());
      
}
