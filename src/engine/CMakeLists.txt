cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME engine)

# Source code
set(TARGET_INCLUDE_DIR "${PROJECT_INCLUDE_DIR}/${TARGET_NAME}")
set(TARGET_PUBLIC_HEADERS
    ${TARGET_INCLUDE_DIR}/app/EApplication.h
)
set(TARGET_SRC_DIR "${PROJECT_SRC_DIR}/${TARGET_NAME}")
set(TARGET_SOURCES
    # app
    ${TARGET_SRC_DIR}/app/EApplication.cpp
    ${TARGET_SRC_DIR}/app/EApplicationImpl.h
    ${TARGET_SRC_DIR}/app/EApplicationImpl.cpp
    # app window
    ${TARGET_SRC_DIR}/app/window/EAppWindow.h
    ${TARGET_SRC_DIR}/app/window/EAppWindow.cpp
)

# Dependencies
find_package(SDL3 REQUIRED CONFIG)

# Target
add_library(${TARGET_NAME} STATIC
    ${TARGET_PUBLIC_HEADERS}
    ${TARGET_SOURCES}
)

# Includes
target_include_directories(${TARGET_NAME}
    PRIVATE ${SDL3_INCLUDE_DIRS}
    PUBLIC ${PROJECT_INCLUDE_DIR}
)

# Linking
target_link_libraries(${TARGET_NAME}
    PRIVATE SDL3::SDL3
)
