CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
PROJECT(TouchinputCalibration)

set(CMAKE_AUTOMOC on)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

option(CI_BUILD "Build project via ci" OFF)

option(CROSS_BUILD "Build project cross for arm64" OFF)

if(("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux") OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin"))
	set(OPERATING_SYSTEM "linux")
	set(FRAMEWORK_OS "linux")

elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
	set(OPERATING_SYSTEM "windows")
	set(FRAMEWORK_OS "winpc")

else()
	message(FATAL_ERROR "\
        Unsupported operating system detected. (${CMAKE_SYSTEM_NAME})
        The following OS' are currently supported:
        \t * Windows
        \t * Linux
    ")
endif()

if (("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "aarch64") OR (("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "arm") AND CROSS_BUILD))
	set(FRAMEWORK_LIB_SUFFIX aarch64)
	add_definitions("-DTARGET")

	if (CROSS_BUILD)
		#the following values are specific to the cross build docker image and should not be changed

		message("Set docker qt path for cross arm64 build")
		set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/usr/local/qt5-cross")

		# add target lib paths to rpath (for cross linker)
		set(CMAKE_EXE_LINKER_FLAGS
				"${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu'")
		set(CMAKE_EXE_LINKER_FLAGS
				"${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'${CMAKE_SYSROOT}/lib/aarch64-linux-gnu'")

	else ()
		set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/Qt5.14")
	endif ()
elseif(("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" OR "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "AMD64") AND (NOT CROSS_BUILD))

	set(FRAMEWORK_LIB_SUFFIX amd64)
	add_definitions("-DHOST")

else()
	message("${CMAKE_SYSTEM_PROCESSOR}")
endif()

set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)
find_package(Qt5 COMPONENTS Core Qml Gui QuickCompiler Quick QuickControls2 REQUIRED)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(SOURCES
        main.cpp
		src/MainAreaBackend.cpp
		src/Monitor.cpp
		src/InputDevice.cpp
		src/Mapping.cpp
		model/AppWindowModel.cpp
		model/AppWindowData.cpp
		)

qtquick_compiler_add_resources(RESOURCES qml.qrc)

add_executable(${PROJECT_NAME} ${RESOURCES} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
       	Qt5::Core
		Qt5::Gui
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::Qml
		X11
		Xrandr
		Xi
)
