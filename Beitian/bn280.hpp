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
class BN280 : public NMEA0183<Uart>, protected nmea0183
{
public:
    BN280();

    void
    getGeoCoordinates(double& latitude, double& longitude);

private:
    double latitude;
    double longitude;

    ResumableResult<void>
    onRMC(RMC rmc) override;
};

}

#include "bn280_impl.hpp"

#endif