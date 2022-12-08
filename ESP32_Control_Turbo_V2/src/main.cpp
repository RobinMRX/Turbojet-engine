#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const char* ssid = "Control_turbo";
const char* password = "Mangemort";

const int air = 4;
const int etincelle = 17;
const int gaz = 16;

const int feuRouge = 18;
const int feuOrange = 19;
const int feuVert = 5;

const int finDeCourse = 2;
int etat_FDC;

int consignePourc = 0;
float consigneTour = 0;
float tour = 0.0;

const int stepPin = 23;
const int dirPin = 22;

int delais = 1500;

AsyncWebServer serveur(80);

float pourcentage2tr(int pourcentage){
  const float maxDeg = 90.0;
  const float pas = 8.0;
  const float r = 85.0;
  const float pi = 3.1415;

  float tour = (maxDeg/100.0)*((2.0*pi*r)/(pas*360.0))*pourcentage;
  return (tour);
}

void start(){
    for (int i=0; i<=2; i++){

        digitalWrite(feuVert, LOW);
        digitalWrite(feuOrange, LOW);
        digitalWrite(feuRouge, LOW);

        delay(1000);

        digitalWrite(feuVert, HIGH);
        digitalWrite(feuOrange, HIGH);
        digitalWrite(feuRouge, HIGH);

        delay(1000);
    }    
}

void zeroStepper(){
    digitalWrite(dirPin, HIGH);
    etat_FDC = digitalRead(finDeCourse);

    while (etat_FDC){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(delais/2);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(delais/2);

        etat_FDC = digitalRead(finDeCourse);
    }

    consignePourc = 0;
    consigneTour = 0;
    tour = 0.0;
    
}

void setup() {
    //----------------------------------------------------------Serial
    Serial.begin(115200);
    Serial.println('\n');

    //----------------------------------------------------------GPIO
    pinMode(air, OUTPUT);
    digitalWrite(air, HIGH);
    
    pinMode(etincelle, OUTPUT);
    digitalWrite(etincelle, HIGH);

    pinMode(gaz, OUTPUT);
    digitalWrite(gaz, HIGH);

    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    digitalWrite(dirPin, HIGH);

    pinMode(feuRouge, OUTPUT);
    digitalWrite(feuRouge, HIGH);

    pinMode(feuOrange, OUTPUT);
    digitalWrite(feuOrange, HIGH);

    pinMode(feuVert, OUTPUT);
    digitalWrite(feuVert, HIGH);

    pinMode(finDeCourse, INPUT_PULLUP);

    //----------------------------------------------------------SPIFFS
    if(!SPIFFS.begin()){
        Serial.println("Erreur SPIFFS...");
        return;
    }

    File root = SPIFFS.open("/");
    File file = root.openNextFile();

    while (file){
        Serial.print("File: ");
        Serial.println(file.name());
        file.close();
        file = root.openNextFile();
    }
    
    //----------------------------------------------------------Wi-Fi
    Serial.println("Creation du point d'acces...");
    WiFi.softAP(ssid, password); // Création du point d'accès. On peu créer un réseau ouvert si on ne précise pas de mdp. Un nom est généré automatiquement si on ne précise pas de nom.

    Serial.print("Adresse IP: ");
    Serial.println(WiFi.softAPIP()); // Donne l'adresse IP généré par notre point d'accès.

    //----------------------------------------------------------SERVEUR
    serveur.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html");
    });

    serveur.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
    });

    serveur.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/script.js", "text/javascript");
    });

    serveur.on("/robi.ico", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/robi.ico", "image/ico");
    });

    serveur.on("/onAllu", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(etincelle, LOW);
        digitalWrite(feuOrange, LOW);
        Serial.println("onAllu");
        request->send(204);
    });

    serveur.on("/offAllu", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(etincelle, HIGH);
        digitalWrite(feuOrange, HIGH);
        Serial.println("offAllu");
        request->send(204);
    });

    serveur.on("/onAir", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(air, LOW);
        digitalWrite(feuVert, LOW);
        Serial.println("onAir");
        request->send(204);
    });

    serveur.on("/offAir", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(air, HIGH);
        digitalWrite(feuVert, HIGH);
        Serial.println("offAir");
        request->send(204);
    });

    serveur.on("/onGaz", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(gaz, LOW);
        digitalWrite(feuRouge, LOW);
        Serial.println("onGaz");
        request->send(204);
    });

    serveur.on("/offGaz", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(gaz, HIGH);
        digitalWrite(feuRouge, HIGH);
        zeroStepper();
        Serial.println("offGaz");
        request->send(204);
    });

    serveur.on("/slider", HTTP_GET, [](AsyncWebServerRequest *request){
        String message;
        if(request->hasParam("value")){
            Serial.println("l'ESP a trouvé le paramètre");
            message = request->getParam("value")->value();
            Serial.println("MESSAGE :" + message);
            Serial.println("TOUR :" + String(tour));

            consignePourc = message.toInt();
            Serial.println("CONSIGNE POURCENTAGE : " + String(consignePourc));

            consigneTour = pourcentage2tr(consignePourc);
            Serial.println("CONSIGNE TOUR : " + String(consigneTour));

            float diffTour = consigneTour - tour;
            Serial.println("DIFF TOUR : " + String(diffTour));

            tour += diffTour;
            Serial.println("TOUR :" + String(tour));

            if (diffTour>0){
                digitalWrite(dirPin, LOW);
                for(int i=0; i<round(200*diffTour); i++){
                digitalWrite(stepPin, HIGH);
                delayMicroseconds(delais/2);
                digitalWrite(stepPin, LOW);
                delayMicroseconds(delais/2);
                }
            }else if (diffTour<0){
                digitalWrite(dirPin, HIGH);
                for(int i=0; i<abs(round(200*diffTour)); i++){
                digitalWrite(stepPin, HIGH);
                delayMicroseconds(delais/2);
                digitalWrite(stepPin, LOW);
                delayMicroseconds(delais/2);
                }
                digitalWrite(dirPin, LOW);
            } else {}
        }

        request->send(204);
    });

    /*serveur.on("/lirePotar", HTTP_GET, [](AsyncWebServerRequest *request){
        int val = analogRead(potar);
        String valPotar = String(val);
        request->send(200, "text/plain", valPotar);
    });

    serveur.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(air, HIGH);
        request->send(200);
    });

    serveur.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(air, LOW);
        request->send(200);
    });*/

    serveur.begin();
    Serial.println("Serveur actif!");

    zeroStepper();
    start();
}

void loop() {

}

