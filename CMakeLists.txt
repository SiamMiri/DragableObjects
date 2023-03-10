cmake_minimum_required(VERSION 3.5)

project(DragableObjects VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Set the source directory
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(FORMS_DIR ${CMAKE_SOURCE_DIR}/forms)

include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})
include_directories(${FORMS_DIR})

set(PROJECT_SOURCES
        main.cpp
        ${SOURCE_DIR}/boxwidget.cpp
        ${SOURCE_DIR}/pane.cpp
        ${SOURCE_DIR}/mainwindow.cpp
        ${INCLUDE_DIR}/mainwindow.h #${INCLUDE_DIR}/
        ${INCLUDE_DIR}/boxwidget.h
        ${INCLUDE_DIR}/pane.h
        ${INCLUDE_DIR}/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DragableObjects
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DragableObjects APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DragableObjects SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DragableObjects
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DragableObjects PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(DragableObjects PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS DragableObjects
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DragableObjects)
endif()
