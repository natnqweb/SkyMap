# SkyMap (4.1.0)
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

## Q6: Can it be used outside of Arduino?

Yes! The SkyMap library is a C-style, header-only library that depends solely on math.h. This means it can be used almost everywhere, as C is a broadly supported language.

# Install tutorial here

<https://www.ardu-badge.com/SkyMap>

# Conversion from azimuth and altitude to right ascension and declination (from SKYMAP 4.1.0)

```C
/**
 * @brief Converts the azimuth and altitude of an object to its equatorial coordinates (RA/Dec).
 * @param geo_position Pointer to a SKYMAP_geo_position_t structure containing the observer's geographic location.
 * @param local_astr_pos_of_object Pointer to a SKYMAP_local_position_t structure containing the azimuth and altitude of the object.
 * @param dt Pointer to a SKYMAP_date_time_values_t structure containing the date and time of the observation. in field hour (Coordinated Universal Time)
 * @return A SKYMAP_astronomical_position_t structure containing the right ascension (RA) and declination (Dec) of the object.
 */
SKYMAP_equatorial_coordinates_t SKYMAP_az_alt_to_ra_dec(
    SKYMAP_geo_position_t* geo_position,
    SKYMAP_local_position_t* local_astr_pos_of_object,
    SKYMAP_date_time_values_t* dt);

```

```C
void test_SKYMAP_directly_az_alt_to_ra_dec() {
    // New York City coordinates
    SKYMAP_geo_position_t geo_position;
    geo_position.latitude = 40.7128;
    geo_position.longitude = -74.0060;

    // Local astronomical position (Alt/Az)
    SKYMAP_local_position_t local_astr_pos_of_object;
    local_astr_pos_of_object.azimuth = 359.89;
    local_astr_pos_of_object.altitude = 41.44;

    // Direct UTC values for time and date
    SKYMAP_date_time_values_t dt;
    dt.year = 2021.0;
    dt.month = 11.0;
    dt.day = 28.0;
    dt.hour = 20.0; //UTC

    // Perform conversion from Alt/Az to RA/Dec
    SKYMAP_equatorial_coordinates_t result = SKYMAP_az_alt_to_ra_dec(&geo_position, &local_astr_pos_of_object, &dt);
    Serial.print("result ra = ");
    Serial.print(result.right_ascension);
    Serial.print(" result dec = ");
    Serial.println((result.declination));
}
```

More in example - az_alt_to_ra_dec

# Step by Step calculations

```C
#include <SkyMap.h>
// data you must provide
double year, month, day, hour, minute, second; // date and time can be taken from rtc
double local_timezone_offset;
double Time_utc;             // we will convert it from your time +offset
double latitude, longitude; // your lat and long can be taken from gps or hardcoded
double RA, dec;              // can be taken from internet just look for star you are interested in
double j2000;                // SKYMAP_days since jan 2000  - to be calculated
double Local_sidereal_time;  // to be calculated
double Hour_angle;           // to be calculated
double Az;                   // finally Azimuth of star and altitude
double Alt;

void setup()
{

    Serial.begin(9600);

    // date 2021-09-04 time 20:30:00-los angeles time not UTC!, observation object Sirius
    year = 2021;
    month = 9;
    day = 4;
    hour = 20;
    minute = 30;
    second = 0;
    local_timezone_offset = -7;                                                  // offset for los angeles
    SKYMAP_date_time_values_t dt;
    dt.day = day;
    dt.month = month;
    dt.year = year;
    Time_utc = SKYMAP_hh_mm_ss2UTC(&dt, hour, minute, second, local_timezone_offset); // converting to UTC

    latitude = 34.06;                                                           // los angeles
    longitude = -118.24358;                                                      // los angeles
    RA = 101.52;                                                                 // sirius
    dec = -16.7424;                                                              // sirius
    j2000 = SKYMAP_j2000(&dt);
    Local_sidereal_time = SKYMAP_local_sidereal_time(j2000, Time_utc, longitude);
    Hour_angle = SKYMAP_hour_angle(Local_sidereal_time, RA);
    SKYMAP_search_result_t result = SKYMAP_search_for_object(Hour_angle, dec, latitude);
    Az = result.azimuth;
    Alt = result.altitude;
}
void loop()
{
    Serial.print("Azimuth: ");
    Serial.println(Az);
    Serial.print("Altitude: ");
    Serial.println(Alt);
    delay(3000);
}
```

# example observation object-Sirius - observation location los angeles ----Lat 34deg 3min 8 sec North----Long 118deg 14 min  37 sec WEST---- observation time 20:12UTC date: 4.september.2021

```C
#include <SkyMap.h>

// Always convert right_ascension to SKYMAP_degs!
// Provided coordinates for Los Angeles:
// Latitude: 34° 3' 8" N
// Longitude: 118° 14' 37" W
// We are observing Sirius:
// Sirius RA: -6.768 (convert to degrees by multiplying by 15)
// Sirius DEC: -16.7424
// Observation date and time: 2021-09-04 at 20:12 UTC
// Directions: North-positive, South-negative, East-positive, West-negative

// const double latitude = 34.06, longitude = -118.24358, declination = -16.7424, right_ascension = 6.768 * 15, year = 2021, month = 9, day = 4, time = 20.2;
// Note: For West direction, the value is negative.
// Use this format if you are unsure.

SKYMAP_degs latitude = 34.06;
SKYMAP_degs longitude = 118.24358; // degrees
SKYMAP_degs declination = -16.7424;
SKYMAP_degs right_ascension = 6.768 * 15;
SKYMAP_years year = 2021;
SKYMAP_months month = 9;
SKYMAP_days day = 4;
SKYMAP_hrs s_time = 20.2;

enum Directions : int8_t
{
    N = 1,
    S = -1,
    E = 1,
    W = -1
};

SKYMAP_skymap_t skymap;

void setup()
{
    SKYMAP_init(&skymap);

    SKYMAP_update(&skymap, latitude * N, longitude * W, declination, right_ascension, year, month, day, s_time);
    SKYMAP_search_result_t star_position = SKYMAP_observe_object(&skymap);

    Serial.begin(115200);
    Serial.println(star_position.altitude);
    Serial.println(star_position.azimuth);
}

void loop()
{
}
```

# Simple RealTime calculations

```C
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
```
