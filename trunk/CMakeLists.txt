cmake_minimum_required(VERSION 2.6)

# set project's name
PROJECT(Boggle)

# OS X specific
IF(APPLE)
  SET(PROGRAM_NAME Boggle)
  # SET(MACOSX_BUNDLE_ICON_FILE Speedcrunch.icns)
  SET(MACOSX_BUNDLE_SHORT_VERSION_STRING 0.1) 
  SET(MACOSX_BUNDLE_VERSION 0.1 alpha)
  SET(MACOSX_BUNDLE_LONG_VERSION_STRING Version 0.1 alpha)
  # SET(CMAKE_OSX_ARCHITECTURES ppc;i386 ) #Comment out if not universal binary
ELSE(APPLE)
  SET(PROGRAM_NAME boggle)
ENDIF(APPLE)

# with SET() command you can change variables or define new ones
# here we define SOURCES variable that contains a list of all .cpp files
# note that we don't need \ at the end of line
SET(SOURCES
	sources/dicetray.cpp
	sources/die.cpp
	sources/lexicon.cpp
	sources/mainwindow.cpp
	sources/main.cpp
)

# another list, this time it includes all header files that should be treated with moc
SET(MOC_HEADERS
	sources/mainwindow.h
)

# some .ui files
SET(UIS
	sources/mainwindow.ui
)

# and finally an resource file
SET(RESOURCES
	resources/files.qrc
)

# enable ALL warnings
ADD_DEFINITIONS(-Wall)

# by default only QtCore and QtGui modules are enabled
# other modules must be enabled like this:
# SET( QT_USE_QT3SUPPORT TRUE )   
# SET( QT_USE_QTXML TRUE )

# this command finds Qt4 libraries and sets all required variables
FIND_PACKAGE(Qt4 REQUIRED)

# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
INCLUDE(${QT_USE_FILE})

# this command will generate rules that will run rcc on all files from RESOURCES
# in result RC_SOURCES variable will contain paths to files produced by rcc
QT4_ADD_RESOURCES(RC_SOURCES ${RESOURCES})

# this will run uic on .ui files:
QT4_WRAP_UI(UI_HEADERS ${UIS})

# and finally this will run moc:
QT4_WRAP_CPP(MOC_SOURCES ${MOC_HEADERS})

# we need this to be able to include headers produced by uic in our code
# (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# --------------------------------------------------
# For distribution on OS X; this is going to need
# some more work to begin working more smoothly
# --------------------------------------------------
#IF(APPLE)
#	ADD_EXECUTABLE(${PROGRAM_NAME} MACOSX_BUNDLE ${SOURCES} ${MOC_SOURCES} ${RC_SOURCES} ${UI_HEADERS})
#    ADD_CUSTOM_COMMAND(TARGET ${PROGRAM_NAME} POST_BUILD
#    	COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}.app/Contents/Resources
#    	# COMMAND cp ${MACOSX_BUNDLE_ICON_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}.app/Contents/Resources
#		# COMMAND cp *.qm ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}.app/Contents/Resources 
#	)
#ELSE(APPLE)
#	ADD_EXECUTABLE(${PROGRAM_NAME} ${SOURCES} ${MOC_SOURCES} ${RC_SOURCES} ${UI_HEADERS})
#ENDIF(APPLE)

# here we instruct CMake to build "sample" executable from all of the source files
ADD_EXECUTABLE(${PROGRAM_NAME} ${SOURCES} ${MOC_SOURCES} ${RC_SOURCES} ${UI_HEADERS})

# last thing we have to do is to tell CMake what libraries our executable needs,
# luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
TARGET_LINK_LIBRARIES(${PROGRAM_NAME} ${QT_LIBRARIES})