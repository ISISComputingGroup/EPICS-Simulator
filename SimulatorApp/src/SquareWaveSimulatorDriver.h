#ifndef SQUAREWAVESIMULATORDRIVER_H
#define SQUAREWAVESIMULATORDRIVER_H
 
#include "SimulatorDriver.h"

class SquareWaveSimulatorDriver : public SimulatorDriver 
{
public:
    SquareWaveSimulatorDriver(const char *portName);
	static const char* driverName() { return "SquareWaveSimulator"; } // must be same as class name with "Driver" removed, override in subclass

private:

    int P_SquareWave_Value; // double
    int P_SquareWave_UpdatePeriod; // double
	#define FIRST_PARAM P_SquareWave_Value
	#define LAST_PARAM P_SquareWave_UpdatePeriod
	
	void pollerThread();
};

#define NUM_PARAMS (&LAST_PARAM - &FIRST_PARAM + 1)

#define P_SquareWave_ValueString	"SQUAREWAVE_VALUE"
#define P_SquareWave_UpdatePeriodString	"SQUAREWAVE_UPDATEPERIOD"

#endif /* SQUAREWAVESIMULATORDRIVER_H */
