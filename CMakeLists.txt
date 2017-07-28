cmake_minimum_required(VERSION 2.8.11)

project(raytracer)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Include all source files.
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Include all subdirectories within include/ path.
macro(subdirlist result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    
    foreach (child ${children})
        if (IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${curdir}/${child})
        endif ()
    endforeach ()
    
    set(${result} ${dirlist})
endmacro()

subdirlist(subdirs ${CMAKE_SOURCE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/include)

foreach (subdir ${subdirs})
    subdirlist(test ${subdir})
    list(APPEND subdirs ${test})
endforeach ()

foreach (subdir ${subdirs})
    include_directories(${subdir})
endforeach ()

# If no build type is specified, build in Release mode by default.
if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

link_directories(/home/user/lib/)
add_executable(raytracer ${SRC_FILES})

target_compile_options(raytracer PUBLIC -std=c++11)

find_package(Lua REQUIRED)
if (${LUA_FOUND})
    target_link_libraries(raytracer ${LUA_LIBRARIES})
endif ()

find_package(FreeImage REQUIRED)
if (${FREEIMAGE_FOUND})
    message(${FREEIMAGE_LIBRARIES})
    target_link_libraries(raytracer ${FreeImage_LIBRARIES})
endif ()

#target_compile_options(raytracer PRIVATE -L${FreeImage_LIBRARIES})
#target_compile_options(raytracer PRIVATE -lfreeimage)
