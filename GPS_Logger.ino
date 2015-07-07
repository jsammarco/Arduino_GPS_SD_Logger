#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
static char lati[15];
static char lngi[15];
static char alt[5];

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(4800);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized. Starting GPS Logging.");
  ss.begin(GPSBaud);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      logData();

  if (millis() > 10000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void logData()
{
  File dataFile = SD.open("GPS.txt", FILE_WRITE);
  dtostrf(gps.location.lat(),0,6,lati);
  dtostrf(gps.location.lng(),0,6,lngi);
  dtostrf(gps.altitude.feet(),0,0,alt);
  dataFile.print(lati);
  dataFile.print(",");
  dataFile.print(lngi);
  dataFile.print(",");
  dataFile.print(alt);
  dataFile.print(",");
  dataFile.print(gps.date.month());
  dataFile.print("/");
  dataFile.print(gps.date.day());
  dataFile.print("/");
  dataFile.print(gps.date.year());
  dataFile.print(" ");
  Serial.print(lati);
  Serial.print(",");
  Serial.print(lngi);
  Serial.print(",");
  Serial.print(alt);
  Serial.print(",");
  Serial.print(gps.date.month());
  Serial.print("/");
  Serial.print(gps.date.day());
  Serial.print("/");
  Serial.print(gps.date.year());
  Serial.println(" ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) dataFile.print(F("0"));
    dataFile.print(gps.time.hour());
    dataFile.print(F(":"));
    if (gps.time.minute() < 10) dataFile.print(F("0"));
    dataFile.print(gps.time.minute());
    dataFile.print(F(":"));
    if (gps.time.second() < 10) dataFile.print(F("0"));
    dataFile.print(gps.time.second());
    dataFile.print(F("."));
    if (gps.time.centisecond() < 10) dataFile.print(F("0"));
    dataFile.println(gps.time.centisecond());
  }
  else
  {
    dataFile.println("INVALID");
  }
  dataFile.close();
}


//Old display func
void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Altitude: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.altitude.feet());
    Serial.print(F("ft"));
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
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
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
