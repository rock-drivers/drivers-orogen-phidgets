#ifndef phidgets_TYPES_HPP
#define phidgets_TYPES_HPP

#include <base/time.h>

namespace phidgets {
    struct Temperature
    {
        base::Time time;
        /** Temperature in celsius */
        float temperature;
    };
}

#endif

