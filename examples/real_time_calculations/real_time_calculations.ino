#include <SkyMap.h>
//this program will show where the sirius is in sky when you will observe him exactly at same day and same time of month for every month
SkyMap Sirius;

float los_angeles_lattitude = 34.06, los_angeles_longitude = -118.24358; //observation location -- los angeles
float year = 2021, month = 1, day = 4, UTC_TIME = 20.50;                 // date and time of observation we plan
float Sirius_right_ascension = 101.52, Sirius_Declination = -16.7424;    //sirius declination and right_ascension read from astronmical data site // note that i changed RA from hours to degrees
float Azimuth, Altitude;                                                 //variables to store alt and az of sirius
void setup()
{
    Serial.begin(9600);
}
void loop()
{

    month += 1;
    if (month > 12)
        month = 1;
    Sirius.update(los_angeles_lattitude, los_angeles_longitude, Sirius_Declination, Sirius_right_ascension, year, month, day, UTC_TIME);
    Azimuth = Sirius.get_star_Azimuth();
    Altitude = Sirius.get_star_Altitude();
    Serial.print("observations for month:");
    Serial.println((int)month);
    Serial.print("in los_angeles: ");
    Serial.print("lattitude:");
    Serial.print(los_angeles_lattitude);
    Serial.print(" longitude:");
    Serial.print(los_angeles_longitude);
    Serial.println();
    Serial.print("time:");
    Serial.println("20:30 UTC");
    Serial.print("year:");
    Serial.println("2021");
    Serial.print("day:");
    Serial.println("4");
    Serial.print("Sirius Azimuth:");
    Serial.println(Azimuth);
    Serial.print("Sirius Altitude:");
    Serial.println(Altitude);
    Serial.println("---------------------");
    delay(3000);
}