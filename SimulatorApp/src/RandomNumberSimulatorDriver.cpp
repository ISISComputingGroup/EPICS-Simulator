#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <exception>
#include <iostream>
#include <time.h>

#include <epicsTypes.h>
#include <epicsTime.h>
#include <epicsThread.h>
#include <epicsString.h>
#include <epicsTimer.h>
#include <epicsMutex.h>
#include <epicsEvent.h>
#include <iocsh.h>

#include "RandomNumberSimulatorDriver.h"

#include <macLib.h>
#include <epicsGuard.h>

#include <epicsExport.h>

/// Constructor for the RandomNumberSimulatorDriver class.
/// Calls constructor for the asynPortDriver base class.
/// \param[in] portName @copydoc initArg0
RandomNumberSimulatorDriver::RandomNumberSimulatorDriver(const char *portName) 
   : SimulatorDriver(portName, NUM_PARAMS)
{
	createParam(P_RandomNumber_ValueString, asynParamFloat64, &P_RandomNumber_Value);
    createParam(P_RandomNumber_UpdatePeriodString, asynParamFloat64, &P_RandomNumber_UpdatePeriod);
}

void RandomNumberSimulatorDriver::pollerThread()
{
    static const char* functionName = "RandomNumberSimulatorPoller";   
    lock();
    //Set default values
    setDoubleParam(P_RandomNumber_UpdatePeriod, 1.0);
    setDoubleParam(P_RandomNumber_Value, 0);
        
    unlock();
    
    srand (time(NULL));
    
	while(true)
	{
		lock();
               
        double value;
        
        value = ((double) rand() / (RAND_MAX));
        
		setDoubleParam(P_RandomNumber_Value, value);    
        
        double period;
        getDoubleParam(P_RandomNumber_UpdatePeriod, &period);
        
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

exportSimulator(RandomNumberSimulator)

