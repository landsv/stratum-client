cmake_minimum_required(VERSION 3.3)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(HUNTER_CONFIGURATION_TYPES Release)
include(HunterGate)
HunterGate(
URL "https://github.com/ruslo/hunter/archive/v0.18.57.tar.gz"
SHA1 "435b09a4eec7fd58486bfb61efb1044ddb85c0f0"
LOCAL
)

project(stratum_client)
set(PROJECT_VERSION 0.0.1)

hunter_add_package(Boost COMPONENTS system)
find_package(Boost CONFIG REQUIRED COMPONENTS system)

hunter_add_package(jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)

hunter_add_package(libjson-rpc-cpp)
find_package(libjson-rpc-cpp CONFIG REQUIRED)

message("------------------------------------------------------------------------")
message("-- CMake ${CMAKE_VERSION}")
message("-- Build ${CMAKE_BUILD_TYPE} / ${CMAKE_SYSTEM_NAME}")
message("------------------------------------------------------------- components")
message("")

if(WIN32)
set(CPACK_GENERATOR ZIP)
else()
set(CPACK_GENERATOR TGZ)
endif()
set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME})
set(CPACK_PACKAGE_CHECKSUM SHA256)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY FALSE)
include(CPack)


# Export some variables for CIs
if(PROJECT_VERSION MATCHES "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$")
set(PROJECT_VERSION_IS_PRERELEASE false)
else()
set(PROJECT_VERSION_IS_PRERELEASE true)
endif()
configure_file(cmake/variables.sh.in variables.sh)
configure_file(cmake/variables.ps1.in variables.ps1)
