#include <SkyMap.h>

double los_angeles_lattitude = 34.06, los_angeles_longitude = -118.24358; //observation location -- los angeles
double year = 2021, month = 9, day = 4, UTC_TIME = 20.50;                 // date and time of observation we plan
double Sirius_right_ascension = 101.52, Sirius_Declination = -16.7424;    //sirius declination and right_ascension read from astronmical data site // note that i changed RA from hours to degrees
double Azimuth, Altitude;                                                 //variables to store alt and az of sirius
const Star Sirius{ Sirius_right_ascension, Sirius_Declination };
void setup()
{
    Serial.begin(9600);
    Skymap.my_location(los_angeles_lattitude, los_angeles_longitude); // lines from 12 to 14 provide enough data to calculate Azimuth and altitude based on your location and time
    Skymap.DateTime(year, month, day, UTC_TIME);
    Skymap.star_ra_dec(Sirius);
    Skymap.Calculate_all();
    Altitude = Skymap.get_star_Altitude();
    Azimuth = Skymap.get_star_Azimuth();
}
void loop()
{

    Serial.print("Sirius Azimuth:");
    Serial.println(Azimuth);
    Serial.print("Sirius Altitude:");
    Serial.println(Altitude);
    delay(2000);
}