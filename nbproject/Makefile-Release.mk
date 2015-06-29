#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Manager.o \
	${OBJECTDIR}/Map.o \
	${OBJECTDIR}/MapSearchNode.o \
	${OBJECTDIR}/PathPlanner.o \
	${OBJECTDIR}/Plans/Plan.o \
	${OBJECTDIR}/Plans/PlnObstacleAvoid.o \
	${OBJECTDIR}/Robot.o \
	${OBJECTDIR}/WayPointsManager.o \
	${OBJECTDIR}/behaviors/Behavior.o \
	${OBJECTDIR}/behaviors/TurnRight.o \
	${OBJECTDIR}/lodepng.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/pngUtil.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robotics-demo

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robotics-demo: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robotics-demo ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Manager.o: Manager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Manager.o Manager.cpp

${OBJECTDIR}/Map.o: Map.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Map.o Map.cpp

${OBJECTDIR}/MapSearchNode.o: MapSearchNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MapSearchNode.o MapSearchNode.cpp

${OBJECTDIR}/PathPlanner.o: PathPlanner.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PathPlanner.o PathPlanner.cpp

${OBJECTDIR}/Plans/Plan.o: Plans/Plan.cpp 
	${MKDIR} -p ${OBJECTDIR}/Plans
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Plans/Plan.o Plans/Plan.cpp

${OBJECTDIR}/Plans/PlnObstacleAvoid.o: Plans/PlnObstacleAvoid.cpp 
	${MKDIR} -p ${OBJECTDIR}/Plans
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Plans/PlnObstacleAvoid.o Plans/PlnObstacleAvoid.cpp

${OBJECTDIR}/Robot.o: Robot.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Robot.o Robot.cpp

${OBJECTDIR}/WayPointsManager.o: WayPointsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WayPointsManager.o WayPointsManager.cpp

${OBJECTDIR}/behaviors/Behavior.o: behaviors/Behavior.cpp 
	${MKDIR} -p ${OBJECTDIR}/behaviors
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/behaviors/Behavior.o behaviors/Behavior.cpp

${OBJECTDIR}/behaviors/TurnRight.o: behaviors/TurnRight.cpp 
	${MKDIR} -p ${OBJECTDIR}/behaviors
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/behaviors/TurnRight.o behaviors/TurnRight.cpp

${OBJECTDIR}/lodepng.o: lodepng.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lodepng.o lodepng.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/pngUtil.o: pngUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pngUtil.o pngUtil.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robotics-demo

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
