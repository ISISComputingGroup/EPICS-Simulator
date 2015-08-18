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

#include "SimulatorDriver.h"

#include <macLib.h>
#include <epicsGuard.h>

#include <epicsExport.h>

static epicsThreadOnceId onceId = EPICS_THREAD_ONCE_INIT;

/// Constructor for the booleanSimulatorDriver class.
/// Calls constructor for the asynPortDriver base class.
/// \param[in] portName @copydoc initArg0
SimulatorDriver::SimulatorDriver(const char *portName, int numParams) 
   : asynPortDriver(portName, 
                    0, /* maxAddr */ 
                    numParams,
                    asynInt32Mask | asynInt32ArrayMask | asynFloat64Mask | asynFloat64ArrayMask | asynOctetMask | asynDrvUserMask, /* Interface mask */
                    asynInt32Mask | asynInt32ArrayMask | asynFloat64Mask | asynFloat64ArrayMask | asynOctetMask,  /* Interrupt mask */
                    ASYN_CANBLOCK, /* asynFlags.  This driver can block but it is not multi-device */
                    1, /* Autoconnect */
                    0, /* Default priority */
                    0)	/* Default stack size*/			
{
    const char *functionName = "SimulatorDriver";

    if (epicsThreadCreate("SimulatorPoller",
                          epicsThreadPriorityMedium,
                          epicsThreadGetStackSize(epicsThreadStackMedium),
                          (EPICSTHREADFUNC)pollerThreadC, this) == 0)
    {
        printf("%s:%s: epicsThreadCreate failure\n", driverName(), functionName);
        return;
    }
}

void SimulatorDriver::pollerThreadC(void* arg)
{ 
    SimulatorDriver* driver = (SimulatorDriver*)arg; 
	driver->pollerThread();
}

void SimulatorDriver::pollerThread()
{
}

