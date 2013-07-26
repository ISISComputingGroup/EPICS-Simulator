#ifndef RANDOMNUMBERSIMULATORDRIVER_H
#define RANDOMNUMBERSIMULATORDRIVER_H
 
#include "SimulatorDriver.h"

class RandomNumberSimulatorDriver : public SimulatorDriver 
{
public:
    RandomNumberSimulatorDriver(const char *portName);
 	static const char* driverName() { return "RandomNumberSimulator"; } // must be same as class name with "Driver" removed, override in subclass

private:

    int P_RandomNumber_Value; // double
    int P_RandomNumber_UpdatePeriod; // double
	#define FIRST_PARAM P_RandomNumber_Value
	#define LAST_PARAM P_RandomNumber_UpdatePeriod
	
	void pollerThread();
};

#define NUM_PARAMS (&LAST_PARAM - &FIRST_PARAM + 1)

#define P_RandomNumber_ValueString	"RANDOMNUMBER_VALUE"
#define P_RandomNumber_UpdatePeriodString	"RANDOMNUMBER_UPDATEPERIOD"

#endif /* RANDOMNUMBERSIMULATORDRIVER_H */
