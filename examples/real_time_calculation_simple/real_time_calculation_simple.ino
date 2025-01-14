#include <SkyMap.h>
//this program will show where the sirius is in sky when you will observe him exactly at same day and same time of month for every month

SKYMAP_skymap_t skymap;
void setup()
{
    Serial.begin(9600);

    SKYMAP_observer_position_t observation_location; // observation location -- los angeles 
    observation_location.latitude = 34.06;
    observation_location.longitude = -118.24358;

    SKYMAP_date_time_values_t dt;
    dt.year = 2021;
    dt.month = 1;
    dt.day = 4;
    dt.hour = 20.5;// UTC

    SKYMAP_star_t sirius;// sirius right_ascension and declination read from astronmical data site // note that i changed RA from hours to degrees
    sirius.right_ascension = 101.52;
    sirius.declination = -16.7424l;

    skymap.observer_position = observation_location;
    skymap.date_time = dt;
    skymap.object_to_search = sirius;
}
void loop()
{


    skymap.date_time.month += 1;
    if (skymap.date_time.month > 12)
        skymap.date_time.month = 1;

    SKYMAP_search_result_t search_result = SKYMAP_observe_object(&skymap);
    Serial.print("observations for month:");
    Serial.println((int)skymap.date_time.month);
    Serial.print("in los_angeles: ");
    Serial.print("latitude:");
    Serial.print(skymap.observer_position.latitude);
    Serial.print(" longitude:");
    Serial.print(skymap.observer_position.longitude);
    Serial.println();
    Serial.print("time:");
    Serial.println("20:30 UTC");
    Serial.print("year:");
    Serial.println("2021");
    Serial.print("day:");
    Serial.println("4");
    Serial.print("Sirius Azimuth:");
    Serial.println(search_result.azimuth);
    Serial.print("Sirius Altitude:");
    Serial.println(search_result.altitude);
    Serial.println("---------------------");
    delay(3000);
}