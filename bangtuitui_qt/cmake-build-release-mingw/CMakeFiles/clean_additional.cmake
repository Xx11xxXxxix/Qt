# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\bangtuitui_qt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\bangtuitui_qt_autogen.dir\\ParseCache.txt"
  "bangtuitui_qt_autogen"
  )
endif()
