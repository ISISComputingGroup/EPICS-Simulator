#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <exception>
#include <iostream>

#include <epicsTypes.h>
#include <epicsTime.h>
#include <epicsThread.h>
#include <epicsString.h>
#include <epicsTimer.h>
#include <epicsMutex.h>
#include <epicsEvent.h>
#include <iocsh.h>

#include "SineWaveSimulatorDriver.h"

#include <macLib.h>
#include <epicsGuard.h>

#include <epicsExport.h>

#define PI 3.14159265

/// Constructor for the SineWaveSimulatorDriver class.
/// Calls constructor for the asynPortDriver base class.
/// \param[in] portName @copydoc initArg0
SineWaveSimulatorDriver::SineWaveSimulatorDriver(const char *portName) 
  : SimulatorDriver(portName, NUM_PARAMS)
{
	createParam(P_SineWave_ValueString, asynParamFloat64, &P_SineWave_Value);
    createParam(P_SineWave_DeltaString, asynParamFloat64, &P_SineWave_Delta);
    createParam(P_SineWave_UpdatePeriodString, asynParamFloat64, &P_SineWave_UpdatePeriod);
}

void SineWaveSimulatorDriver::pollerThread()
{
    static const char* functionName = "SineWaveSimulatorPoller";   
    lock();
    //Set default values
    setDoubleParam(P_SineWave_UpdatePeriod, 1.0);
    setDoubleParam(P_SineWave_Value, 0);
    setDoubleParam(P_SineWave_Delta, 5.0);
        
    unlock();
    
    int step = 0;
    
	while(true)
	{
		lock();
        
        double delta;
        getDoubleParam(P_SineWave_Delta, &delta);
        
        if (abs(delta) < 1.0) delta = 1.0;

        double value = sin (step * PI/180);
        step += abs(delta);
        
        if (step >= 360)
        {
            step = 0;
        }
        
		setDoubleParam(P_SineWave_Value, value);    
        
        double period;
        getDoubleParam(P_SineWave_UpdatePeriod, &period);
        
        //Just to be safe
        if (period < 0.1) 
        {
            period = 0.1;
        }        
        
        callParamCallbacks();
        
        unlock();

		epicsThreadSleep(period);
	}
}	

exportSimulator(SineWaveSimulator)

