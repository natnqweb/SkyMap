#include <SkyMap.h>

#define _EPS_PRECISION (0.02) 
// depending on board you might not get exact same result because of floating point aritmetics
// if possible use board that supports 64-bit double precision
// also if you have a way to get utc datatime directly do not convert it using SKYMAP_hh_mm_ss2UTC but assign it to dt.hour directly

void test_SKYMAP_sirius_los_angeles() {
    // Directly use UTC values for time and date
    SKYMAP_skymap_t skymap;
    SKYMAP_init(&skymap);

    skymap.observer_position.latitude = 34.06; // Los Angeles coordinates
    skymap.observer_position.longitude = -118.24358;

    // 20:30 Los Angeles time in UTC
    skymap.date_time.day = 4;
    skymap.date_time.month = 9;
    skymap.date_time.year = 2021;
    skymap.date_time.hour = 20.5; // UTC

    //Sirius
    skymap.object_to_search.right_ascension = 101.52;
    skymap.object_to_search.declination = -16.7424;

    SKYMAP_search_result_t result = SKYMAP_observe_object(&skymap);

    SKYMAP_astronomical_position_t resulta = SKYMAP_az_alt_to_ra_dec(&skymap.observer_position, &result, &skymap.date_time);

    if (fabs(resulta.right_ascension - skymap.object_to_search.right_ascension) < _EPS_PRECISION && fabs(resulta.declination - skymap.object_to_search.declination) < _EPS_PRECISION) {
        Serial.println("\nTest success\n");
    }
    else {
        Serial.println("\nTest failed\n");
    }
}

void test_SKYMAP_sun_equator_noon() {
    // Directly use UTC values for time and date (Summer Solstice at UTC)
    double year = 2021, month = 6, day = 21, hour = 12; // Summer Solstice at UTC
    double latitude = 0.0, longitude = 0.0; // Equator, Prime Meridian
    double RA = 0.0, dec = 23.44; // Sun RA and Dec at summer solstice
    SKYMAP_date_time_values_t dt;
    dt.day = day;
    dt.month = month;
    dt.year = year;
    dt.hour = hour;

    // Calculate J2000, Local Sidereal Time, Hour Angle, and Alt/Az
    double j2000 = SKYMAP_j2000(&dt);
    double Local_sidereal_time = SKYMAP_local_sidereal_time(j2000, dt.hour, longitude);
    double Hour_angle = SKYMAP_hour_angle(Local_sidereal_time, RA);
    SKYMAP_search_result_t result = SKYMAP_search_for_object(Hour_angle, dec, latitude);

    // Perform conversion from Alt/Az back to RA/Dec
    SKYMAP_geo_position_t geo_position;
    geo_position.latitude = latitude;
    geo_position.longitude = longitude;

    SKYMAP_astronomical_position_t resulta = SKYMAP_az_alt_to_ra_dec(&geo_position, &result, &dt);

    if (((fabs(resulta.right_ascension - RA) < _EPS_PRECISION) || ((fabs(resulta.right_ascension - 360.0)) < _EPS_PRECISION)) && fabs(resulta.declination - dec) < _EPS_PRECISION) {
        Serial.println("\nTest success\n");
    }
    else {
        Serial.println("\nTest failed\n");
    }
}

void test_SKYMAP_orion_sydney() {
    // Directly use UTC values for time and date
    double year = 2021, month = 12, day = 15, hour = 22; // 22:00 Sydney time in UTC
    double latitude = -33.8688, longitude = 151.2093; // Sydney, Australia
    double RA = 83.822, dec = -5.391; // Alnilam, the central star of Orion’s Belt
    SKYMAP_date_time_values_t dt;
    dt.day = day;
    dt.month = month;
    dt.year = year;
    dt.hour = hour;

    // Calculate J2000, Local Sidereal Time, Hour Angle, and Alt/Az
    double j2000 = SKYMAP_j2000(&dt);
    double Local_sidereal_time = SKYMAP_local_sidereal_time(j2000, dt.hour, longitude);
    double Hour_angle = SKYMAP_hour_angle(Local_sidereal_time, RA);
    SKYMAP_search_result_t result = SKYMAP_search_for_object(Hour_angle, dec, latitude);

    // Perform conversion from Alt/Az back to RA/Dec
    SKYMAP_geo_position_t geo_position;
    geo_position.latitude = latitude;
    geo_position.longitude = longitude;
    SKYMAP_astronomical_position_t resulta = SKYMAP_az_alt_to_ra_dec(&geo_position, &result, &dt);

    if (fabs(resulta.right_ascension - RA) < _EPS_PRECISION && fabs(resulta.declination - dec) < _EPS_PRECISION) {
        Serial.println("\nTest success\n");
    }
    else {
        Serial.println("\nTest failed\n");
    }
}

void test_SKYMAP_polaris_nyc() {
    // Directly use UTC values for time and date
    double year = 2021.0, month = 11.0, day = 28.0, hour = 20.0; // 20:00 UTC
    double latitude = 40.7128, longitude = -74.0060; // New York City coordinates
    double RA = 2.530, dec = 89.264; // Polaris RA and Dec
    SKYMAP_date_time_values_t dt;
    dt.day = day;
    dt.month = month;
    dt.year = year;
    dt.hour = hour;
    // Calculate J2000, Local Sidereal Time, Hour Angle, and Alt/Az
    double j2000 = SKYMAP_j2000(&dt);
    double Local_sidereal_time = SKYMAP_local_sidereal_time(j2000, dt.hour, longitude);
    double Hour_angle = SKYMAP_hour_angle(Local_sidereal_time, RA);
    SKYMAP_search_result_t result = SKYMAP_search_for_object(Hour_angle, dec, latitude);

    // Perform conversion from Alt/Az back to RA/Dec
    SKYMAP_geo_position_t geo_position;
    geo_position.latitude = latitude;
    geo_position.longitude = longitude;

    SKYMAP_astronomical_position_t resulta = SKYMAP_az_alt_to_ra_dec(&geo_position, &result, &dt);
    Serial.print("Ra = ");
    Serial.print(RA);
    Serial.print(" dec = ");
    Serial.print(dec);
    Serial.print(" result ra = ");
    Serial.print(resulta.right_ascension);
    Serial.print(" result dec = ");
    Serial.println((resulta.declination));
    if (fabs(resulta.right_ascension - RA) < _EPS_PRECISION && fabs(resulta.declination - dec) < _EPS_PRECISION) {
        Serial.println("\nTest success\n");
    }
    else {
        Serial.println("\nTest failed\n");
    }
}

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
    SKYMAP_equatorial_coordinates_t resulta = SKYMAP_az_alt_to_ra_dec(&geo_position, &local_astr_pos_of_object, &dt);
    Serial.print("result ra = ");
    Serial.print(resulta.right_ascension);
    Serial.print(" result dec = ");
    Serial.println((resulta.declination));
}


void setup()
{
    Serial.begin(115200);
    test_SKYMAP_polaris_nyc();
    test_SKYMAP_orion_sydney();
    test_SKYMAP_sun_equator_noon();
    test_SKYMAP_sirius_los_angeles();
    test_SKYMAP_directly_az_alt_to_ra_dec(); // direct conversion az alt to ra dec
}

void loop()
{

}