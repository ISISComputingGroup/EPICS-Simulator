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

#include "SquareWaveSimulatorDriver.h"

#include <macLib.h>
#include <epicsGuard.h>

#include <epicsExport.h>

/// Constructor for the SquareWaveSimulatorDriver class.
/// Calls constructor for the asynPortDriver base class.
/// \param[in] portName @copydoc initArg0
SquareWaveSimulatorDriver::SquareWaveSimulatorDriver(const char *portName) 
   : SimulatorDriver(portName, NUM_PARAMS)
{
	createParam(P_SquareWave_ValueString, asynParamFloat64, &P_SquareWave_Value);
    createParam(P_SquareWave_UpdatePeriodString, asynParamFloat64, &P_SquareWave_UpdatePeriod);
}

void SquareWaveSimulatorDriver::pollerThread()
{
    static const char* functionName = "SquareWaveSimulatorPoller";   
    lock();
    //Set default values
    setDoubleParam(P_SquareWave_UpdatePeriod, 5.0);
    setDoubleParam(P_SquareWave_Value, 1.0);
        
    unlock();
    
    int step = 0;
    int stepsize = 5;
    
	while(true)
	{
		lock();
        
        double value;
        getDoubleParam(P_SquareWave_Value, &value);
        
        if (value <= 0)
        {
            value = 1.0;
        }
        else
        {
            value = -1.0;
        }
        
		setDoubleParam(P_SquareWave_Value, value);    
        
        double period;
        getDoubleParam(P_SquareWave_UpdatePeriod, &period);
        
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

exportSimulator(SquareWaveSimulator)