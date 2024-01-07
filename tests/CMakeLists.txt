link_libraries(${PROJECT_NAME}::SimpleLib)

add_executable(SimpleLibTest test_simplelib.cpp)
add_test(NAME SimpleLibTest COMMAND SimpleLibTest)
