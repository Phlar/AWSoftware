#########################################################
project(libSceneGraphBase CXX)

#########################################################
# The library itself
set(targetName "libSceneGraphBase")

add_library(${targetName} SHARED "")

target_sources(${targetName}
	PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/public/scenegraph.base/INodeProperty.hpp"
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/include/internal/scenegraph.base.internal/INode.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/internal/scenegraph.base.internal/INodeVisitor.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/internal/scenegraph.base.internal/NodeInstance.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/internal/scenegraph.base.internal/NodeOccurrence.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/internal/scenegraph.base.internal/TypedNodeInstance.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/internal/scenegraph.base.internal/TypedNodeOccurrence.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/internal/scenegraph.base.internal/NodeInstance.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/internal/scenegraph.base.internal/NodeOccurrence.cpp"
)

target_include_directories(${targetName}
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/include/public"
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/include/internal"
)

target_link_libraries(${targetName} "libModule" "libLogging")

setTargetCompileOptions(${targetName})

#########################################################
# The library's tests.	
add_subdirectory(testing)