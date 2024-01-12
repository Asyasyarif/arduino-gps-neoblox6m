
#include <TinyGPS++.h>

#define RXD2 16
#define TXD2 17
HardwareSerial neogps(1);

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  //Begin serial communication Arduino IDE (Serial Monitor)

  //Begin serial communication Neo6mGPS
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);

  delay(2000);

}

void loop() {
    
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;){
    while (neogps.available()){
      if (gps.encode(neogps.read())){
        newData = true;
      }
    }
  }

  //If newData is true
  if(newData == true){
    newData = false;
    Serial.println(gps.satellites.value());
    print_speed();
  }
  
}

void print_speed()
{
       
  if (gps.location.isValid() == 1){

    Serial.println(gps.location.lat(), 6);
    Serial.println(gps.location.lng(), 6);
    Serial.println(gps.speed.kmph());
    Serial.println(gps.satellites.value());
    Serial.println(gps.altitude.meters(), 0);

  } else {
     Serial.println("No data");
  }  

}