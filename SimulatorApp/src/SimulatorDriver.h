#ifndef SIMULATORDRIVER_H
#define SIMULATORDRIVER_H
 
#include "asynPortDriver.h"

class SimulatorDriver : public asynPortDriver 
{
public:
    SimulatorDriver(const char *portName, int numParams);
 	static void pollerThreadC(void* arg);
	static const char* driverName() { return "SimulatorDriver"; }  // must be same as class name, override in subclass

private:
	virtual void pollerThread(); // usually provided by subclass
};

template <class T>
static int SimulatorConfigure(const char *portName)
{
	try
	{
        new T(portName);
        return(asynSuccess);			
	}
	catch(const std::exception& ex)
	{
		std::cerr << T::driverName() << " configure failed: " << ex.what() << std::endl;
		return(asynError);
	}
}

template <class T>
static void initCallFunc(const iocshArgBuf *args)
{
    SimulatorConfigure<T>(args[0].sval);
}

#define exportSimulator(__name) \
    extern "C" \
    { \
        static void __name##Register(void) \
        { \
	        static const iocshArg initArg0 = { "portName", iocshArgString} ; \
	        static const iocshArg * const initArgs[] = { &initArg0 }; \
	        static const iocshFuncDef initFuncDef = { #__name "Configure", sizeof(initArgs) / sizeof(iocshArg*), initArgs}; \
			iocshRegister(&initFuncDef, initCallFunc<__name##Driver>); \
        } \
		epicsExportRegistrar(__name##Register); \
    }

#endif /* SIMULATORDRIVER_H */
