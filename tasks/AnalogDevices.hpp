#ifndef PHIDGETS_ANALOG_DEVICES_HPP
#define PHIDGETS_ANALOG_DEVICES_HPP

#include <phidgets/phidgetsTypes.hpp>
#include <rtt/base/PortInterface.hpp>

struct _CPhidgetInterfaceKit;

namespace phidgets
{
    struct AnalogDeviceHandler
    {
        typedef int (*ChangeHandlerFn)(_CPhidgetInterfaceKit* phidget, void* usrptr, int Index, int Value);
        typedef int (*DeviceToAnalogFn)(float value);
        typedef RTT::base::PortInterface* (*PortCreationFn)(std::string const& name);

        DEVICE_TYPES deviceType;
        ChangeHandlerFn changeHandler;
        DeviceToAnalogFn deviceToAnalog;
        PortCreationFn createPort;

        AnalogDeviceHandler(DEVICE_TYPES deviceType, ChangeHandlerFn changeHandler, DeviceToAnalogFn deviceToAnalog, PortCreationFn createPort)
            : deviceType(deviceType)
            , changeHandler(changeHandler)
            , deviceToAnalog(deviceToAnalog)
            , createPort(createPort)
        {}
    };

    AnalogDeviceHandler getAnalogDeviceHandler(DEVICE_TYPES deviceType);
}

#endif
