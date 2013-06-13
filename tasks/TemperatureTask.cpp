/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "TemperatureTask.hpp"
#include <phidget21.h>

using namespace phidgets;

TemperatureTask::TemperatureTask(std::string const& name)
    : TemperatureTaskBase(name)
{
}

TemperatureTask::TemperatureTask(std::string const& name, RTT::ExecutionEngine* engine)
    : TemperatureTaskBase(name, engine)
{
}

TemperatureTask::~TemperatureTask()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See TemperatureTask.hpp for more detailed
// documentation about them.

bool TemperatureTask::configureHook()
{
    CPhidgetTemperatureSensor_create(&mPhidget);
    if (! TemperatureTaskBase::configureHook())
        return false;

    CPhidget_open((CPhidgetHandle)mPhidget, -1);

    return true;
}
bool TemperatureTask::startHook()
{
    if (! TemperatureTaskBase::startHook())
        return false;
    int result = CPhidget_waitForAttachment((CPhidgetHandle)mPhidget, 10000);
    if (result)
    {
        char const* err;
        CPhidget_getErrorDescription(result, &err);
        log(RTT::Error) << "Problem waiting for attachment: " << err << RTT::endlog();
        return false;
    }

    return true;
}
void TemperatureTask::updateHook()
{
    double temperature;
    int result = CPhidgetTemperatureSensor_getTemperature(mPhidget, 0, &temperature);
    if (result)
    {
        char const* err;
        CPhidget_getErrorDescription(result, &err);
        log(RTT::Error) << "failed to read temperature: " << err << RTT::endlog();
        return exception(PHIDGET_ERROR);
    }

    Temperature sample;
    sample.time = base::Time::now();
    sample.value = temperature;
    _temperature_samples.write(sample);

    TemperatureTaskBase::updateHook();
}
void TemperatureTask::errorHook()
{
    TemperatureTaskBase::errorHook();
}
void TemperatureTask::stopHook()
{
    TemperatureTaskBase::stopHook();
}
void TemperatureTask::cleanupHook()
{
    CPhidget_close((CPhidgetHandle)mPhidget);
    CPhidget_delete((CPhidgetHandle)mPhidget);
    TemperatureTaskBase::cleanupHook();
}
