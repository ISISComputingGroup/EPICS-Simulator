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

DBD += SimulatorSupport.dbd

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

