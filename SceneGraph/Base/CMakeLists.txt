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

target_link_libraries(${targetName} "libModule" "libCommon" "libLogging")

setTargetCompileOptions(${targetName})

#########################################################
# The gmock target
# Merely in order to make the target visible in an IDE.
set(targetName_gmock "${targetName}_gmock")
add_library(${targetName_gmock} STATIC "")

target_sources(${targetName_gmock}
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/gmock/include/internal/scenegraph.base.internal.gmock/MockINode.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/gmock/include/internal/scenegraph.base.internal.gmock/MockINodeVisitor.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/gmock/src/internal/scenegraph.base.internal.gmock/MockINode.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/gmock/src/internal/scenegraph.base.internal.gmock/MockINodeVisitor.cpp"
)

# Start
# Todo: Workaround in order to retrieve also the "private" directories....
# In general create a gmock-helper set like for the test-creation...
set(originalIncludeDirectories "")
get_target_property(originalIncludeDirectories ${targetName_gmock} "INCLUDE_DIRECTORIES")
set(adjustedIncludeDirectories ${${originalIncludeDirectories}})

get_target_property(directories ${targetName} "INCLUDE_DIRECTORIES")
foreach(directory ${directories})
    if(directory)
        list(APPEND adjustedIncludeDirectories "${directory}")
    endif()
endforeach()
# End

target_include_directories(${targetName_gmock}
	PUBLIC
		 "${CMAKE_CURRENT_SOURCE_DIR}/gmock/include/public/"
         "${adjustedIncludeDirectories}"
	PRIVATE
         "${CMAKE_CURRENT_SOURCE_DIR}/gmock/include/internal/"
)

target_link_libraries(${targetName_gmock} gMock_static ${targetName})

setTargetCompileOptions(${targetName_gmock})

#########################################################
# The library's tests.	
add_subdirectory(testing)