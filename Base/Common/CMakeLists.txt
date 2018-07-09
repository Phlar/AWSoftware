#########################################################
project(libCommon CXX)

#########################################################
# The library itself
set(targetName "libCommon")

add_library(${targetName} INTERFACE)

target_include_directories(${targetName} INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}/include/public/base.common/"
)
