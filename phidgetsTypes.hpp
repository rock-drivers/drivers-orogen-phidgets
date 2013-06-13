#ifndef phidgets_TYPES_HPP
#define phidgets_TYPES_HPP

#include <base/time.h>
#include <vector>
#include <base/float.h>

namespace phidgets {
    /** Temperature reading */
    struct Temperature
    {
        base::Time time;
        /** Temperature in celsius */
        float value;
    };

    /** Voltage reading */
    struct Voltage
    {
        base::Time time;
        /** Voltage in volts */
        float value;
    };

    /** Humidity reading */
    struct Humidity
    {
        base::Time time;
        /** Whether the humidity reading is absolute or relative */
        bool relative;
        /** Humidity */
        float value;
    };

    /** Types of devices known to the phidget InterfaceTask
     */
    enum DEVICE_TYPES
    {
        /** Raw reading (voltage between 0 and 1) */
        RAW,
        TEMPERATURE_1125,
        HUMIDITY_1125
    };

    /** Description of a device attached to an InterfaceKit analog input */
    struct AnalogDevice
    {
        /** The analog port on which this device is connected */
        int port;
        /** The device name. It is used as the output port name as well */
        std::string name;
        /** The device type. See the documentation of the 'devices'
         * property on phidgets::InterfaceTask for a mapping from device type
         * to data type
         */
        DEVICE_TYPES device_type;
        /** The sensitivity, expressed in the output of the device (i.e.
         * degrees if the device is a temperature sensor). Should be
         * base::unset<float> if the data rate is set as well. 
         */
        float sensitivity;
        /** Sampling period in milliseconds
         *
         * Must be zero if the sensitivity is set. Defaults to 8.
         */
        int data_rate;

        AnalogDevice()
            : port(0)
            , device_type(RAW)
            , sensitivity(base::unset<float>())
            , data_rate(8) {}
    };
}

#endif

