/* Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
namespace modm
{

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

    RF_WAIT_UNTIL(uart.read(c));

    do {
        if (c == '$' || message.size > 81) {
            message.clear();
        }

        message += c;

        if(c == '\r' || c== '\n') {
            RF_CALL(parse());
            message.clear();
        }
    } while(uart.read(c));

    RF_END();
}

template <class Uart>
ResumableResult<void>
NMEA0183<Uart>::parse()
{
    RF_BEGIN();

    // Check for RMC
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
    RF_BEGIN();

    char* field = message.data;
    RMC rmc;

    // Time
    field = strchr(field, ',') + 1;
    rmc.time = (*field == ',') ? 0 : atoi(field);

    // Status
    field = strchr(field, ',') + 1;
    rmc.status = (*field == ',') ? 0 : field;

    // Latitude
    field = strchr(field, ',') + 1;
    rmc.latitude = (*field == ',') ? 0 : parseGeoCoordinate(field);

    // Lat orientation
    field = strchr(field, ',') + 1;
    rmc.latitude = (*field == ',') ? rmc.latitude : rmc.latitude * parseOrientation(field, rmc.latitude);

    // Longitude
    field = strchr(field, ',') + 1;
    rmc.longitude = (*field == ',') ? 0 : parseGeoCoordinate(field);
   
    // Longitude orientation
    field = strchr(field, ',') + 1;
    rmc.longitude = (*field == ',') ? rmc.longitude : rmc.longitude * parseOrientation(field, rmc.longitude);

    // Speed over ground
    field = strchr(field, ',') + 1;
    rmc.speed = (*field == ',') ? 0 : strtof(field, &field);

    // Course
    field = strchr(field, ',') + 1;
    rmc.course = (*field == ',') ? 0 : strtof(field, &field);

    // Date stamp
    field = strchr(field + 1, ',') + 1;
    rmc.date = (*field == ',') ? 0 : atoi(field);

    RF_CALL(onRMC())

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
    double value = strtod(p, &p);
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

}