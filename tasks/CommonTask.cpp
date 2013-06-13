/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "CommonTask.hpp"
#include <phidget21.h>

using namespace phidgets;

CommonTask::CommonTask(std::string const& name)
    : CommonTaskBase(name)
{
}

CommonTask::CommonTask(std::string const& name, RTT::ExecutionEngine* engine)
    : CommonTaskBase(name, engine)
{
}

CommonTask::~CommonTask()
{
}


void CommonTask::setPhidgetHandle(CPhidgetHandle handle)
{
    mPhidget = handle;
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See CommonTask.hpp for more detailed
// documentation about them.

bool CommonTask::configureHook()
{
    if (! CommonTaskBase::configureHook())
        return false;

    CPhidget_open(mPhidget, -1);
    return true;
}
bool CommonTask::startHook()
{
    if (! CommonTaskBase::startHook())
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
void CommonTask::updateHook()
{
    CommonTaskBase::updateHook();
}
void CommonTask::errorHook()
{
    CommonTaskBase::errorHook();
}
void CommonTask::stopHook()
{
    CommonTaskBase::stopHook();
}
void CommonTask::cleanupHook()
{
    CommonTaskBase::cleanupHook();
}
