/*  Etalonnage du magnétomètre.
 *  Utiliser avec C:\Users\Olivier\Documents\Voile\Navigation\Calibration\MotionCal.exe
 *  et entrer les valeurs relevées dans OZNav\compas.h
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_FXAS21002C.h>
#include <Adafruit_FXOS8700.h>

// Create sensor instances.
Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);

// NOTE: THIS IS A WORK IN PROGRESS!

// This sketch can be used to output raw sensor data in a format that
// can be understoof by MotionCal from PJRC. Download the application
// from http://www.pjrc.com/store/prop_shield.html and make note of the
// magentic offsets after rotating the sensors sufficiently.
//
// You should end up with 3 offsets for X/Y/Z, which are displayed
// in the top-right corner of the application.

void setup()
{
  Serial.begin(115200);

  // Wait for the Serial Monitor to open (comment out to run without Serial Monitor)
  // while(!Serial);

  Serial.println(F("Adafruit nDOF AHRS Calibration Example")); Serial.println("");

  // Initialize the sensors.
  if(!gyro.begin())
  {
    /* There was a problem detecting the gyro ... check your connections */
    Serial.println("Ooops, no gyro detected ... Check your wiring!");
    while(1);
  }

  if(!accelmag.begin(ACCEL_RANGE_4G))
  {
    Serial.println("Ooops, no FXOS8700 detected ... Check your wiring!");
    while(1);
  }
}

void loop(void)
{
  sensors_event_t event; // Need to read raw data, which is stored at the same time

    // Get new data samples
    gyro.getEvent(&event);
    accelmag.getEvent(&event);

  // Print the sensor data
  Serial.print("Raw:");
  Serial.print(accelmag.accel_raw.x);
  Serial.print(',');
  Serial.print(accelmag.accel_raw.y);
  Serial.print(',');
  Serial.print(accelmag.accel_raw.z);
  Serial.print(',');
  Serial.print(gyro.raw.x);
  Serial.print(',');
  Serial.print(gyro.raw.y);
  Serial.print(',');
  Serial.print(gyro.raw.z);
  Serial.print(',');
  Serial.print(accelmag.mag_raw.x);
  Serial.print(',');
  Serial.print(accelmag.mag_raw.y);
  Serial.print(',');
  Serial.print(accelmag.mag_raw.z);
  Serial.println();

  delay(50);
}
