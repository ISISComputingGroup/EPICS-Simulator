#!../../bin/windows-x64/SimulatorTest

## You may have to change SimulatorTest to something else
## everywhere it appears in this file

# Increase this if you get <<TRUNCATED>> or discarded messages warnings in your errlog output
errlogInit2(65536, 256)

< envPaths

epicsEnvSet "IOCNAME" "$(P=$(MYPVPREFIX))SIMULATOR" 
epicsEnvSet "IOCSTATS_DB" "$(DEVIOCSTATS)/db/iocAdminSoft.db" 

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/SimulatorTest.dbd"
SimulatorTest_registerRecordDeviceDriver pdbbase
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

