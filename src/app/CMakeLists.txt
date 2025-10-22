cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME app)

# Source code
set(TARGET_SRC_DIR "${PROJECT_SRC_DIR}/${TARGET_NAME}")
set(TARGET_SOURCES
    ${TARGET_SRC_DIR}/main.cpp
)

# Dependencies
find_package(SDL3 REQUIRED CONFIG)

# Target
if(WIN32)
add_executable(${TARGET_NAME} WIN32 ${TARGET_SOURCES})
elseif(UNIX)
add_executable(${TARGET_NAME} ${TARGET_SOURCES})
endif()

# Includes
target_include_directories(${TARGET_NAME}
    PRIVATE ${SDL3_INCLUDE_DIRS}
)

# Linking
target_link_libraries(${TARGET_NAME}
    PRIVATE SDL3::SDL3
)
