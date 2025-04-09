# Add the current directory to the module path
list(APPEND CMAKE_MODULE_PATH CMAKE_CURRENT_LIST_DIR)
message(STATUS ">>> Found Embedded SuperLoop at ${CMAKE_CURRENT_LIST_DIR}")
include(${CMAKE_CURRENT_LIST_DIR}/embedded-superloop.cmake)
