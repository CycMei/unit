

AUX_SOURCE_DIRECTORY("." exp_src_list)


INCLUDE_DIRECTORIES(${unit_src})

ADD_EXECUTABLE(exp ${exp_src_list})


TARGET_LINK_LIBRARIES(exp unit)
