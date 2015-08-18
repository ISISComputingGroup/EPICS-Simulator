#ifndef BOOLEANSIMULATORDRIVER_H
#define BOOLEANSIMULATORDRIVER_H
 
#include "SimulatorDriver.h"

class BooleanSimulatorDriver : public SimulatorDriver 
{
public:
    BooleanSimulatorDriver(const char *portName);
	static const char* driverName() { return "BooleanSimulator"; } // must be same as class name with "Driver" removed, override in subclass

private:

    int P_Boolean_Value; // int
    int P_Boolean_UpdatePeriodNoise; // int
    int P_Boolean_UpdatePeriod; // int
	#define FIRST_PARAM P_Boolean_Value
	#define LAST_PARAM P_Boolean_UpdatePeriod
	
	virtual void pollerThread();

};

#define NUM_PARAMS (&LAST_PARAM - &FIRST_PARAM + 1)

#define P_Boolean_ValueString	"BOOLEAN_VALUE"
#define P_Boolean_UpdatePeriodNoiseString	"BOOLEAN_UPDATEPERIODNOISE"
#define P_Boolean_UpdatePeriodString	"BOOLEAN_UPDATEPERIOD"

#endif /* BOOLEANSIMULATORDRIVER_H */
