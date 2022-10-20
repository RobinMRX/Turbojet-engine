#include <SoftwareSerial.h>
#include <Servo.h>  // on inclut la bibliothèque pour piloter un servomoteur

SoftwareSerial ArduinoMaitre(10, 11);
Servo servoAir;

String msg;

const int Etincelle = 2;

const int Pot = A0;
int val_pot;
int val_pot_deg;

int motor_O = 8; // Sens de l'ouverture de la vanne. (IN?)
int motor_F = 9; // Sens de la fermeture de la vanne. (IN?)
int enablePin = 5;

const int BP_pos_0 = 4;
int etat_BP_pos_0;

int data_etincelle;
int data_air;
int data_gaz;

void setup() {

  ArduinoMaitre.begin(9600);

  servoAir.attach(3);
  servoAir.write(0);

  pinMode (Etincelle, OUTPUT);
  digitalWrite (Etincelle, LOW);

  pinMode (Pot, INPUT);

  pinMode(motor_O, OUTPUT);
  pinMode(motor_F, OUTPUT);
  pinMode(enablePin, OUTPUT);

  pinMode (BP_pos_0, INPUT_PULLUP);

}

void verin_action (int capteur, int commande) {

  while (capteur < commande) {
    digitalWrite(motor_O, HIGH);
    digitalWrite(motor_F, LOW);

    val_pot_deg = analogRead(A0);
    capteur = map(val_pot_deg, 0, 1023, 0, 415);

  }

  while (capteur > commande) {
    digitalWrite(motor_O, LOW);
    digitalWrite(motor_F, HIGH);

    val_pot_deg = analogRead(A0);
    capteur = map(val_pot_deg, 0, 1023, 0, 415);
  }
}

void loop() {

  // LECTURE DES DATA
  LectureMaitre();

  val_pot = analogRead(Pot);
  val_pot_deg = map(val_pot, 0, 1023, 0, 415);

  analogWrite (enablePin, 255);
  digitalWrite(motor_O, HIGH);
  digitalWrite(motor_F, HIGH);

  // ACTION
  if (msg != "") {

    char Data[msg.length() + 1];
    msg.toCharArray(Data, msg.length() + 1);

    sscanf(Data, "%03d:%03d:%03d", &data_etincelle, &data_air, &data_gaz);

  }

  // ETINCELLE
  if (data_etincelle == 101) {
    digitalWrite(Etincelle, HIGH);
  }
  else if (data_etincelle == 102) {
    digitalWrite(Etincelle, LOW);
  }

  // AIR
  if (data_air == 203) {
    servoAir.write(180);
  }
  else if (data_air == 204) {
    servoAir.write(0);
  }

  // GAZ
  if (data_gaz == 300) {
    etat_BP_pos_0 = digitalRead(BP_pos_0);
    while (etat_BP_pos_0 == HIGH ) {
      digitalWrite(motor_O, LOW);
      digitalWrite(motor_F, HIGH);

      etat_BP_pos_0 = digitalRead(BP_pos_0);
    }
  }
  if (data_gaz == 301) {
    verin_action (val_pot_deg, 1);
  } else if (data_gaz == 302) {
    verin_action (val_pot_deg, 2);
  } else if (data_gaz == 303) {
    verin_action (val_pot_deg, 3);
  } else if (data_gaz == 304) {
    verin_action (val_pot_deg, 4);
  } else if (data_gaz == 305) {
    verin_action (val_pot_deg, 5);
  } else if (data_gaz == 306) {
    verin_action (val_pot_deg, 6);
  } else if (data_gaz == 307) {
    verin_action (val_pot_deg, 7);
  } else if (data_gaz == 308) {
    verin_action (val_pot_deg, 8);
  } else if (data_gaz == 309) {
    verin_action (val_pot_deg, 9);
  } else if (data_gaz == 310) {
    verin_action (val_pot_deg, 10);
  } else if (data_gaz == 311) {
    verin_action (val_pot_deg, 11);
  } else if (data_gaz == 312) {
    verin_action (val_pot_deg, 12);
  } else if (data_gaz == 313) {
    verin_action (val_pot_deg, 13);
  } else if (data_gaz == 314) {
    verin_action (val_pot_deg, 14);
  } else if (data_gaz == 315) {
    verin_action (val_pot_deg, 15);
  } else if (data_gaz == 316) {
    verin_action (val_pot_deg, 16);
  } else if (data_gaz == 317) {
    verin_action (val_pot_deg, 17);
  } else if (data_gaz == 318) {
    verin_action (val_pot_deg, 18);
  } else if (data_gaz == 319) {
    verin_action (val_pot_deg, 19);
  } else if (data_gaz == 320) {
    verin_action (val_pot_deg, 20);
  } else if (data_gaz == 321) {
    verin_action (val_pot_deg, 21);
  } else if (data_gaz == 322) {
    verin_action (val_pot_deg, 22);
  } else if (data_gaz == 323) {
    verin_action (val_pot_deg, 23);
  } else if (data_gaz == 324) {
    verin_action (val_pot_deg, 24);
  } else if (data_gaz == 325) {
    verin_action (val_pot_deg, 25);
  } else if (data_gaz == 326) {
    verin_action (val_pot_deg, 26);
  } else if (data_gaz == 327) {
    verin_action (val_pot_deg, 27);
  } else if (data_gaz == 328) {
    verin_action (val_pot_deg, 28);
  } else if (data_gaz == 329) {
    verin_action (val_pot_deg, 29);
  } else if (data_gaz == 330) {
    verin_action (val_pot_deg, 30);
  } else if (data_gaz == 331) {
    verin_action (val_pot_deg, 31);
  } else if (data_gaz == 332) {
    verin_action (val_pot_deg, 32);
  } else if (data_gaz == 333) {
    verin_action (val_pot_deg, 33);
  } else if (data_gaz == 334) {
    verin_action (val_pot_deg, 34);
  } else if (data_gaz == 335) {
    verin_action (val_pot_deg, 35);
  } else if (data_gaz == 336) {
    verin_action (val_pot_deg, 36);
  } else if (data_gaz == 337) {
    verin_action (val_pot_deg, 37);
  } else if (data_gaz == 338) {
    verin_action (val_pot_deg, 38);
  } else if (data_gaz == 339) {
    verin_action (val_pot_deg, 39);
  } else if (data_gaz == 340) {
    verin_action (val_pot_deg, 40);
  } else if (data_gaz == 341) {
    verin_action (val_pot_deg, 41);
  } else if (data_gaz == 342) {
    verin_action (val_pot_deg, 42);
  } else if (data_gaz == 343) {
    verin_action (val_pot_deg, 43);
  } else if (data_gaz == 344) {
    verin_action (val_pot_deg, 44);
  } else if (data_gaz == 345) {
    verin_action (val_pot_deg, 45);
  } else if (data_gaz == 346) {
    verin_action (val_pot_deg, 46);
  } else if (data_gaz == 347) {
    verin_action (val_pot_deg, 47);
  } else if (data_gaz == 348) {
    verin_action (val_pot_deg, 48);
  } else if (data_gaz == 349) {
    verin_action (val_pot_deg, 49);
  } else if (data_gaz == 350) {
    verin_action (val_pot_deg, 50);
  } else if (data_gaz == 351) {
    verin_action (val_pot_deg, 51);
  } else if (data_gaz == 352) {
    verin_action (val_pot_deg, 52);
  } else if (data_gaz == 353) {
    verin_action (val_pot_deg, 53);
  } else if (data_gaz == 354) {
    verin_action (val_pot_deg, 54);
  } else if (data_gaz == 355) {
    verin_action (val_pot_deg, 55);
  } else if (data_gaz == 356) {
    verin_action (val_pot_deg, 56);
  } else if (data_gaz == 357) {
    verin_action (val_pot_deg, 57);
  } else if (data_gaz == 358) {
    verin_action (val_pot_deg, 58);
  } else if (data_gaz == 359) {
    verin_action (val_pot_deg, 59);
  } else if (data_gaz == 360) {
    verin_action (val_pot_deg, 60);
  } else if (data_gaz == 361) {
    verin_action (val_pot_deg, 61);
  } else if (data_gaz == 362) {
    verin_action (val_pot_deg, 62);
  } else if (data_gaz == 363) {
    verin_action (val_pot_deg, 63);
  } else if (data_gaz == 364) {
    verin_action (val_pot_deg, 64);
  } else if (data_gaz == 365) {
    verin_action (val_pot_deg, 65);
  } else if (data_gaz == 366) {
    verin_action (val_pot_deg, 66);
  } else if (data_gaz == 367) {
    verin_action (val_pot_deg, 67);
  } else if (data_gaz == 368) {
    verin_action (val_pot_deg, 68);
  } else if (data_gaz == 369) {
    verin_action (val_pot_deg, 69);
  } else if (data_gaz == 370) {
    verin_action (val_pot_deg, 70);
  } else if (data_gaz == 371) {
    verin_action (val_pot_deg, 71);
  } else if (data_gaz == 372) {
    verin_action (val_pot_deg, 72);
  } else if (data_gaz == 373) {
    verin_action (val_pot_deg, 73);
  } else if (data_gaz == 374) {
    verin_action (val_pot_deg, 74);
  } else if (data_gaz == 375) {
    verin_action (val_pot_deg, 75);
  } else if (data_gaz == 376) {
    verin_action (val_pot_deg, 76);
  } else if (data_gaz == 377) {
    verin_action (val_pot_deg, 77);
  } else if (data_gaz == 378) {
    verin_action (val_pot_deg, 78);
  } else if (data_gaz == 379) {
    verin_action (val_pot_deg, 79);
  } else if (data_gaz == 380) {
    verin_action (val_pot_deg, 80);
  } else if (data_gaz == 381) {
    verin_action (val_pot_deg, 81);
  } else if (data_gaz == 382) {
    verin_action (val_pot_deg, 82);
  } else if (data_gaz == 383) {
    verin_action (val_pot_deg, 83);
  } else if (data_gaz == 384) {
    verin_action (val_pot_deg, 84);
  } else if (data_gaz == 385) {
    verin_action (val_pot_deg, 85);
  } else if (data_gaz == 386) {
    verin_action (val_pot_deg, 86);
  } else if (data_gaz == 387) {
    verin_action (val_pot_deg, 87);
  } else if (data_gaz == 388) {
    verin_action (val_pot_deg, 88);
  } else if (data_gaz == 389) {
    verin_action (val_pot_deg, 89);
  } else if (data_gaz == 390) {
    verin_action (val_pot_deg, 90);
  }

  msg = "";
  data_etincelle = 0;
  data_air = 0;
  data_gaz = 0;
}


void LectureMaitre() {
  while (ArduinoMaitre.available()) {
    delay(10);
    if (ArduinoMaitre.available() > 0) {
      char c = ArduinoMaitre.read();  //gets one byte from serial buffer
      msg += c; //makes the string readString
    }
  }
  ArduinoMaitre.flush();
}
