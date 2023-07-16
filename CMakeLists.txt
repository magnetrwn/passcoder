cmake_minimum_required(VERSION 3.12.0)
project(passcoder)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

file(GLOB CODE
    "include/*.hpp"
    "include/*.ipp"
    "src/*.cpp"
)
include_directories(
    include
    src
    ${GTKMM_INCLUDE_DIRS}
)
link_libraries(
    ${GTKMM_LIBRARIES}
)
if(MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()
add_compile_definitions(DEBUG)
add_compile_definitions(UI_FILENAME="ui/mainw.glade")
add_executable(${PROJECT_NAME} ${CODE})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_lambda_init_captures)
