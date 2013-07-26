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

#include "TriangleWaveSimulatorDriver.h"

#include <macLib.h>
#include <epicsGuard.h>

#include <epicsExport.h>

/// Constructor for the TriangleWaveSimulatorDriver class.
/// Calls constructor for the asynPortDriver base class.
/// \param[in] portName @copydoc initArg0
TriangleWaveSimulatorDriver::TriangleWaveSimulatorDriver(const char *portName) 
   : SimulatorDriver(portName, NUM_PARAMS)
{
	createParam(P_TriangleWave_ValueString, asynParamFloat64, &P_TriangleWave_Value);
    createParam(P_TriangleWave_UpdatePeriodString, asynParamFloat64, &P_TriangleWave_UpdatePeriod);
    createParam(P_TriangleWave_DeltaString, asynParamFloat64, &P_TriangleWave_Delta);
}

void TriangleWaveSimulatorDriver::pollerThread()
{
    static const char* functionName = "TriangleWaveSimulatorPoller";   
    lock();
    //Set default values
    setDoubleParam(P_TriangleWave_UpdatePeriod, 1.0);
    setDoubleParam(P_TriangleWave_Value, 0);
    setDoubleParam(P_TriangleWave_Delta, 0.1);
        
    unlock();
    
    bool direction = true; //true = increasing, false = decreasing
    
	while(true)
	{
		lock();
               
        double value, delta;
        getDoubleParam(P_TriangleWave_Value, &value);
        getDoubleParam(P_TriangleWave_Delta, &delta);
        
        //Make sure delta is +ve
        delta = abs(delta);   
        
        if (direction)
        {
            value += delta;
            
            if (value >= 1.0 - (delta/2.0))
            {
                value = 1.0;
                direction = false;
            }
        }
        else
        {
            value -= delta;
            
            if (value <= -1.0 + (delta/2.0))
            {
                value = -1.0;
                direction = true;
            }
        }
        
        if (abs(value) < abs(delta))
        {
            value = 0.0;
        }
        
		setDoubleParam(P_TriangleWave_Value, value);    
        
        double period;
        getDoubleParam(P_TriangleWave_UpdatePeriod, &period);
        
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

exportSimulator(TriangleWaveSimulator)

