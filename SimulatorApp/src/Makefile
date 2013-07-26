TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

LIBRARY_IOC += SimulatorSupport

SimulatorSupport_SRCS += SimulatorDriver.cpp BooleanSimulatorDriver.cpp TrafficLightSimulatorDriver.cpp SineWaveSimulatorDriver.cpp SquareWaveSimulatorDriver.cpp TriangleWaveSimulatorDriver.cpp RandomNumberSimulatorDriver.cpp
SimulatorSupport_LIBS += asyn
SimulatorSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================
# Build the IOC application

PROD_IOC = Simulator
# Simulator.dbd will be created and installed
DBD += Simulator.dbd

# Simulator_registerRecordDeviceDriver.cpp derives from BooleanSimulator.dbd
Simulator_SRCS += Simulator_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
Simulator_SRCS_DEFAULT += SimulatorMain.cpp
Simulator_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#Simulator_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

Simulator_LIBS += SimulatorSupport asyn

# Finally link to the EPICS Base libraries
Simulator_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

