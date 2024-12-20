#include <TinyGPS.h>
#include <SoftwareSerial.h>
 
SoftwareSerial gpsSerial(4, 3);  
TinyGPS gps;  
unsigned long lastUpdate = 0;  
 
void setup() {
  Serial.begin(115200);      
  gpsSerial.begin(9600);     
  Serial.println("Testing GPS module with TinyGPS...");
}
 
void loop() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    gps.encode(c);  
  }
 
  if (millis() - lastUpdate > 5000) {  
    lastUpdate = millis();  
 
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
 
    Serial.print("Latitude: ");
    Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);  
 
    Serial.print("Longitude: ");
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);  
 
    Serial.print("Altitude (meters): ");
    Serial.println(gps.f_altitude() == TinyGPS::GPS_INVALID_F_ALTITUDE ? 0.0 : gps.f_altitude());  
 
    Serial.print("Satellites: ");
    Serial.println(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());  
 
    Serial.print("Speed (km/h): ");
    Serial.println(gps.f_speed_kmph());  
 
    Serial.println();  
  }
}
