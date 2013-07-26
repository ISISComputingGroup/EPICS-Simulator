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

#include "BooleanSimulatorDriver.h"

#include <macLib.h>
#include <epicsGuard.h>

#include <epicsExport.h>

/// Constructor for the booleanSimulatorDriver class.
/// Calls constructor for the asynPortDriver base class.
/// \param[in] portName @copydoc initArg0
BooleanSimulatorDriver::BooleanSimulatorDriver(const char *portName) 
   : SimulatorDriver(portName, NUM_PARAMS)
{
	createParam(P_Boolean_ValueString, asynParamInt32, &P_Boolean_Value);
    createParam(P_Boolean_UpdatePeriodString, asynParamInt32, &P_Boolean_UpdatePeriod);
    createParam(P_Boolean_UpdatePeriodNoiseString, asynParamInt32, &P_Boolean_UpdatePeriodNoise);
}

void BooleanSimulatorDriver::pollerThread()
{
    static const char* functionName = "BooleanSimulatorPoller";   
    lock();
    //Set default values
    setIntegerParam(P_Boolean_UpdatePeriod, 10);
    setIntegerParam(P_Boolean_Value, 0);
    setIntegerParam(P_Boolean_UpdatePeriodNoise, 0);  
    
    unlock();
    
	while(true)
	{
		lock();
        
        int value;
        getIntegerParam(P_Boolean_Value, &value);    
        
        if (value == 0)
        {
            value = 1;
        }
        else
        {
            value = 0;
        }
        
		setIntegerParam(P_Boolean_Value, value);    
        
        int period;
        getIntegerParam(P_Boolean_UpdatePeriod, &period);
        int noise;
        getIntegerParam(P_Boolean_UpdatePeriodNoise, &noise);
        
        callParamCallbacks();
        
        unlock();
        
        if (noise > 0)
        {            
            if (rand() % 2 == 0)
            {
                period = period - rand() % (noise);
            }
            else
            {
                period = period + rand() % (noise);
            }
        }
        
        //Just to be safe
        if (period < 1) period = 1;
        
		epicsThreadSleep(period);
	}
}	

exportSimulator(BooleanSimulator)
