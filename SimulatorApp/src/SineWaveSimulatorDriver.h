#ifndef SINEWAVESIMULATORDRIVER_H
#define SINEWAVESIMULATORDRIVER_H
 
#include "SimulatorDriver.h"

class SineWaveSimulatorDriver : public SimulatorDriver 
{
public:
    SineWaveSimulatorDriver(const char *portName);
 	static const char* driverName() { return "SineWaveSimulator"; } // must be same as class name with "Driver" removed, override in subclass

private:

    int P_SineWave_Value; // double
    int P_SineWave_Delta; // double
    int P_SineWave_UpdatePeriod; // double
	#define FIRST_PARAM P_SineWave_Value
	#define LAST_PARAM P_SineWave_UpdatePeriod
	
	void pollerThread();

};

#define NUM_PARAMS (&LAST_PARAM - &FIRST_PARAM + 1)

#define P_SineWave_ValueString	"SINEWAVE_VALUE"
#define P_SineWave_DeltaString	    "SINEWAVE_DELTA"
#define P_SineWave_UpdatePeriodString	"SINEWAVE_UPDATEPERIOD"

#endif /* SINEWAVESIMULATORDRIVER_H */
