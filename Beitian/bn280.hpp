/* Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
#ifndef BN280_HPP
#define BN280_HPP

#include "../protocol/nmea0183_definitions.hpp"
#include "../protocol/nmea0183.hpp"

using namespace modm;

namespace Beitian 
{

template <class Uart>
class BN280 : public NMEA0183<Uart>
{
public:
    volatile double latitude;
    volatile double longitude;

    BN280();

private:
    ResumableResult<void>
    onRMC(NMEA0183<Uart>::RMC rmc) override;
};

}

#include "bn280_impl.hpp"

#endif