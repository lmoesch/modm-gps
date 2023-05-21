/*
 * Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
#ifndef NMEA0183_HPP
#define NMEA0183_HPP

#include <cstring>

#include <modm/io/iodevice_wrapper.hpp>

#include "message_buffer.hpp"
#include "nmea0183_definitions.hpp"

namespace modm
{

template <class Uart>
class NMEA0183: public nmea0183, protected NestedResumable<2>
{
public:
	NMEA0183();

protected:
    ResumableResult<void>
    update();

    virtual ResumableResult<void>
    onRMC() {
        RF_BEGIN();
        RF_END();
    };

    virtual ResumableResult<void> 
    onGSA() {
        RF_BEGIN();
        RF_END();
    };

private:
    MessageBuffer<82> message;
    IODeviceWrapper<Uart, modm::IOBuffer::BlockIfFull> uart;
    
    void
    parse();

    void
    parseRMC();

    void
    parseGSA();

};
}

#include "nmea0183_impl.hpp"

#endif
