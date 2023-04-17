# Disable in-source builds to prevent source tree corruption
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
 message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
      You should create a separate directory for build files.
")
endif()

# Force install prefix path (Don't use --prefix and -DCMAKE_INSTALL_PREFIX)
set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/output"
    CACHE PATH "Install Path" FORCE)
	
cmake_minimum_required(VERSION 3.17)

project(StdThreadProgram)

if(DEFINED QT_CREATOR_SKIP_PACKAGE_MANAGER_SETUP AND NOT QT_CREATOR_SKIP_PACKAGE_MANAGER_SETUP)
    include(${CMAKE_BINARY_DIR}/conan-dependencies/conan_paths.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenMP REQUIRED)

set(CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/include)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Place all exe and dlls in Build Directory, without subdirectories
# First case: Generic, no-config (e.g. with mingw)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
# Second case: for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_BINARY_DIR})
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

# Add target JADE
add_executable(${PROJECT_NAME} WIN32 "src/main.cpp" "resources.qrc")

# In MSVC, Startup project must be JADE
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Configure warnings and parallel compilation
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -W3 -MP)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _HAS_STD_BYTE=0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

add_subdirectory(src)

# Configure warnings and parallel compilation
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -W3 -MP)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _HAS_STD_BYTE=0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# Link to dependencies. The Render module is included on Interface Componentes and linked together.
target_link_libraries(${PROJECT_NAME} PUBLIC
                      Qt5::Widgets OpenMP::OpenMP_CXX)
					  
					  # Point out the include path
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_INCLUDE_PATH})

# Avoid extensions such as "gnu++11" instead of "c++11", which could include non-standard features
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

# Compile features: requires c++17
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)


