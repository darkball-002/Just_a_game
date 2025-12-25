# cmake mminimum version
cmake_minimum_required(VERSION 3.20)

# set project
project(${LN} LANGUAGES C)

# C std library version
set(CMAKE_C_STANDARD 11)

# source
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "${LSOURCE}/*.c")
add_executable(${LN} ${SRC})
target_include_directories(${LN} PRIVATE "${LHEADER}")

# glad
add_library(glad "${LGLAD}/src/glad.c")
target_include_directories(glad PUBLIC "${LGLAD}/include")

# cglm
add_library(cglm INTERFACE)
target_include_directories(cglm INTERFACE "${LCGLM}/include")

# glfw
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION "${LGLFW}/build/src/libglfw3.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LGLFW}/include"
)

# link
target_link_libraries(${LN} PRIVATE glad cglm glfw opengl32 gdi32)
target_compile_options(${LN} PRIVATE -Wno-incompatible-pointer-types-discards-qualifiers)

target_link_options(${LN} PRIVATE "-Wl,-subsystem,windows" "-s")

# export
set_target_properties(${LN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${LEXPORT}")
