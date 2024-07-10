# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Dad_n_Me_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Dad_n_Me_autogen.dir\\ParseCache.txt"
  "Dad_n_Me_autogen"
  )
endif()
