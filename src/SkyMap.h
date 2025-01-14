#ifndef SKYMAP_H
#define SKYMAP_H

#include <math.h>

#define SKYMAP_PI (3.14159265358979)

typedef double SKYMAP_years, SKYMAP_months, SKYMAP_days, SKYMAP_hrs, SKYMAP_rads, SKYMAP_degs;

typedef struct SKYMAP_date_time_values
{
    SKYMAP_years year; // The year of the observation
    SKYMAP_months month; // The month of the observation
    SKYMAP_days day; // The day of the observation
    SKYMAP_hrs hour; // The hour of the observation (UTC)
} SKYMAP_date_time_values_t;

typedef struct SKYMAP_observer_position
{
    SKYMAP_degs latitude; // The latitude of the observer's position
    SKYMAP_degs longitude; // The longitude of the observer's position
} SKYMAP_observer_position_t, SKYMAP_geo_position_t;

typedef struct SKYMAP_celestial_object
{
    SKYMAP_degs right_ascension; // The right ascension of the celestial object (similar to longitude on Earth)
    SKYMAP_degs declination; // The declination of the celestial object (similar to latitude on Earth)
} SKYMAP_celestial_object_t, SKYMAP_star_t, SKYMAP_planet_t, SKYMAP_astronomical_position_t, SKYMAP_equatorial_coordinates_t;

typedef struct SKYMAP_search_result
{
    SKYMAP_degs azimuth; // The azimuth angle of the celestial object (measured clockwise from the north)
    SKYMAP_degs altitude; // The altitude angle of the celestial object (measured from the horizon)
} SKYMAP_search_result_t, SKYMAP_local_position_t;

typedef struct SKYMAP_skymap
{
    SKYMAP_observer_position_t observer_position; // The position of the observer (latitude and longitude)
    SKYMAP_date_time_values_t date_time; // The date and time of the observation
    SKYMAP_celestial_object_t object_to_search; // The celestial object being searched for (right ascension and declination)
} SKYMAP_skymap_t;

// Function declarations

/**
 * @brief Converts degrees to radians.
 * @param Deg Angle in degrees.
 * @return Angle in radians.
 */
SKYMAP_rads SKYMAP_deg2rad(SKYMAP_degs Deg);

/**
 * @brief Converts radians to degrees.
 * @param Rad Angle in radians.
 * @return Angle in degrees.
 */
SKYMAP_degs SKYMAP_rad2deg(SKYMAP_rads Rad);

/**
 * @brief Converts hours to degrees.
 * @param h Time in hours.
 * @return Angle in degrees.
 */
SKYMAP_degs SKYMAP_h2deg(SKYMAP_hrs h);

/**
 * @brief Converts degrees to hours.
 * @param deg Angle in degrees.
 * @return Time in hours.
 */
SKYMAP_hrs SKYMAP_deg2h(SKYMAP_degs deg);

/**
 * @brief Calculates the arcsine of an angle in radians and returns the result in degrees.
 * @param rad Angle in radians.
 * @return Angle in degrees.
 */
SKYMAP_degs SKYMAP_asind(SKYMAP_rads rad);

/**
 * @brief Calculates the arccosine of an angle in radians and returns the result in degrees.
 * @param rad Angle in radians.
 * @return Angle in degrees.
 */
SKYMAP_degs SKYMAP_acosd(SKYMAP_rads rad);

/**
 * @brief Calculates the number of SKYMAP_days since J2000.0.
 * @param dt Pointer to a SKYMAP_date_time_values_t structure containing the date and time.
 * @return Number of SKYMAP_days since J2000.0.
 */
SKYMAP_days SKYMAP_j2000(SKYMAP_date_time_values_t* dt);

/**
 * @brief Calculates the local sidereal time.
 * @param j2000 Number of SKYMAP_days since J2000.0.
 * @param a_time Time in hours.
 * @param longitude Observer's longitude in degrees.
 * @return Local sidereal time in degrees.
 */
SKYMAP_degs SKYMAP_local_sidereal_time(SKYMAP_days j2000, SKYMAP_hrs a_time, SKYMAP_degs longitude);

/**
 * @brief Calculates the hour angle.
 * @param lst Local sidereal time in degrees.
 * @param right_ascension Right ascension of the object in degrees.
 * @return Hour angle in degrees.
 */
SKYMAP_degs SKYMAP_hour_angle(SKYMAP_degs lst, SKYMAP_degs right_ascension);

/**
 * @brief Searches for an object's position in the sky.
 * @param hour_angle Hour angle in degrees.
 * @param declination Declination of the object in degrees.
 * @param latitude Observer's latitude in degrees.
 * @return A SKYMAP_search_result_t structure containing the azimuth and altitude of the object.
 */
SKYMAP_search_result_t SKYMAP_search_for_object(SKYMAP_degs hour_angle, SKYMAP_degs declination, SKYMAP_degs latitude);

/**
 * @brief Calculates the number of SKYMAP_days since J2000.0 for a given skymap.
 * @param skymap Pointer to a SKYMAP_skymap_t structure.
 * @return Number of SKYMAP_days since J2000.0.
 */
SKYMAP_days SKYMAP_get_j2000(SKYMAP_skymap_t* skymap);

/**
 * @brief Calculates the local sidereal time for a given skymap.
 * @param skymap Pointer to a SKYMAP_skymap_t structure.
 * @return Local sidereal time in degrees.
 */
SKYMAP_degs SKYMAP_get_local_sidereal_time(SKYMAP_skymap_t* skymap);

/**
 * @brief Calculates the hour angle for a given skymap.
 * @param skymap Pointer to a SKYMAP_skymap_t structure.
 * @return Hour angle in degrees.
 */
SKYMAP_degs SKYMAP_get_hour_angle(SKYMAP_skymap_t* skymap);

/**
 * @brief Gets the position of a celestial object in the sky for a given skymap.
 * @param skymap Pointer to a SKYMAP_skymap_t structure.
 * @return A SKYMAP_search_result_t structure containing the azimuth and altitude of the star.
 */
SKYMAP_search_result_t SKYMAP_observe_object(SKYMAP_skymap_t* skymap);

/**
 * @brief Updates the skymap with new observer and object parameters.
 * @param skymap Pointer to a SKYMAP_skymap_t structure.
 * @param latitude Observer's latitude in degrees.
 * @param longitude Observer's longitude in degrees.
 * @param declination Declination of the object in degrees.
 * @param right_ascension Right ascension of the object in degrees.
 * @param year Year of the observation.
 * @param month Month of the observation.
 * @param day Day of the observation.
 * @param a_time Time of the observation in hours.
 */
void SKYMAP_update(SKYMAP_skymap_t* skymap, SKYMAP_degs latitude, SKYMAP_degs longitude, SKYMAP_degs declination, SKYMAP_degs right_ascension, SKYMAP_years year, SKYMAP_months month, SKYMAP_days day, SKYMAP_hrs a_time);

/**
 * @brief Converts time from hours, minutes, and seconds to UTC.
 * @param dt Pointer to a SKYMAP_date_time_values_t structure.
 * @param h Hours.
 * @param m Minutes.
 * @param s Seconds.
 * @param your_timezone_offset Timezone offset from UTC.
 * @return Time in hours in UTC.
 */
SKYMAP_hrs SKYMAP_hh_mm_ss2UTC(SKYMAP_date_time_values_t* dt, double h, double m, double s, double your_timezone_offset);

/**
 * @brief Initializes the skymap structure with default values.
 * @param skymap Pointer to a SKYMAP_skymap_t structure.
 */
void SKYMAP_init(SKYMAP_skymap_t* skymap);

/**
 * @brief Checks if an object is visible in the sky.
 * @param obj Pointer to a SKYMAP_search_result_t structure containing the object's position.
 * @return 1 if the object is visible, 0 otherwise.
 */
int SKYMAP_is_object_visible(SKYMAP_search_result_t* obj);

/**
 * @brief Checks if an object is visible in the sky for a given skymap.
 * @param skymap Pointer to a SKYMAP_skymap_t structure.
 * @return 1 if the object is visible, 0 otherwise.
 */
int SKYMAP_is_object_observable(SKYMAP_skymap_t* skymap);

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


SKYMAP_hrs SKYMAP_ra_from_lst_and_ha(SKYMAP_degs lst, SKYMAP_degs ha);


SKYMAP_rads SKYMAP_deg2rad(SKYMAP_degs Deg)
{
    return Deg * SKYMAP_PI / 180;
}

SKYMAP_degs SKYMAP_rad2deg(SKYMAP_rads Rad)
{
    return Rad * 180 / SKYMAP_PI;
}

SKYMAP_degs SKYMAP_h2deg(SKYMAP_hrs h)
{
    return h * 15;
}
SKYMAP_hrs SKYMAP_deg2h(SKYMAP_degs deg)
{
    return deg / 15;
}

SKYMAP_degs SKYMAP_asind(SKYMAP_rads rad)
{
    return asin(SKYMAP_rad2deg(rad));
}

SKYMAP_degs SKYMAP_acosd(SKYMAP_rads rad)
{
    return acos(SKYMAP_rad2deg(rad));
}

SKYMAP_days SKYMAP_j2000(SKYMAP_date_time_values_t* dt)
{

    double JD = (367.0 * (double)dt->year - floor(7.0 * ((double)dt->year + floor(((double)dt->month + 9.0) / 12.0)) / 4.0) - floor(3.0 * (floor(((double)dt->year + ((double)dt->month - 9.0) / 7.0) / 100.0) + 1.0) / 4.0) + floor(275.0 * (double)dt->month / 9.0) + (double)dt->day + 1721028.5 + dt->hour / 24.0);
    double j2000 = JD - 2451545.0;

    return j2000;
}

SKYMAP_degs SKYMAP_local_sidereal_time(SKYMAP_days j2000, SKYMAP_hrs a_time, SKYMAP_degs longitude)
{
    SKYMAP_degs LST = 100.46 + 0.985647 * j2000 + longitude + 15.0 * a_time;
    if (LST < 0)
    {
        LST += 360;
    }
    else if (LST > 360)
    {
        LST -= 360;
    }
    return LST;
}

SKYMAP_degs SKYMAP_hour_angle(SKYMAP_degs lst, SKYMAP_degs right_ascension)
{
    SKYMAP_degs HA = lst - right_ascension;
    if (HA < 0)
    {
        HA += 360;
    }
    else if (HA > 360)
    {
        HA -= 360;
    }
    return HA;
}

SKYMAP_search_result_t SKYMAP_search_for_object(SKYMAP_degs hour_angle, SKYMAP_degs declination, SKYMAP_degs latitude)
{
    /*  math behind calculations -- conversion from HA and DEC to ALT and  AZ
sin(ALT) = sin(DEC) * sin(LAT) + cos(DEC) * cos(LAT) * cos(HA)

ALT = asin(ALT)

           sin(DEC) - sin(ALT) * sin(LAT)
cos(A) = ---------------------------------
                cos(ALT) * cos(LAT)
A = acos(A)
If sin(HA) is negative,then AZ = A, otherwise AZ = 360 - A */
    double sinDEC = sin(SKYMAP_deg2rad(declination));
    double sinHA = sin(SKYMAP_deg2rad(hour_angle));
    double sinLAT = sin(SKYMAP_deg2rad(latitude));
    double cosDEC = cos(SKYMAP_deg2rad(declination));
    double cosHA = cos(SKYMAP_deg2rad(hour_angle));
    double cosLAT = cos(SKYMAP_deg2rad(latitude));
    double sinALT = (sinDEC * sinLAT) + (cosDEC * cosLAT * cosHA);
    SKYMAP_degs ALT = asin(sinALT);
    double cosALT = cos((ALT));
    double cosA = (sinDEC - sinALT * sinLAT) / (cosALT * cosLAT);
    SKYMAP_degs A = acos(cosA);
    A = SKYMAP_rad2deg(A);
    ALT = SKYMAP_rad2deg(ALT);

    SKYMAP_degs AZ;
    if (sinHA > 0)
    {
        AZ = 360 - A;
    }
    else
    {
        AZ = A;
    }

    SKYMAP_search_result_t result;
    result.azimuth = AZ;
    result.altitude = ALT;

    return result;
}

SKYMAP_days SKYMAP_get_j2000(SKYMAP_skymap_t* skymap)
{
    return SKYMAP_j2000(&skymap->date_time);
}

SKYMAP_degs SKYMAP_get_local_sidereal_time(SKYMAP_skymap_t* skymap)
{
    return SKYMAP_local_sidereal_time(
        SKYMAP_get_j2000(skymap),
        skymap->date_time.hour,
        skymap->observer_position.longitude
    );
}

SKYMAP_degs SKYMAP_get_hour_angle(SKYMAP_skymap_t* skymap)
{
    return SKYMAP_hour_angle(
        SKYMAP_get_local_sidereal_time(skymap),
        skymap->object_to_search.right_ascension
    );
}

SKYMAP_search_result_t SKYMAP_observe_object(SKYMAP_skymap_t* skymap)
{
    return SKYMAP_search_for_object(
        SKYMAP_get_hour_angle(skymap),
        skymap->object_to_search.declination,
        skymap->observer_position.latitude
    );
}

void SKYMAP_update(SKYMAP_skymap_t* skymap, SKYMAP_degs latitude, SKYMAP_degs longitude, SKYMAP_degs declination, SKYMAP_degs right_ascension, SKYMAP_years year, SKYMAP_months month, SKYMAP_days day, SKYMAP_hrs a_time)
{
    skymap->observer_position.latitude = latitude;
    skymap->observer_position.longitude = longitude;
    skymap->date_time.year = year;
    skymap->date_time.month = month;
    skymap->date_time.day = day;
    skymap->date_time.hour = a_time;
    skymap->object_to_search.declination = declination;
    skymap->object_to_search.right_ascension = right_ascension;
}

SKYMAP_hrs SKYMAP_hh_mm_ss2UTC(SKYMAP_date_time_values_t* dt, double h, double m, double s, double your_timezone_offset) {
    // Convert hours, minutes, and seconds to total hours
    SKYMAP_hrs total_hours = h + (m / 60.0) + (s / 3600.0);

    // Adjust for the timezone offset
    total_hours -= your_timezone_offset;

    // Update the date_time_values structure if the total hours go past midnight
    if (total_hours < (SKYMAP_hrs)0) {
        total_hours += (SKYMAP_hrs)24;
        dt->day -= (SKYMAP_days)1;
        if ((long)dt->day < 1) {
            dt->month -= (SKYMAP_months)1;
            if ((long)dt->month < 1) {
                dt->month = (SKYMAP_months)12;
                dt->year -= (SKYMAP_years)1;
            }
            // Adjust the day for the previous month
            if ((long)dt->month == 2) {
                if ((long)dt->year % 4 == 0 && ((long)dt->year % 100 != 0 || (long)dt->year % 400 == 0)) {
                    dt->day = (SKYMAP_days)29;
                }
                else {
                    dt->day = (SKYMAP_days)28;
                }
            }
            else if ((long)dt->month == 4 || (long)dt->month == 6 || (long)dt->month == 9 || (long)dt->month == 11) {
                dt->day = (SKYMAP_days)30;
            }
            else {
                dt->day = (SKYMAP_days)31;
            }
        }
    }
    else if (total_hours >= (SKYMAP_hrs)24) {
        total_hours -= (SKYMAP_hrs)24;
        dt->day += (SKYMAP_days)1;
        if ((long)dt->month == 2) {
            if ((long)dt->year % 4 == 0 && ((long)dt->year % 100 != 0 || (long)dt->year % 400 == 0)) {
                if ((long)dt->day > 29) {
                    dt->day = (SKYMAP_days)1;
                    dt->month += (SKYMAP_months)1;
                }
            }
            else {
                if ((long)dt->day > 28) {
                    dt->day = (SKYMAP_days)1;
                    dt->month += (SKYMAP_months)1;
                }
            }
        }
        else if ((long)dt->month == 4 || (long)dt->month == 6 || (long)dt->month == 9 || (long)dt->month == 11) {
            if ((long)dt->day > 30) {
                dt->day = (SKYMAP_days)1;
                dt->month += (SKYMAP_months)1;
            }
        }
        else {
            if ((long)dt->day > 31) {
                dt->day = (SKYMAP_days)1;
                dt->month += (SKYMAP_months)1;
            }
        }
        if ((long)dt->month > 12) {
            dt->month = (SKYMAP_months)1;
            dt->year += (SKYMAP_years)1;
        }
    }

    dt->hour = total_hours;
    return total_hours;
}


void SKYMAP_init(SKYMAP_skymap_t* skymap)
{
    SKYMAP_update(skymap,
        1.0,
        1.0,
        1.0,
        1.0,
        1.0,
        1.0,
        1.0,
        1.0
    );
}

int SKYMAP_is_object_visible(SKYMAP_search_result_t* obj)
{
    return obj->altitude >= 0;
}

int SKYMAP_is_object_observable(SKYMAP_skymap_t* skymap)
{
    SKYMAP_search_result_t result = SKYMAP_observe_object(skymap);
    return SKYMAP_is_object_visible(&result);
}

SKYMAP_hrs SKYMAP_ra_from_lst_and_ha(SKYMAP_degs lst, SKYMAP_degs ha) {
    SKYMAP_hrs ra = lst - ha;

    ra = fmod(ra, 360.0);

    if (ra < 0.0) {
        ra += 360.0;
    }

    return ra;
}

SKYMAP_equatorial_coordinates_t SKYMAP_az_alt_to_ra_dec(
    SKYMAP_geo_position_t* geo_position,
    SKYMAP_local_position_t* local_astr_pos_of_object,
    SKYMAP_date_time_values_t* dt)
{
    SKYMAP_rads az_rad = SKYMAP_deg2rad(local_astr_pos_of_object->azimuth);
    SKYMAP_rads alt_rad = SKYMAP_deg2rad(local_astr_pos_of_object->altitude);
    SKYMAP_rads lat_rad = SKYMAP_deg2rad(geo_position->latitude);

    double sin_dec = sin(alt_rad) * sin(lat_rad) + cos(alt_rad) * cos(lat_rad) * cos(az_rad);

    if (sin_dec > 1.0) sin_dec = 1.0;
    if (sin_dec < -1.0) sin_dec = -1.0;
    SKYMAP_rads dec_rad = asin(sin_dec);

    double cos_ha = (sin(alt_rad) - sin(lat_rad) * sin(dec_rad)) / (cos(lat_rad) * cos(dec_rad));

    if (cos_ha > 1.0) cos_ha = 1.0;
    if (cos_ha < -1.0) cos_ha = -1.0;
    SKYMAP_rads ha_rad = acos(cos_ha);

    // Determine the correct hemisphere for HA using sin(Az)
    if (sin(az_rad) > 0) {
        ha_rad = 2 * SKYMAP_PI - ha_rad;
    }

    SKYMAP_degs hour_angle = SKYMAP_rad2deg(ha_rad);
    SKYMAP_degs declination = SKYMAP_rad2deg(dec_rad);
    SKYMAP_days j2000 = SKYMAP_j2000(dt);
    SKYMAP_degs lst = SKYMAP_local_sidereal_time(j2000, dt->hour, geo_position->longitude);
    SKYMAP_degs ra = SKYMAP_ra_from_lst_and_ha(lst, hour_angle);

    SKYMAP_equatorial_coordinates_t celestial_object;
    celestial_object.declination = declination;
    celestial_object.right_ascension = ra;

    return celestial_object;
}

#endif // SKYMAP_H
