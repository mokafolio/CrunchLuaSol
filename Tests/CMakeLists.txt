add_executable (CrunchLuaSolTests CrunchLuaSolTests.cpp)
set_target_properties(CrunchLuaSolTests PROPERTIES COMPILE_FLAGS "-fsanitize=address")
set_target_properties(CrunchLuaSolTests PROPERTIES LINK_FLAGS "-fsanitize=address")
target_link_libraries(CrunchLuaSolTests ${CRUNCHLUASOLDEPS})
add_custom_target(check COMMAND CrunchLuaSolTests)