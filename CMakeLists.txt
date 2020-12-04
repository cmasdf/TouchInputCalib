CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
PROJECT(TouchScreenDetermination)

set(CMAKE_AUTOMOC on)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/Qt5/Qt5.13.1/5.13.1/gcc_64")

find_package(Qt5 COMPONENTS Core Qml Gui QuickCompiler Quick QuickControls2 REQUIRED)

set(SOURCES
        main.cpp
		backend.cpp
        )

qtquick_compiler_add_resources(RESOURCES qml.qrc)

add_executable(${PROJECT_NAME} ${RESOURCES} ${SOURCES}
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}
        )

target_link_libraries(${PROJECT_NAME} PRIVATE
       	Qt5::Core
		Qt5::Gui
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::Qml
		Xrandr
		X11
)
