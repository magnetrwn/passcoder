# Setup project
cmake_minimum_required(VERSION 3.12.0)
project(passcoder)

find_package(PkgConfig REQUIRED)
find_package(OpenSSL 1.1.0 REQUIRED)
find_package(Boost 1.70 REQUIRED COMPONENTS json)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

file(GLOB PROJECT_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.tpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Defines
add_compile_definitions(DEBUG)

# Setup compiler
if(MSVC)
    add_compile_options(/w4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${GTKMM_INCLUDE_DIRS}
    PRIVATE ${Boost_INCLUDE_DIRS}
    PUBLIC include
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${GTKMM_LIBRARIES}
    PRIVATE OpenSSL::Crypto
    PRIVATE Boost::json
)
target_compile_features(
    ${PROJECT_NAME}
    PRIVATE cxx_std_14
    PRIVATE cxx_lambda_init_captures
)
