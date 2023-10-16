project(kd_tree CXX)

set(FILES
)

foreach(file ${FILES})
    add_example(${file} ${GTEST_BOTH_LIBRARIES})
endforeach()
