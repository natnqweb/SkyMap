# SkyMap

Tool that let you calculate star azimuth altitude, in any given time and any given position
i provided some examples
in examples we observate sirius from los angeles
as you will see in examples under you can gather some interesting data as for example hour angle or days from j2000 or local sidereal time and even you can calculate UTC for your timezone

# Install tutorial here

<https://www.ardu-badge.com/SkyMap>

# constructor example observation object-Sirius - observation location los angeles ----Lat 34deg 3min 8 sec North----Long 118deg 14 min  37 sec WEST---- observation time 20:12UTC date: 4.september.2021

```C++
    #include <SkyMap.h>
    degs lattitude = 34.06;
    degs longitude = 118.24358;
    degs declination = -16.7424;
    degs right_ascension = 6.768 * 15;
    years year = 2021;
    months month = 9;
    days day = 4;
    hrs s_time = 20.2;
    enum Directions : int8_t
    {
    N = 1,
    S = -1,
    E = 1,
    W = -1
    };


    SkyMap star(lattitude *N, longitude *W, declination, right_ascension, year, month, day, s_time);
```

# Simple RealTime calculations

```C++
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
```
