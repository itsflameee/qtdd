# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/qtdd_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/qtdd_autogen.dir/ParseCache.txt"
  "qtdd_autogen"
  )
endif()
