#include "nmea0183.hpp"
/* Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
template <typename Uart>
NMEA0183<Uart>::NMEA0183()
{

}

template <typename Uart>
ResumableResult<void>
NMEA0183<Uart>::update()
{
    uint8_t c;

    RF_BEGIN();

    RF_WAIT_UNTIL(Uart::read(c) || Uart::hasError());

    if (Uart::hasError()) {
        Uart::clearError();
        message.clear();            
        Board::usb::ioStream << "E"; 
    } else {
        do {
            if (c == '$' || message.size > 81) {
                message.clear();
            }
            message += (char) c;

            if(c == '\r' || c == '\n') {
                RF_CALL(parse());
                message.clear();
            }
        } while(Uart::read(c));
    }

    RF_END();
}

template <class Uart>
ResumableResult<void>
NMEA0183<Uart>::parse()
{
    RF_BEGIN();
 
    //Check for RMC
    if (strncmp((message.data + 3), "RMC", 3) == 0) {
        RF_CALL(parseRMC());
    } 

    // Check for GSA
    if (strncmp((message.data + 3), "GSA", 3) == 0) {
        RF_CALL(parseGSA());
    } 

    RF_END();
}

template <class Uart>
ResumableResult<void>
NMEA0183<Uart>::parseRMC()
{
    char* field = message.data;
    RMC rmc;

    RF_BEGIN();

    // Time
    field = strchr(field, ',') + 1;
    rmc.time = (*field == ',') ? 0 : atoi(field);

    // Status
    field = strchr(field, ',') + 1;
    rmc.status = (*field == ',') ? 0 : *field;

    // Latitude
    field = strchr(field, ',') + 1;
    rmc.latitude = (*field == ',') ? 0 : NMEA0183<Uart>::parseGeoCoordinate(field);

    // Lat orientation
    field = strchr(field, ',') + 1;
    rmc.latitude = (*field == ',') ? rmc.latitude : rmc.latitude * NMEA0183<Uart>::parseOrientation(field, rmc.latitude);

    // Longitude
    field = strchr(field, ',') + 1;
    rmc.longitude = (*field == ',') ? 0 : NMEA0183<Uart>::parseGeoCoordinate(field);
   
    // Longitude orientation
    field = strchr(field, ',') + 1;
    rmc.longitude = (*field == ',') ? rmc.longitude : rmc.longitude * NMEA0183<Uart>::parseOrientation(field, rmc.longitude);

    // Speed over ground
    field = strchr(field, ',') + 1;
    rmc.speed = (*field == ',') ? 0 : NMEA0183<Uart>::strtof(field);

    // Course
    field = strchr(field, ',') + 1;
    rmc.course = (*field == ',') ? 0 : NMEA0183<Uart>::strtof(field);

    // Date stamp
    field = strchr(field + 1, ',') + 1;
    rmc.date = (*field == ',') ? 0 : atoi(field);

    RF_CALL(onRMC(rmc));

    RF_END();
}

template <class Uart>
ResumableResult<void> 
NMEA0183<Uart>::parseGSA()
{
    RF_BEGIN();
    RF_END();
}

template <class Uart>
double NMEA0183<Uart>::parseGeoCoordinate(char *field)
{
    double value = NMEA0183<Uart>::strtod(field);
    uint8_t degree = (int) (value / 100);
    double minutes = (value - 100 * degree);

    return  (double) (degree + (minutes / 60));
}

template <class Uart>
double NMEA0183<Uart>::parseOrientation(char *field, double geoCoordinate)
{
    bool setNegative = (*field == 'W' || *field == 'S') && geoCoordinate > 0;
    bool setPositive = (*field == 'E' || *field == 'N') && geoCoordinate < 0;
    
    if (setNegative || setPositive) {
        return -1;
    } else {
        return 1;
    }
}

template <class Uart>
double NMEA0183<Uart>::strtod(char *str)
{
    double result = 0.0;
    double fraction = 0.1;
    bool negative = false;

    // Handle negative sign
    if (*str == '-')
    {
        negative = true;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Parse digits before decimal point
    while (isdigit(*str))
    {
        result = (result * (double) 10.0) + (*str - '0');
        str++;
    }

    // Parse digits after decimal point
    if (*str == '.')
    {
        str++;

        while (isdigit(*str))
        {
            result += (*str - '0') * fraction;
            fraction *= (double) 0.1;
            str++;
        }
    }

    // Apply negative sign if necessary
    if (negative)
    {
        result = -result;
    }

    return result;
}

template <class Uart>
float NMEA0183<Uart>::strtof(char *str)
{
    float result = 0.0;
    float fraction = 0.1;
    bool negative = false;

    // Handle negative sign
    if (*str == '-')
    {
        negative = true;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Parse digits before decimal point
    while (isdigit(*str))
    {
        result = (result * 10.0f) + (*str - '0');
        str++;
    }

    // Parse digits after decimal point
    if (*str == '.')
    {
        str++;

        while (isdigit(*str))
        {
            result += (*str - '0') * fraction;
            fraction *= 0.1f;
            str++;
        }
    }

    // Apply negative sign if necessary
    if (negative)
    {
        result = -result;
    }

    return result;
}
