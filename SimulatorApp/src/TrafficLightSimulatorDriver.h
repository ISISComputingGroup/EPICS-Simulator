#ifndef TRAFFICLIGHTSIMULATORDRIVER_H
#define TRAFFICLIGHTSIMULATORDRIVER_H
 
#include "SimulatorDriver.h"

class TrafficLightSimulatorDriver : public SimulatorDriver 
{
public:
    TrafficLightSimulatorDriver(const char *portName);
	static const char* driverName() { return "TrafficLightSimulator"; } // must be same as class name with "Driver" removed, override in subclass

private:

    int P_TrafficLight_Value; // int
    int P_TrafficLight_UpdatePeriodNoise; // int
    int P_TrafficLight_UpdatePeriod; // int
	#define FIRST_PARAM P_TrafficLight_Value
	#define LAST_PARAM P_TrafficLight_UpdatePeriod
	
	void pollerThread();
};

#define NUM_PARAMS (&LAST_PARAM - &FIRST_PARAM + 1)

#define P_TrafficLight_ValueString	"TRAFFICLIGHT_VALUE"
#define P_TrafficLight_UpdatePeriodNoiseString	"TRAFFICLIGHT_UPDATEPERIODNOISE"
#define P_TrafficLight_UpdatePeriodString	"TRAFFICLIGHT_UPDATEPERIOD"

#endif /* TRAFFICLIGHTSIMULATORDRIVER_H */
