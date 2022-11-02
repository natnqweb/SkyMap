#include "SkyMap.h"

SkyMap::SkyMap(degs lattitude, degs longitude, degs declination, hrs right_ascension, years year, months month, days day, hrs a_time)
{

    _lattitude = lattitude;
    _longitude = longitude;
    _declination = declination;
    _right_ascension = right_ascension;
    m_time = a_time;
    _year = year;
    _month = month;
    _day = day;

    if (_lattitude != 0 && _longitude != 0)
    {
        Calculate_all();
    }
}
SkyMap::SkyMap(ObserverPosition observer, CelestialObject* celestialobject, DateTimeValues datetime)
{

    _lattitude = observer.lattitude;
    _longitude = observer.longitude;
    _declination = celestialobject->GetDec();
    _right_ascension = celestialobject->GetRA();
    m_time = datetime.a_time;
    _year = datetime.year;
    _month = datetime.month;
    _day = datetime.day;

    if (_lattitude != 0 && _longitude != 0)
    {
        Calculate_all();
    }
}
DateTimeValues SkyMap::DateTime(years year, months month, days day, hrs UTC)
{

    _year = year;
    _month = month;
    _day = day;
    m_time = UTC;
    _day += newday;

    return { _year, _month, _day, m_time };
}
DateTimeValues SkyMap::DateTime()
{
    return { _year, _month, _day, m_time };
}

ObserverPosition SkyMap::my_location(degs lattitude, degs longitude)
{

    _lattitude = lattitude;
    _longitude = longitude;
    _observer_position.lattitude = _lattitude;
    _observer_position.longitude = _longitude;
    return { _lattitude, _longitude };
}
ObserverPosition SkyMap::my_location()
{
    return { _lattitude, _longitude };
}

Star SkyMap::star_ra_dec(hrs right_ascension, degs declination)
{
    _right_ascension = right_ascension;
    _declination = declination;
    _star.SetRA(_right_ascension);
    _star.SetDec(_declination);

    return _star;
}

Star SkyMap::star_ra_dec()
{
    return _star;
}

CelestialObject* SkyMap::celestial_object_ra_dec(CelestialObject* celestial_object)
{
    if (celestial_object)
    {
        _right_ascension = celestial_object->GetRA();
        _declination = celestial_object->GetDec();
        _star.SetRA(_right_ascension);
        _star.SetDec(_declination);
    }
    return &_star;
}

CelestialObject* SkyMap::celestial_object_ra_dec()
{
    return &_star;
}

days SkyMap::J2000(years Y, months M, days D, hrs TIME)
{

    double JD = (367 * Y - floor(7 * (Y + floor((M + 9) / 12)) / 4) - floor(3 * (floor((Y + (M - 9) / 7) / 100) + 1) / 4) + floor(275 * M / 9) + D + 1721028.5 + TIME / 24);
    double j2000 = JD - double(2451545);

    return j2000;
}
days SkyMap::J2000()
{

    _JD = (367 * _year - floor(7 * (_year + floor((_month + 9) / 12)) / 4) - floor(3 * (floor((_year + (_month - 9) / 7) / 100) + 1) / 4) + floor(275 * _month / 9) + _day + 1721028.5 + m_time / 24);
    _j2000 = _JD - double(2451545);

    return _j2000;
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
degs SkyMap::Local_Sidereal_Time(days j2000, hrs a_time, degs longitude)
{

    degs LST = 100.46 + 0.985647 * j2000 + longitude + 15 * a_time;
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
degs SkyMap::Local_Sidereal_Time()
{
    _LST = 100.46 + 0.985647 * _j2000 + _longitude + 15 * m_time;
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
degs SkyMap::Hour_Angle(degs LST, hrs right_ascension)
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

degs SkyMap::Hour_Angle()
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

SearchResult SkyMap::calculate_AZ_alt(degs hour_angle, degs declination, degs lattitude)
{
    /*  math behind calculations -- conversion from HA and DEC to ALT and  AZ
sin(ALT) = sin(DEC) * sin(LAT) + cos(DEC) * cos(LAT) * cos(HA)

ALT = asin(ALT)

           sin(DEC) - sin(ALT) * sin(LAT)
cos(A) = ---------------------------------
                cos(ALT) * cos(LAT)
A = acos(A)
If sin(HA) is negative,then AZ = A, otherwise AZ = 360 - A */

    double sinDEC = sinf(deg2rad(declination));
    double sinHA = sinf(deg2rad(hour_angle));
    double sinLAT = sinf(deg2rad(lattitude));
    double cosDEC = cosf(deg2rad(declination));
    double cosHA = cosf(deg2rad(hour_angle));
    double cosLAT = cosf(deg2rad(lattitude));
    double sinALT = (sinDEC * sinLAT) + (cosDEC * cosLAT * cosHA);
    degs ALT = asinf(sinALT);
    double cosALT = cosf((ALT));
    double cosA = (sinDEC - sinALT * sinLAT) / (cosALT * cosLAT);
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
    _search_result.SetAzimuth(AZ);
    _search_result.SetAltitude(ALT);
    return _search_result;
}
double SkyMap::Hh_mm_ss2UTC(double hhh, double mmm, double sss, double your_timezone_offset)
{
    hrs converted_to_utc = hhh + mmm / 60 + sss * 0.000277777778;
    converted_to_utc -= your_timezone_offset;
    if (converted_to_utc >= 24)
    {
        converted_to_utc -= 24;

        newday = 1;
    }
    else if (converted_to_utc < 0)
    {
        converted_to_utc += 24;
        newday = -1;
    }
    else if (converted_to_utc == 24)
    {

        converted_to_utc = 0;
        newday = 1;
    }
    else
    {
        newday = 0;
    }

    return converted_to_utc;
}
void SkyMap::Calculate_all()
{
    J2000();
    Local_Sidereal_Time();
    Hour_Angle();
    calculate_AZ_alt(_hourangle, _declination, _lattitude);
}
degs SkyMap::get_star_Azimuth()
{
    return _search_result.GetAzimuth();
}
degs SkyMap::get_star_Altitude()
{
    return _search_result.GetAltitude();
}

SearchResult SkyMap::get_star_search_result()
{
    return _search_result;
}

void SkyMap::update(degs lattitude, degs longitude, degs declination, hrs right_ascension, years year, months month, days day, hrs a_time)
{

    _lattitude = lattitude;
    _longitude = longitude;
    _declination = declination;
    _right_ascension = right_ascension;
    m_time = a_time;
    _year = year;
    _month = month;
    _day = day;
    _day += newday;
    Calculate_all();
}

CelestialObject* SkyMap::get_celestial_object()
{
    return &_star;
};
bool SkyMap::IsVisible()
{
    if (_search_result.GetAltitude() >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}