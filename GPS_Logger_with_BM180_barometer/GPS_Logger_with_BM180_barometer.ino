#include <TinyGPS++.h>
#include <SFE_BMP180.h>
//#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

SFE_BMP180 pressure;

const int chipSelect = 4;
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
static char lati[15];
static char lngi[15];
static char alt[5];
double baseline; // baseline pressure
double Temp;
File dataFile;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  //Serial.begin(4800);
  //Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
//  dataFile = SD.open("GPS.txt");
//  if (dataFile) {
//    while (dataFile.available()) {
//      Serial.write(dataFile.read());
//    }
//    dataFile.close();
//  }
//  else {
//    Serial.println("error opening datalog.txt");
//  }
  //Serial.println("card initialized. Starting GPS Logging.");
  Serial.begin(GPSBaud);
  if (pressure.begin()){
    //Serial.println("BMP180 init success");
  }else{
    //Serial.println("BMP180 init FAIL");
    return;
  }
  baseline = getPressure();
  //Serial.print("baseline pressure: ");
  //Serial.print(baseline);
  //Serial.println(" mb");
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial.available() > 0)
    if (gps.encode(Serial.read()))
      logData();

    ///MOVE STUFF IN HERE WITH NON-BLOCKING INTERVALS

  if (millis() > 10000 && gps.charsProcessed() < 10)
  {
    //Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void logData()
{
  double P,a;
  P = getPressure();
  a = (pressure.altitude(P,baseline)+311)*3.2808;
  dtostrf(gps.location.lat(),0,6,lati);
  dtostrf(gps.location.lng(),0,6,lngi);
  dtostrf(a,0,2,alt);
  dataFile = SD.open("GPS.txt", FILE_WRITE);
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
  dataFile.print(",");
  dataFile.print((9.0/5.0)*Temp+32.0,2);
  dataFile.print("");
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
    dataFile.print(F(":"));
    if (gps.time.centisecond() < 10) dataFile.print(F("0"));
    dataFile.println(gps.time.centisecond());
  }else{
    dataFile.println("INVALID");
  }
  dataFile.close();
//  Serial.print(lati);
//  Serial.print(",");
//  Serial.print(lngi);
//  Serial.print(",");
//  Serial.print(alt);
//  Serial.print(",");
//  Serial.print(gps.date.month());
//  Serial.print("/");
//  Serial.print(gps.date.day());
//  Serial.print("/");
//  Serial.print(gps.date.year());
//  Serial.print(",");
//  Serial.print((9.0/5.0)*Temp+32.0,2);
//  Serial.println("");
}


double getPressure()
{
  char status;
  double T,P,p0,a;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      Temp = T;
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}
