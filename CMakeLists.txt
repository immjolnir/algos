cmake_minimum_required(VERSION 3.20)
project(algos CXX)

function(add_example src)
    # https://cmake.org/cmake/help/latest/command/get_filename_component.html
    get_filename_component(example ${src} NAME_WLE)
    get_filename_component(output_dir ${src} DIRECTORY)
    # string(REGEX REPLACE "([a-zA-Z0-9_ ]+)(\.cpp)" "\\1" example "${src}")
    message(STATUS "Creating example ${example}")
    add_executable(${example} ${src})
    # set_target_warnings(${example})
    target_include_directories(${example} BEFORE
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/modules>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )
    set(additional_libs ${ARGN})
    target_link_libraries(${example}
        ${OpenCV_LIBS}
        ${additional_libs}
    )

    # https://blog.csdn.net/MacKendy/article/details/122549819
    set_target_properties(${example} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${output_dir}")
endfunction()

set(modules
    kd_tree
)

foreach(m ${modules})
    add_subdirectory(${m})
endforeach()
