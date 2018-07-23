#########################################################
project(libCommon CXX)

#########################################################
# The library itself
set(targetName "libCommon")

add_library(${targetName} INTERFACE)

target_include_directories(${targetName} INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}/include/public/"
)

# target_link_libraries(${targetName} INTERFACE "boost_filesystem_shared")


#########################################################
# The library's tests.	
add_subdirectory(testing)