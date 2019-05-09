CMAKE_MINIMUM_REQUIRED(VERSION 3.14 FATAL_ERROR)

PROJECT(unit)



SET(unit_src "${PROJECT_SOURCE_DIR}/unit/")


ADD_SUBDIRECTORY("./unit/" "./unit/")


ADD_SUBDIRECTORY("./example/" "./example/")


