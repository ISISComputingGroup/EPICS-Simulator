#ifndef TRIANGLEWAVESIMULATORDRIVER_H
#define TRIANGLEWAVESIMULATORDRIVER_H
 
#include "SimulatorDriver.h"

class TriangleWaveSimulatorDriver : public SimulatorDriver 
{
public:
    TriangleWaveSimulatorDriver(const char *portName);
 	static const char* driverName() { return "TriangleWaveSimulator"; } // must be same as class name with "Driver" removed, override in subclass

private:

    int P_TriangleWave_Value; // double
    int P_TriangleWave_Delta; // double
    int P_TriangleWave_UpdatePeriod; // double
	#define FIRST_PARAM P_TriangleWave_Value
	#define LAST_PARAM P_TriangleWave_UpdatePeriod
	
	void pollerThread();
};

#define NUM_PARAMS (&LAST_PARAM - &FIRST_PARAM + 1)

#define P_TriangleWave_ValueString	"TRIANGLEWAVE_VALUE"
#define P_TriangleWave_DeltaString	"TRIANGLEWAVE_DELTA"
#define P_TriangleWave_UpdatePeriodString	"TRIANGLEWAVE_UPDATEPERIOD"

#endif /* TRIANGLEWAVESIMULATORDRIVER_H */
