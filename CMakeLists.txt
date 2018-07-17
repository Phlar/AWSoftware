cmake_minimum_required(VERSION 3.4.3)

project("AWSoftware" CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BooL "Export all symbols.")
add_definitions("-DBOOST_ALL_NO_LIB") # Disable boost's auto-link feature using MSVC.

# This has to happen at the very beginning as it determines system- / build-settings used thoughout the project.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/AWCMake)

# Where to place all imported targets at.
set(3RD_PARTY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty")

# First for the generic no-config case (e.g. with mingw)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
# Second, for multi-config builds (e.g. msvc)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/lib")
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

#################################################################################
set(GTEST_URL "https://www.dropbox.com/s/k2ev201xjp7vvv1/gTest_gMock-1.8.0.zip?dl=0")
set(GTEST_ARCHIVE_NAME "gTest_gMock-1.8.0.zip")
set(GTEST_ARCHIVE_MD5 "1c7192fb6766a88a4ca9581e42531ac7")
set(GTEST_TARGET_NAME "gTest")
downloadAndImportTarget(${GTEST_URL} "${3RD_PARTY_DIRECTORY}/${GTEST_ARCHIVE_NAME}" EXPECTED_MD5 ${GTEST_ARCHIVE_MD5})
#################################################################################

#################################################################################
set(BOOST_URL "https://www.dropbox.com/s/po86yvmvzyhctwn/boost-1.66.0.zip?dl=0")			
set(BOOST_ARCHIVE_NAME "boost-1.66.0.zip")
set(BOOST_ARCHIVE_MD5 "de9e34711b8589425c2d36dc9d072bd5")
set(BOOST_TARGET_NAME "boost")
downloadAndImportTarget(${BOOST_URL} "${3RD_PARTY_DIRECTORY}/${BOOST_ARCHIVE_NAME}" EXPECTED_MD5 ${GTEST_ARCHIVE_MD5})
#################################################################################

enable_testing()

# Set the linker flags for all targets depending on the configuration settings.
setGlobalLinkerFlags()

add_subdirectory(Base)