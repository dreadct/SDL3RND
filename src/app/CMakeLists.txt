cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME app)

# Source code
set(TARGET_SRC_DIR "${PROJECT_SRC_DIR}/${TARGET_NAME}")
set(TARGET_SOURCES
    $<$<PLATFORM_ID:Darwin>:${TARGET_SRC_DIR}/unix/main.cpp>
    $<$<PLATFORM_ID:Linux>:${TARGET_SRC_DIR}/unix/main.cpp>
    $<$<PLATFORM_ID:Windows>:${TARGET_SRC_DIR}/windows/main.cpp>
)

# Target
if(WIN32)
add_executable(${TARGET_NAME} WIN32 ${TARGET_SOURCES})
elseif(UNIX)
add_executable(${TARGET_NAME} ${TARGET_SOURCES})
endif()
