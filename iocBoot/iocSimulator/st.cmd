#!../../bin/windows-x64/Simulator

## You may have to change Simulator to something else
## everywhere it appears in this file

< envPaths

epicsEnvSet "IOCNAME" "$(P=$(MYPVPREFIX))SIMULATOR" 
epicsEnvSet "IOCSTATS_DB" "$(DEVIOCSTATS)/db/iocAdminSoft.db" 

cd ${TOP}

## Register all support components
dbLoadDatabase "dbd/Simulator.dbd"
Simulator_registerRecordDeviceDriver pdbbase

BooleanSimulatorConfigure("booleansimulator")
TrafficLightSimulatorConfigure("trafficlightsimulator")
SineWaveSimulatorConfigure("sinewavesimulator")
SquareWaveSimulatorConfigure("squarewavesimulator")
TriangleWaveSimulatorConfigure("trianglewavesimulator")
RandomNumberSimulatorConfigure("randomnumbersimulator")

## Load record instances
dbLoadRecords("$(TOP)/db/Simulator.db","P=$(IOCNAME)")
#dbLoadRecords("$(IOCSTATS_DB)","IOC=$(IOCNAME)")  

cd ${TOP}/iocBoot/${IOC}
iocInit

