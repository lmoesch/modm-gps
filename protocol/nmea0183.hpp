/*
 * Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
#ifndef NMEA0183_HPP
#define NMEA0183_HPP

#include <cstring>

#include "message_buffer.hpp"
#include "nmea0183_definitions.hpp"

using namespace modm;
template <class Uart>
class NMEA0183: public nmea0183, protected NestedResumable<5>
{
public:
	NMEA0183();

    ResumableResult<void>
    update();

protected:
    virtual ResumableResult<void>
    onRMC(RMC rmc) {
        RF_BEGIN();
        RF_END();
    };

    virtual ResumableResult<void> 
    onGSA(GSA gsa) {
        RF_BEGIN();
        RF_END();
    };

private:
    MessageBuffer<82> message;
    
    ResumableResult<void>
    parse();

    ResumableResult<void>
    parseRMC();

    ResumableResult<void>
    parseGSA();

    static double
    parseGeoCoordinate(char* field);

    static double
    parseOrientation(char* field, double geoCoordinate);

    static double
    strtod(char* str);

    static float
    strtof(char* str);

};


#include "nmea0183_impl.hpp"

#endif
