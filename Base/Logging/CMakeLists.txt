#########################################################
enable_language(CXX)

#########################################################
# The library itself
set(targetName "libLogging")

add_library(${targetName} SHARED "")

target_sources(${targetName}
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/include/public/base.logging/ILogger.hpp"
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/include/internal/base.logging.internal/Logger.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/include/internal/base.logging.internal/FileLoggerStrategy.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/internal/base.logging.internal/FileLoggerStrategy.cpp"
)

target_include_directories(${targetName}
	PUBLIC
		 "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
)

target_link_libraries(${targetName} "libMModule" "libCommon")

setTargetCompileOptions(${targetName})

#########################################################
# The gmock target
# Merely in order to make the target visible in an IDE.
set(targetName_gmock "${targetName}_gmock")
add_library(${targetName_gmock} STATIC "")

target_sources(${targetName_gmock}
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/gmock/include/public/base.logging.gmock/MockILogger.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/gmock/src/public/base.logging.gmock/MockILogger.cpp"
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
# add_subdirectory(testing)