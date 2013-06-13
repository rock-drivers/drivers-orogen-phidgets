/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "InterfaceTask.hpp"
#include "AnalogDevices.hpp"
#include <phidget21.h>

using namespace phidgets;

InterfaceTask::InterfaceTask(std::string const& name)
    : InterfaceTaskBase(name)
{
}

InterfaceTask::InterfaceTask(std::string const& name, RTT::ExecutionEngine* engine)
    : InterfaceTaskBase(name, engine)
{
}

InterfaceTask::~InterfaceTask()
{
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See InterfaceTask.hpp for more detailed
// documentation about them.

bool InterfaceTask::configureHook()
{
    CPhidgetInterfaceKitHandle phidget;
    CPhidgetInterfaceKit_create(&phidget);
    setPhidgetHandle((CPhidgetHandle)phidget);

    std::vector<phidgets::AnalogDevice> const& devices =
        _analog_devices.get();
    for (size_t i = 0; i < devices.size(); ++i)
    {
        AnalogDevice const& device(devices[i]);
        AnalogDeviceHandler handler(getAnalogDeviceHandler(devices[i].device_type));

        CPhidgetInterfaceKit_set_OnSensorChange_Handler(phidget, handler.changeHandler, NULL);

        RTT::base::PortInterface* port = handler.createPort(device.name);
        addPort(*port);
        mPorts.push_back(port);
        if (device.data_rate)
            CPhidgetInterfaceKit_setDataRate(phidget, device.port, device.data_rate);
        else if (device.sensitivity)
        {
            int trigger = handler.deviceToAnalog(device.sensitivity);
            CPhidgetInterfaceKit_setSensorChangeTrigger(phidget, device.port, trigger);
        }
    }

    if (! InterfaceTaskBase::configureHook())
        return false;
    return true;
}
bool InterfaceTask::startHook()
{
    if (! InterfaceTaskBase::startHook())
        return false;

    return true;
}

std::string InterfaceTask::getPortNameForAnalogInput(int index) const
{
    std::vector<phidgets::AnalogDevice> const& devices =
        _analog_devices.get();
    for (size_t i = 0; i < devices.size(); ++i)
        if (devices[i].port == index)
            return devices[i].name;
    return "";
}

void InterfaceTask::updateHook()
{
    InterfaceTaskBase::updateHook();
}
void InterfaceTask::errorHook()
{
    InterfaceTaskBase::errorHook();
}
void InterfaceTask::stopHook()
{
    InterfaceTaskBase::stopHook();
}
void InterfaceTask::cleanupHook()
{
    InterfaceTaskBase::cleanupHook();
}

