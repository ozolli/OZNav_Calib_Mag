/* Etalonnage du magnétomètre
 
Norm of Magnetic field calculator pour Magneto :
http://www.geomag.bgs.ac.uk/data_service/models_compass/wmm_calc.html

Prendre la valeur F = Total Intensity et la diviser par 1000 puisque nous sommes en µT
Par exemple 47.128 µT pour Marans le 08/03/2018
C'est la valeur à entrer dans Magneto 1.2

Ouvrir un moniteur série et bouger le NXP en 3D loin de toutes masses métalliques et magnétiques
ainsi que toutes sources de courant pour collecter les données. J'utilise un cordon USB de 5m.
Copier-coller l'ensemble des données dans un fichier texte et l'importer dans Magneto 1.2

Mettre à jour les valeurs de OZNav/compas.h avec les calculs de Magneto :
- Combined bias (b) dans mag_offsets
- Correction for combined scale factors, misalignments and soft iron (A) dans mag_softiron_matrix
- Norm of Magnetic field dans mag_field_strength (pour info, non utilisé)
*/
 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_FXOS8700.h>

#define MAG_UT_LSB      (0.1F)

// Create sensor instances.
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);

// Offsets X, Y et Z de l'accéléromètre entrés directement dans le FXOS8700
int accel_offset[3]             = { -14, 20, -27 };

void setup()
{
  Serial.begin(38400);
  if(!accelmag.begin(ACCEL_RANGE_2G, accel_offset[0], accel_offset[1], accel_offset[2]))
  {
    Serial.println("Ooops, no FXOS8700 detected ... Check your wiring!");
    while(1);
  }
  Serial.println("Magnetometer Uncalibrated (Units in µT/LSB)");
}

void loop()
{
  sensors_event_t event; // Need to read raw data, which is stored at the same time
  float Xm_print, Ym_print, Zm_print;

  accelmag.getEvent(&event);
  
  // Mesures brutes converties en µT
  Xm_print = accelmag.mag_raw.x*MAG_UT_LSB;
  Ym_print = accelmag.mag_raw.y*MAG_UT_LSB;
  Zm_print = accelmag.mag_raw.z*MAG_UT_LSB;
  
  Serial.print(Xm_print); Serial.print(" "); Serial.print(Ym_print); Serial.print(" "); Serial.println(Zm_print);
  delay(125);
}

