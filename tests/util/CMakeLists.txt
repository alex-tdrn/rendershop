add_executable(tests_util "src/main.cpp" "src/colors.cpp")

target_link_libraries(tests_util PRIVATE Catch2::Catch2 clayknot::util)
target_compile_definitions(tests_util PRIVATE CATCH_CONFIG_CONSOLE_WIDTH=200)
