This oroGen project handles the phidget devices. See www.phidgets.com for
details on phidgets

There are two types of phidgets: the USB-interfaced phidgets and the
analog-interfaced ones. The first ones have their own oroGen task, the second
ones are interfaced through the InterfaceKit phidget, e.g. the InterfaceTask

Analog Phidgets
---------------
To interface an analog phidget in oroGen, you have to use the InterfaceTask.
This task has support to either read the raw voltage data, or (generally more
interesting), to convert the data to the domain of the sensor (e.g. temperature
for a temperature sensor).

In both cases, each of the board's analog input for which you want data to be
exported needs to be declared in the 'analog\_devices' property of the task.
These data structure declare the device type (if some special handler is already
defined for your particular analog sensor), or RAW to get voltage readings, as
well as the trigger type (data rate or sensitivity) and the name of the port on
whcih the data should be exported.

scripts/phidget\_analog\_read allows to (1) see how this can be done in practice
and (2) test whether you can talk to your phidget InterfaceKit already. Simply
start the script without argument to get a help message

For instance, to read a 1125 phidget temperature sensor:

    scripts/phidget_analog_read temperature1125 0

Adding support for analog devices to the InterfaceTask
---------------------------
All analog devices that can be handled by the InterfaceTask directly need to be
declared:

1. in the ENUM\_TYPES enumeration in phidgetTypes.hpp
2. in the tasks/AnalogDevices.hpp file.

In both cases, it is best to choose a name that both describe what the sensor
does (e.g. "temperature", 'IRDistance") and the phidget model number.

In tasks/AnalogDevices.hpp, you need to declare:

 * a change handler. It is called by the Phidget API when a new value arrives,
   and should write the relevant data type on a port. Look at the existing
   functions for examples.
        int changeHandler(CPhidgetInterfaceKitHandler* phidget, InterfaceTask* usrptr, int Index, int Value);
 * a method that converts device-specific values (i.e. temperature) to
   phidget-analog values. This is the inverse of the function that Phidget
   documents with their analog sensors. It has the signature
        int deviceToAnalogFn(float value);
 * finally, a method that creates a port of a type relevant for the analog
   device. See existing examples
        RTT::base::PortInterface* portCreation(std::string const& name);

Finally, you register all these methods in the getAnalogDeviceHandler function
at the bottom of the file.

Creating new tasks for Phidgets that are not handled
---------------------------

