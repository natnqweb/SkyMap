#include <SkyMap.h>

double los_angeles_latitude = 34.06, los_angeles_longitude = -118.24358; //observation location -- los angeles
double year = 2021, month = 9, day = 4, UTC_TIME = 20.50;                 // date and time of observation we plan
double Sirius_right_ascension = 101.52, Sirius_Declination = -16.7424;    //sirius declination and right_ascension read from astronmical data site // note that i changed RA from hours to degrees
double Azimuth, Altitude;                                                 //variables to store alt and az of sirius

SKYMAP_skymap_t skymap;
SKYMAP_star_t Sirius;
SKYMAP_observer_position_t los_angeles;
SKYMAP_date_time_values_t observation_time;

void setup()
{
    SKYMAP_init(&skymap);
    Serial.begin(9600);

    //SKYMAP_celestial_object_t Sirius;
    Sirius.right_ascension = Sirius_right_ascension;
    Sirius.declination = Sirius_Declination;

    los_angeles.latitude = los_angeles_latitude;
    los_angeles.longitude = los_angeles_longitude;

    observation_time.year = year;
    observation_time.month = month;
    observation_time.day = day;
    observation_time.hour = UTC_TIME;

}
void loop()
{
    skymap.object_to_search = Sirius;
    skymap.observer_position = los_angeles;
    skymap.date_time = observation_time;

    SKYMAP_search_result_t result = SKYMAP_observe_object(&skymap);

    Altitude = result.altitude;
    Azimuth = result.azimuth;

    Serial.print("Sirius Azimuth:");
    Serial.println(Azimuth);
    Serial.print("Sirius Altitude:");
    Serial.println(Altitude);
    delay(2000);
}