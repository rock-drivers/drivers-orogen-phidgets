/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "TemperatureTask.hpp"

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
    if (! TemperatureTaskBase::configureHook())
        return false;
    return true;
}
bool TemperatureTask::startHook()
{
    if (! TemperatureTaskBase::startHook())
        return false;
    return true;
}
void TemperatureTask::updateHook()
{
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
    TemperatureTaskBase::cleanupHook();
}
