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

#include "TrafficLightSimulatorDriver.h"

#include <macLib.h>
#include <epicsGuard.h>

#include <epicsExport.h>

/// Constructor for the TrafficLightSimulatorDriver class.
/// Calls constructor for the asynPortDriver base class.
/// \param[in] portName @copydoc initArg0
TrafficLightSimulatorDriver::TrafficLightSimulatorDriver(const char *portName) 
   : SimulatorDriver(portName, NUM_PARAMS)
{
	createParam(P_TrafficLight_ValueString, asynParamInt32, &P_TrafficLight_Value);
    createParam(P_TrafficLight_UpdatePeriodString, asynParamInt32, &P_TrafficLight_UpdatePeriod);
    createParam(P_TrafficLight_UpdatePeriodNoiseString, asynParamInt32, &P_TrafficLight_UpdatePeriodNoise);
}

void TrafficLightSimulatorDriver::pollerThread()
{
    static const char* functionName = "TrafficLightSimulatorPoller";   
    lock();
    //Set default values
    setIntegerParam(P_TrafficLight_UpdatePeriod, 10);
    setIntegerParam(P_TrafficLight_Value, 0);
    setIntegerParam(P_TrafficLight_UpdatePeriodNoise, 0);
    
    bool direction = true; //true = going up, false = going down
    
    unlock();
    
	while(true)
	{
		lock();
        
        int value;
        getIntegerParam(P_TrafficLight_Value, &value);    
        
        if (direction)
        {
            //Going up
            if (value == 0)
            {
                value = 1;
            }
            else if (value == 1)
            {
                value = 2;
                direction = false;
            }
            else
            {
                value = 2;
                direction = false;
            }
        }
        else
        {
            //Going down
            if (value == 2)
            {
                value = 1;
            }
            else if (value == 1)
            {
                value = 0;
                direction = true;
            }
            else
            {
                value = 0;
                direction = true;
            }
        }
        
		setIntegerParam(P_TrafficLight_Value, value);    
        
        int period;
        getIntegerParam(P_TrafficLight_UpdatePeriod, &period);
        int noise;
        getIntegerParam(P_TrafficLight_UpdatePeriodNoise, &noise);
        
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

exportSimulator(TrafficLightSimulator)