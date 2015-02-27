#include <TinyGPS++.h> // Biblioteka za GPS
#include <SoftwareSerial.h> // Biblioteka za dodatnu serijsku kominkaciju
#include <SPI.h> // Biblioteka (Serial Peripheral Interface) za komunikaciju SD kartice
#include <SD.h> // Biblioteka za SD karticu

static const int RXPin = 4, TXPin = 3; // TX i RX pinovi za GPS, spojiti TX-RX, RX-TX
static const unsigned long GPSBaud = 9600; // GPS radi na 9600 bauda
TinyGPSPlus gps; // Instanca TinyGPS objekta
SoftwareSerial ss(RXPin, TXPin); // Serija sa GPS modulom
int chipSelect = 2; // CS pin SD kartice je spojen na pin 2
File sdCardObject; // Varijabla za manipuliranje SD karticom

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);

  Serial.println(F("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"));
  Serial.println(F("Visoka skola za primijenjeno racunarstvo"));
  Serial.println(F("Sustav za detekciju prometne nesrece"));
  Serial.println(F("Testiranje GPS modula"));
  Serial.print(F("TinyGPS++ biblioteka u verziji ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println();
  
  pinMode(10, OUTPUT); // Pin 10 mora biti zauzet za SD modul
  SD.begin(chipSelect); // Inicijaliziramo SD karticu i dodijelimo pin
  
  if(SD.exists("gpsData.txt")){ // Ako postoji gpsData.txt, izbrisat cemo ga i pisati nanovo
    SD.remove("gpsData.txt");
  }
}

void loop()
{
  // Nakon svake NMEA recenice ispisuju se podaci
  while (ss.available() > 0){
    if (gps.encode(ss.read())){
        displayInfo();
        
        if(gps.location.isValid()){ // Zapisujemo samo ako imamo koordinate
            sdCardObject = SD.open("gpsData.txt", FILE_WRITE); // Otvaramo gpsData za pisanje
            sdCardObject.print(gps.location.lng(), 6);
            sdCardObject.print(",");
            sdCardObject.print(gps.location.lat(), 6);
            sdCardObject.print(" ");
            sdCardObject.close();
        }
      }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("Veza sa GPS modulom nije uspostavljena."));
    while(true){};
  }
}

void displayInfo() // Funkcija za ispis podataka
{
  // Koordinate
  Serial.print(F("Lokacija: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
      Serial.print(F("[KOORDINATE NEDOSTUPNE]"));
  }
  
  // Datum i vrijeme
  Serial.print(F("  Datum/Vrijeme: "));
  
  if (gps.date.isValid())
  {
    Serial.print(gps.date.day());
    Serial.print(F("."));
    Serial.print(gps.date.month());
    Serial.print(F("."));
    Serial.print(gps.date.year());
    Serial.print(F("."));
  }
  else
  {
    Serial.print(F("[DATUM NEDOSTUPAN]"));
  }

  Serial.print(F("/"));
  
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour() + 1);
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("[VRIJEME NEDOSTUPNO]"));
  }
  
  Serial.print(F("  "));
  
  // Brzina
  if(gps.speed.isValid())
  {
     Serial.print("Brzina: ");
     Serial.print(gps.speed.kmph());
     Serial.print("km/h");
  }
  else
  {
     Serial.print(F("[BRZINA NIJE DOSTUPNA]")) ;
  }
  
  Serial.print(F("  "));
  
  // Visina
  if(gps.altitude.isValid())
  {
    Serial.print("Visina: ");
    Serial.print(gps.altitude.meters());
  }
  else
  {
     Serial.print("[VISINA NIJE DOSTUPNA]");
  }
  
  Serial.print(F("  "));
  
  // Jacina signala
  if(gps.hdop.isValid())
  {
     Serial.print("Jacina signala (HDOP): ");
     Serial.print(gps.hdop.value()); 
  }
  else
  {
     Serial.print("[JACINA SIGNALA NIJE DOSTUPNA]"); 
  }

  Serial.println();
}
