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
_CPhidget* CommonTask::getPhidgetHandle() const
{
    return mPhidget;
}

void CommonTask::phidgetHandleError(int errorCode)
{
    if (errorCode != 0)
    {
        const char *errorDescription;
        phidgetHandleError(CPhidget_getErrorDescription(errorCode, &errorDescription));
        throw std::runtime_error(errorDescription);
    }
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See CommonTask.hpp for more detailed
// documentation about them.

bool CommonTask::configureHook()
{
    if (! CommonTaskBase::configureHook())
        return false;

    phidgetHandleError(CPhidget_open(mPhidget, -1));
    return true;
}
bool CommonTask::startHook()
{
    if (! CommonTaskBase::startHook())
        return false;

    phidgetHandleError(CPhidget_waitForAttachment((CPhidgetHandle)mPhidget, 2000));
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
    CPhidget_close(mPhidget);
    CPhidget_delete(mPhidget);
    CommonTaskBase::cleanupHook();
}

