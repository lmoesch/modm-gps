/*
 * Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
#ifndef NMEA0183_HPP
#define NMEA0183_HPP

#include <modm/architecture/interface/uart.hpp>

namespace modm
{

template <class Uart>
class NMEA0183 
{
public:
	NMEA0183();
};
}

#include "nmea0183_impl.hpp"

#endif
