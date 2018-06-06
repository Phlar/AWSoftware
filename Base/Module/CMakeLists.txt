#########################################################
#project(libBaseModule LANGUAGES C CXX)

enable_language(CXX)

#########################################################
# The library itself
set(targetName "libModule")

add_library(${targetName} SHARED "")

target_sources(${targetName}
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/include/public/base.module/IModule.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/include/public/base.module/ModuleProvider.hpp"
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/src/public/base.module/ModuleProvider.cpp"
)

target_include_directories(${targetName}
	PUBLIC
		 "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
)

setTargetCompileOptions(${targetName})

#########################################################
# The gmock target
# Merely in order to make the target visible in an IDE.
# add_library("${libModule}_gmock" INTERFACE)
set(targetName_gmock "${targetName}_gmock")
add_library(${targetName_gmock} STATIC "")

target_sources(${targetName_gmock}
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/gmock/include/public/base.module.gmock/MockIModule.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/gmock/src/public/base.module.gmock/MockIModule.cpp"
)

target_include_directories(${targetName_gmock}
	PUBLIC
		 "${CMAKE_CURRENT_SOURCE_DIR}/gmock/include/public/"
	PRIVATE
		 "${CMAKE_CURRENT_SOURCE_DIR}/include/public/"
)

target_link_libraries(${targetName_gmock} gMock_static ${targetName})

setTargetCompileOptions(${targetName_gmock})

#########################################################
# The library's tests.	
add_subdirectory(testing)