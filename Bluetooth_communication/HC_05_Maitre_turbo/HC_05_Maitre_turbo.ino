#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial ArduinoEsclave(10, 11);
LiquidCrystal_I2C lcd (0x27, 20, 4);

String data = "";

const int Btn_etincelle = 8;
int etat_Btn_etincelle;

const int Btn_air = 7;
int etat_Btn_air;

int Ptr_gaz;
int Ptr_gaz_deg;

void setup() {

  ArduinoEsclave.begin(9600);

  lcd.init();

  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("ALLU:");
  lcd.setCursor(5, 0);
  lcd.print("INI");
  lcd.setCursor(9, 0);
  lcd.print("AIR:");
  lcd.setCursor(13, 0);
  lcd.print("INI");
  lcd.setCursor(0, 1);
  lcd.print("ANGLE GAZ : ");
  lcd.setCursor(12, 1);
  lcd.print("INI");

  pinMode (Btn_etincelle, INPUT_PULLUP);
  pinMode (Btn_air, INPUT_PULLUP);

}

void loop() {

  // LECTURE DES COMMANDES
  etat_Btn_etincelle = digitalRead(Btn_etincelle);
  etat_Btn_air = digitalRead(Btn_air);
  Ptr_gaz = analogRead(A0);
  Ptr_gaz_deg = map(Ptr_gaz, 0, 1023, 0, 90);
  
  lcd.setCursor(12, 1);
  lcd.print("   ");
  lcd.setCursor(12, 1);
  lcd.print(Ptr_gaz_deg);

  // ENVOI DES DONNEES A L'ESCLAVE

  // ETINCELLE
  if (etat_Btn_etincelle == LOW) {
    data = "101"; // Etincelle ON
    lcd.setCursor(5, 0);
    lcd.print("ON ");
  }
  else {
    data = "102"; // Etincelle OFF
    lcd.setCursor(5, 0);
    lcd.print("OFF ");
  }

  data += ":";
  delay(100);


  // AIR
  if (etat_Btn_air == LOW) {
    data += "203"; // Air ON
    lcd.setCursor(13, 0);
    lcd.print("ON ");
  }
  else {
    data += "204"; // Air OFF
    lcd.setCursor(13, 0);
    lcd.print("OFF ");
  }

  data += ":";
  delay(100);

  // GAZ
  if (Ptr_gaz_deg == 0) {
    data += "300";
  }
  else if (Ptr_gaz_deg == 1) {
    data += "301";
  }
  else if (Ptr_gaz_deg == 2) {
    data += "302";
  }
  else if (Ptr_gaz_deg == 3) {
    data += "303";
  }
  else if (Ptr_gaz_deg == 4) {
    data += "304";
  }
  else if (Ptr_gaz_deg == 5) {
    data += "305";
  }
  else if (Ptr_gaz_deg == 6) {
    data += "306";
  }
  else if (Ptr_gaz_deg == 7) {
    data += "307";
  }
  else if (Ptr_gaz_deg == 8) {
    data += "308";
  }
  else if (Ptr_gaz_deg == 9) {
    data += "309";
  }
  else if (Ptr_gaz_deg == 10) {
    data += "310";
  }
  else if (Ptr_gaz_deg == 11) {
    data += "311";
  }
  else if (Ptr_gaz_deg == 12) {
    data += "312";
  }
  else if (Ptr_gaz_deg == 13) {
    data += "313";
  }
  else if (Ptr_gaz_deg == 14) {
    data += "314";
  }
  else if (Ptr_gaz_deg == 15) {
    data += "315";
  }
  else if (Ptr_gaz_deg == 16) {
    data += "316";
  }
  else if (Ptr_gaz_deg == 17) {
    data += "317";
  }
  else if (Ptr_gaz_deg == 18) {
    data += "318";
  }
  else if (Ptr_gaz_deg == 19) {
    data += "319";
  }
  else if (Ptr_gaz_deg == 20) {
    data += "320";
  }
  else if (Ptr_gaz_deg == 21) {
    data += "321";
  }
  else if (Ptr_gaz_deg == 22) {
    data += "322";
  }
  else if (Ptr_gaz_deg == 23) {
    data += "323";
  }
  else if (Ptr_gaz_deg == 24) {
    data += "324";
  }
  else if (Ptr_gaz_deg == 25) {
    data += "325";
  }
  else if (Ptr_gaz_deg == 26) {
    data += "326";
  }
  else if (Ptr_gaz_deg == 27) {
    data += "327";
  }
  else if (Ptr_gaz_deg == 28) {
    data += "328";
  }
  else if (Ptr_gaz_deg == 29) {
    data += "329";
  }
  else if (Ptr_gaz_deg == 30) {
    data += "330";
  }
  else if (Ptr_gaz_deg == 31) {
    data += "331";
  }
  else if (Ptr_gaz_deg == 32) {
    data += "332";
  }
  else if (Ptr_gaz_deg == 33) {
    data += "333";
  }
  else if (Ptr_gaz_deg == 34) {
    data += "334";
  }
  else if (Ptr_gaz_deg == 35) {
    data += "335";
  }
  else if (Ptr_gaz_deg == 36) {
    data += "336";
  }
  else if (Ptr_gaz_deg == 37) {
    data += "337";
  }
  else if (Ptr_gaz_deg == 38) {
    data += "338";
  }
  else if (Ptr_gaz_deg == 39) {
    data += "339";
  }
  else if (Ptr_gaz_deg == 40) {
    data += "340";
  }
  else if (Ptr_gaz_deg == 41) {
    data += "341";
  }
  else if (Ptr_gaz_deg == 42) {
    data += "342";
  }
  else if (Ptr_gaz_deg == 43) {
    data += "343";
  }
  else if (Ptr_gaz_deg == 44) {
    data += "344";
  }
  else if (Ptr_gaz_deg == 45) {
    data += "345";
  }
  else if (Ptr_gaz_deg == 46) {
    data += "346";
  }
  else if (Ptr_gaz_deg == 47) {
    data += "347";
  }
  else if (Ptr_gaz_deg == 48) {
    data += "348";
  }
  else if (Ptr_gaz_deg == 49) {
    data += "349";
  }
  else if (Ptr_gaz_deg == 50) {
    data += "350";
  }
  else if (Ptr_gaz_deg == 51) {
    data += "351";
  }
  else if (Ptr_gaz_deg == 52) {
    data += "352";
  }
  else if (Ptr_gaz_deg == 53) {
    data += "353";
  }
  else if (Ptr_gaz_deg == 54) {
    data += "354";
  }
  else if (Ptr_gaz_deg == 55) {
    data += "355";
  }
  else if (Ptr_gaz_deg == 56) {
    data += "356";
  }
  else if (Ptr_gaz_deg == 57) {
    data += "357";
  }
  else if (Ptr_gaz_deg == 58) {
    data += "358";
  }
  else if (Ptr_gaz_deg == 59) {
    data += "359";
  }
  else if (Ptr_gaz_deg == 60) {
    data += "360";
  }
  else if (Ptr_gaz_deg == 61) {
    data += "361";
  }
  else if (Ptr_gaz_deg == 62) {
    data += "362";
  }
  else if (Ptr_gaz_deg == 63) {
    data += "363";
  }
  else if (Ptr_gaz_deg == 64) {
    data += "364";
  }
  else if (Ptr_gaz_deg == 65) {
    data += "365";
  }
  else if (Ptr_gaz_deg == 66) {
    data += "366";
  }
  else if (Ptr_gaz_deg == 67) {
    data += "367";
  }
  else if (Ptr_gaz_deg == 68) {
    data += "368";
  }
  else if (Ptr_gaz_deg == 69) {
    data += "369";
  } else if (Ptr_gaz_deg == 70) {
    data += "370";
  } else if (Ptr_gaz_deg == 71) {
    data += "371";
  } else if (Ptr_gaz_deg == 72) {
    data += "372";
  } else if (Ptr_gaz_deg == 73) {
    data += "373";
  } else if (Ptr_gaz_deg == 74) {
    data += "374";
  } else if (Ptr_gaz_deg == 75) {
    data += "375";
  } else if (Ptr_gaz_deg == 76) {
    data += "376";
  } else if (Ptr_gaz_deg == 77) {
    data += "377";
  } else if (Ptr_gaz_deg == 78) {
    data += "378";
  } else if (Ptr_gaz_deg == 79) {
    data += "379";
  } else if (Ptr_gaz_deg == 80) {
    data += "380";
  } else if (Ptr_gaz_deg == 81) {
    data += "381";
  } else if (Ptr_gaz_deg == 82) {
    data += "382";
  } else if (Ptr_gaz_deg == 83) {
    data += "383";
  } else if (Ptr_gaz_deg == 84) {
    data += "384";
  } else if (Ptr_gaz_deg == 85) {
    data += "385";
  } else if (Ptr_gaz_deg == 86) {
    data += "386";
  } else if (Ptr_gaz_deg == 87) {
    data += "387";
  } else if (Ptr_gaz_deg == 88) {
    data += "388";
  } else if (Ptr_gaz_deg == 89) {
    data += "389";
  } else if (Ptr_gaz_deg == 90) {
    data += "390";
  }
  else {
    data += "666";
  }
  delay(100);

  ArduinoEsclave.println(data);
  data = "";
  delay(100);
}
