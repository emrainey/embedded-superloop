# Add the current directory to the module path
list(APPEND CMAKE_MODULE_PATH CMAKE_CURRENT_LIST_DIR)
message(STATUS ">>> Found Jarnax at ${CMAKE_CURRENT_LIST_DIR}")
include(${CMAKE_CURRENT_LIST_DIR}/jarnax.cmake)
