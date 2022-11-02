#include <SkyMap.h>
//this program will show where the sirius is in sky when you will observe him exactly at same day and same time of month for every month

ObserverPosition observation_location{ 34.06 ,-118.24358 };                // observation location -- los angeles 
DateTimeValues dt{ 2021/*year*/,1 /*month*/,4/*day*/,20.50 /*time utc*/ };// date and time of observation we plan  
Star Sirius{ 101.52 ,-16.7424 };                                          // sirius right_ascension and declination read from astronmical data site // note that i changed RA from hours to degrees
SearchResult search_result{};                                             // variables to store alt and az of sirius
void setup()
{
    Serial.begin(9600);
}
void loop()
{

    dt.month += 1;
    if (dt.month > 12)
        dt.month = 1;
    Skymap.update(observation_location, Sirius, dt);
    search_result = Skymap.get_search_result();
    Serial.print("observations for month:");
    Serial.println((int)dt.month);
    Serial.print("in los_angeles: ");
    Serial.print("lattitude:");
    Serial.print(observation_location.lattitude);
    Serial.print(" longitude:");
    Serial.print(observation_location.longitude);
    Serial.println();
    Serial.print("time:");
    Serial.println("20:30 UTC");
    Serial.print("year:");
    Serial.println("2021");
    Serial.print("day:");
    Serial.println("4");
    Serial.print("Sirius Azimuth:");
    Serial.println(search_result.GetAzimuth());
    Serial.print("Sirius Altitude:");
    Serial.println(search_result.GetAltitude());
    Serial.println("---------------------");
    delay(3000);
}