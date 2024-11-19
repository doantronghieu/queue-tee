cmake_minimum_required(VERSION 3.16)

project(One LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(One
  main.cpp
  animal.h animal.cpp
  laptop.h laptop.cpp
  mammal.h mammal.cpp
  canine.h canine.cpp
  feline.h feline.cpp
  Toaster.h
  Freezer.h
  Microwave.h
  appliance.h appliance.cpp
  agecalc.h agecalc.cpp
  teststaticfunctions.h teststaticfunctions.cpp
  source.h source.cpp
  destination.h destination.cpp
  radio.h radio.cpp
  station.h station.cpp
  testqproperty.h testqproperty.cpp
  watcher.h watcher.cpp
)
target_link_libraries(One Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS One
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
