# SkyMap (3.0.1)
# Frequently Asked Questions (FAQ) :
## Q1: What is the SkyMap library?

The SkyMap library for Arduino allows you to calculate the positions of stars and planets in the sky. It’s a very helpful tool that will allow every amateur and professional to perform complex astronomical calculations. With this library, you can calculate J2000, hour angle, sidereal time, azimuth, altitude. The library was created to enable the creation of devices related to astronomy on Arduino and other systems.

## Q2: How do I install the SkyMap library?

You can install the SkyMap library using the Library Manager in the Arduino IDE. To do this, open the Arduino IDE and navigate to Sketch > Include Library > Manage Libraries. In the Library Manager, search for “SkyMap”, find it in the list, and click on it. You should see the target version of SkyMap (version 3.0.1) listed. Click on “install” and wait for the IDE to install SkyMap.

## Q3: How do I use the SkyMap library in my project?

Once the library is installed, you can include it in your sketch. To do this, navigate to Sketch > Include Library and you should find SkyMap available in the menu. Now that the library is included in your sketch, you can use its functions to calculate the positions of stars and planets in the sky. The SkyMap library allows you to perform complex astronomical calculations, including calculating J2000, hour angle, sidereal time, azimuth, altitude.

## Q4: What is J2000?

J2000.0 is a standard epoch used in astronomy. The prefix “J” indicates that it is a Julian epoch, and the number refers to the date and time of January 1, 2000, at 12:00 Terrestrial Time. This is a moment in time used as a reference point for some time-varying astronomical quantities. The J2000.0 epoch is used due to the precession of the equinoxes, which refers to the observable phenomena of the rotation of the celestial sphere. This precession causes the celestial coordinates of objects, which are defined by the reference of the celestial equator and celestial poles, to constantly change. Therefore, coordinate systems that are defined by the vernal equinox must have a date associated with them.

## Q5: Is the SkyMap library better than other libraries like SolarPosition, Solarlib, SolarCalculator?

The choice between the SkyMap library and the other libraries depends on your specific needs. The SkyMap library is specifically designed for astronomical calculations, including the positions of stars and planets. It provides functions to calculate J2000, hour angle, sidereal time, azimuth, altitude. This makes it a powerful tool for more complex astronomical projects. On the other hand, the SolarPosition, Solarlib, and SolarCalculator libraries are primarily focused on solar calculations. They provide various functions to calculate aspects of solar position in the sky, sunrise, solar noon, and sunset times for the current day, and various other statistics for the sun at the given time. If your project involves calculating the positions of stars and planets, the SkyMap library would be a better choice. However, if you’re primarily interested in solar calculations, the SolarPosition, Solarlib, or SolarCalculator libraries might be more suitable.
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
