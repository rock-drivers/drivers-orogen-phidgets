#include "AnalogDevices.hpp"
#include <phidgets/Types.hpp>
#include "InterfaceTask.hpp"
#include <phidget21.h>

using namespace phidgets;

template<typename T>
void writeSample(void* usrptr, int Index, T const& sample)
{
    InterfaceTask* task = reinterpret_cast<InterfaceTask*>(usrptr);
    std::string port_name = task->getPortNameForAnalogInput(Index);
    if (!port_name.empty())
        dynamic_cast<RTT::OutputPort<T>*>(task->getPort(port_name))->write(sample);
}

static int Raw_ChangedHandler(CPhidgetInterfaceKitHandle IFK,
       void* usrptr, int Index, int Value)
{
    phidgets::Voltage sample;
    sample.time = base::Time::now();
    sample.value = 5.0 * Value / 1000;
    writeSample(usrptr, Index, sample);
    return 0;
}
static int Raw_DeviceToAnalog(float value)
{
    return static_cast<int>((value * 1000) / 5);
}

static int Temperature1125_ChangedHandler(CPhidgetInterfaceKitHandle IFK,
       void* usrptr, int Index, int Value)
{
    phidgets::Temperature sample;
    sample.time = base::Time::now();
    sample.value = (static_cast<float>(Value) * 0.22222) - 61.1;

    writeSample(usrptr, Index, sample);
    return 0;
}
static int Temperature1125_DeviceToAnalog(float value)
{
    return static_cast<int>((value + 61.1) / 0.22222);
}

static int Humidity1125_ChangedHandler(CPhidgetInterfaceKitHandle IFK,
       void* usrptr, int Index, int Value)
{
    phidgets::Humidity sample;
    sample.time = base::Time::now();
    sample.relative = true;
    sample.value = (static_cast<float>(Value) * 0.1906) - 40.2;

    writeSample(usrptr, Index, sample);
    return 0;
}
static int Humidity1125_DeviceToAnalog(float value)
{
    return static_cast<int>((value + 40.2) / 0.1906);
}

AnalogDeviceHandler phidgets::getAnalogDeviceHandler(DEVICE_TYPES deviceType)
{
    switch(deviceType)
    {
        case RAW:
            return AnalogDeviceHandler(RAW, Raw_ChangedHandler, Raw_DeviceToAnalog);
        case TEMPERATURE_1125:
            return AnalogDeviceHandler(TEMPERATURE_1125, Temperature1125_ChangedHandler, Temperature1125_DeviceToAnalog);
        case HUMIDITY_1125:
            return AnalogDeviceHandler(HUMIDITY_1125, Humidity1125_ChangedHandler, Humidity1125_DeviceToAnalog);
        default: throw std::runtime_error("I do not know how to handle this analog device");
    }
}



