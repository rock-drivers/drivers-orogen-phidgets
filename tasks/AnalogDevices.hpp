#ifndef PHIDGETS_ANALOG_DEVICES_HPP
#define PHIDGETS_ANALOG_DEVICES_HPP

#include <phidgets/phidgetsTypes.hpp>

struct _CPhidgetInterfaceKit;

namespace phidgets
{
    struct AnalogDeviceHandler
    {
        typedef int (*ChangeHandlerFn)(_CPhidgetInterfaceKit* phidget, void* usrptr, int Index, int Value);
        typedef int (*DeviceToAnalogFn)(float value);

        DEVICE_TYPES deviceType;
        ChangeHandlerFn changeHandler;
        DeviceToAnalogFn deviceToAnalog;

        AnalogDeviceHandler(DEVICE_TYPES deviceType, ChangeHandlerFn changeHandler, DeviceToAnalogFn deviceToAnalog)
            : deviceType(deviceType)
            , changeHandler(changeHandler)
            , deviceToAnalog(deviceToAnalog) {}
    };

    AnalogDeviceHandler getAnalogDeviceHandler(DEVICE_TYPES deviceType);
}

#endif
