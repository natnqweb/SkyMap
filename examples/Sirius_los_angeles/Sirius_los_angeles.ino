#include <SkyMap.h>
SkyMap sirius;

float los_angeles_lattitude = 34.06, los_angeles_longitude = -118.24358; //observation location -- los angeles
float year = 2021, month = 9, day = 4, UTC_TIME = 20.50;                 // date and time of observation we plan
float Sirius_right_ascension = 101.52, Sirius_Declination = -16.7424;    //sirius declination and right_ascension read from astronmical data site // note that i changed RA from hours to degrees
float Azymuth, Altitude;                                                 //variables to store alt and az of sirius

void setup()
{
    Serial.begin(9600);
    sirius.my_location(los_angeles_lattitude, los_angeles_longitude); // lines from 12 to 14 provide enough data to calculate azymuth and altitude based on your location and time
    sirius.DateTime(year, month, day, UTC_TIME);
    sirius.star_ra_dec(Sirius_right_ascension, Sirius_Declination);
    sirius.Calculate_all();
    Altitude = sirius.get_star_Altitude();
    Azymuth = sirius.get_star_Azymuth();
}
void loop()
{

    Serial.print("Sirius Azymuth:");
    Serial.println(Azymuth);
    Serial.print("Sirius Altitude:");
    Serial.println(Altitude);
    delay(2000);
}