#include "SkyMap.h"

SkyMap::SkyMap(degs lattitude, degs longitude, degs declination, hrs right_ascension, years year, months month, days day, hrs time)
{

    _lattitude = lattitude;
    _longitude = longitude;
    _declination = declination;
    _right_ascension = right_ascension;
    _time = time;
    _year = year;
    _month = month;
    _day = day;

    if (_lattitude != 0 && _longitude != 0)
    {
        Calculate_all();
    }
}

degs *SkyMap::my_location(degs lattitude, degs longitude)
{
    if (lattitude != 0 && longitude != 0)
    {
        _lattitude = lattitude;
        _longitude = longitude;
        _MyLocation[0] = _lattitude;
        _MyLocation[1] = _longitude;
    }

    _MyLocation[0] = _lattitude;
    _MyLocation[1] = _longitude;
    return _MyLocation;
}
float *SkyMap::star_ra_dec(hrs right_ascension, degs declination)
{
    if (right_ascension != 0 && declination != 0)
    {
        _right_ascension = right_ascension;
        _declination = declination;
        _star_ra_dec[0] = _right_ascension;
        _star_ra_dec[1] = _declination;
    }

    _star_ra_dec[0] = _right_ascension;
    _star_ra_dec[1] = _declination;
    return _star_ra_dec;
}

days SkyMap::J2000(years Y, months M, days D, hrs TIME)
{
    if (Y != 0 && M != 0 && D != 0 && TIME != 0)
    {
        float JD = (367 * Y - floor(7 * (Y + floor((M + 9) / 12)) / 4) - floor(3 * (floor((Y + (M - 9) / 7) / 100) + 1) / 4) + floor(275 * M / 9) + D + 1721028.5 + TIME / 24);
        float j2000 = JD - float(2451545);

        return j2000;
    }
    else
    {
        _JD = (367 * _year - floor(7 * (_year + floor((_month + 9) / 12)) / 4) - floor(3 * (floor((_year + (_month - 9) / 7) / 100) + 1) / 4) + floor(275 * _month / 9) + _day + 1721028.5 + _time / 24);
        _j2000 = _JD - float(2451545);

        return _j2000;
    }
}
degs SkyMap::asind(rads rad)
{
    return asin(rad2deg(rad));
}
degs SkyMap::acosd(rads rad)
{
    return acos(rad2deg(rad));
}
degs SkyMap::h2deg(hrs h)
{
    return h * 15;
}
hrs SkyMap::deg2h(degs Deg)
{
    return Deg / 15;
}
rads SkyMap::deg2rad(degs Deg)
{
    return Deg * 3.14159265358979 / 180;
}
degs SkyMap::rad2deg(rads Rad)
{
    return Rad * 180 / 3.14159265358979;
}
degs SkyMap::Local_Sidereal_Time(days j2000, hrs time, degs longitude)
{
    if (j2000 != 0 && time != 0 && longitude != 0)
    {
        degs LST = 100.46 + 0.985647 * j2000 + longitude + 15 * time;
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
    else
    {
        _LST = 100.46 + 0.985647 * _j2000 + _longitude + 15 * _time;
        if (_LST < 0)
        {
            _LST += 360;
        }
        else if (_LST > 360)
        {
            _LST -= 360;
        }
        _local_sidereal_time = _LST;
        return _LST;
    }
}
degs SkyMap::Hour_Angle(degs LST, hrs right_ascension)
{
    if (LST != 0 && right_ascension != 0)
    {
        degs HA = LST - right_ascension;
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
    else
    {
        _HA = _local_sidereal_time - _right_ascension;
        if (_HA < 0)
        {
            _HA += 360;
        }
        else if (_HA > 360)
        {
            _HA -= 360;
        }
        _hourangle = _HA;
        return _hourangle;
    }
}
degs *SkyMap::calculate_AZ_alt(degs hour_angle, degs declination, degs lattitude)
{
    /*  math behind calculations -- conversion from HA and DEC to ALT and  AZ
sin(ALT) = sin(DEC) * sin(LAT) + cos(DEC) * cos(LAT) * cos(HA)

ALT = asin(ALT)

           sin(DEC) - sin(ALT) * sin(LAT)
cos(A) = ---------------------------------
                cos(ALT) * cos(LAT)
A = acos(A)
If sin(HA) is negative,then AZ = A, otherwise AZ = 360 - A */

    float sinDEC = sinf(deg2rad(declination));
    float sinHA = sinf(deg2rad(hour_angle));
    float sinLAT = sinf(deg2rad(lattitude));
    float cosDEC = cosf(deg2rad(declination));
    float cosHA = cosf(deg2rad(hour_angle));
    float cosLAT = cosf(deg2rad(lattitude));
    float sinALT = (sinDEC * sinLAT) + (cosDEC * cosLAT * cosHA);
    degs ALT = asinf(sinALT);
    float cosALT = cosf((ALT));
    float cosA = (sinDEC - sinALT * sinLAT) / (cosALT * cosLAT);
    degs A = acosf(cosA);
    A = rad2deg(A);
    ALT = rad2deg(ALT);

    degs AZ;
    if (sinHA > 0)

    {
        AZ = 360 - A;
    }
    else
    {
        AZ = A;
    }

    _Star_ALT_AZ[0] = ALT;
    _Star_ALT_AZ[1] = AZ;
    return _Star_ALT_AZ;
}
float SkyMap::Hh_mm_ss2UTC(unsigned int hhh, unsigned int mmm, unsigned int sss, unsigned int your_timezone_offset)
{
    hrs converted_to_utc = hhh + mmm / 60 + sss * 0.000277777778;
    converted_to_utc += your_timezone_offset;
    return converted_to_utc;
}
void SkyMap::Calculate_all()
{
    J2000();
    Local_Sidereal_Time();
    Hour_Angle();
    calculate_AZ_alt(_hourangle, _declination, _lattitude);
}
degs SkyMap::get_star_Azymuth()
{
    return _Star_ALT_AZ[1];
}
degs SkyMap::get_star_Altitude()
{
    return _Star_ALT_AZ[0];
}
void SkyMap::update(degs lattitude, degs longitude, degs declination, hrs right_ascension, years year, months month, days day, hrs time)
{

    _lattitude = lattitude;
    _longitude = longitude;
    _declination = declination;
    _right_ascension = right_ascension;
    _time = time;
    _year = year;
    _month = month;
    _day = day;
    Calculate_all();
}