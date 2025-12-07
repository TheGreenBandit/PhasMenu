cmake_minimum_required(VERSION 3.5)

project(PhasMenu CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Fetch modules
message("\nFetching modules")
include(cmake/json.cmake)
include(cmake/pugixml.cmake)
include(cmake/cpr.cmake)
include(cmake/imgui.cmake)
include(cmake/minhook.cmake)
include(cmake/g3log.cmake)

# blade
message(STATUS "PhasMenu")
file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.asm"
)

add_library(PhasMenu MODULE "${SRC_MAIN}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET PhasMenu PROPERTY CXX_STANDARD 23)

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN} )

target_include_directories(PhasMenu PRIVATE 
    "${SRC_DIR}"
    "${json_SOURCE_DIR}/single_include"
    "${minhook_SOURCE_DIR}/src/hde"
    "${imgui_SOURCE_DIR}"
)

target_precompile_headers(PhasMenu PRIVATE "${SRC_DIR}/common.hpp")
target_link_libraries(PhasMenu PRIVATE pugixml d3d11 imgui minhook g3log cpr d3dcompiler nlohmann_json::nlohmann_json dwmapi winmm psapi)

add_compile_definitions(PhasMenu 
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
    "_WIN32_WINNT=0x0600"
)