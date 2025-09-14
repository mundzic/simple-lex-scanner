project(lexer)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(cfg)
add_subdirectory(scan)
add_subdirectory(rt)

target_link_libraries(${PROJECT_NAME}
    cmp::cfg
    cmp::scan
	cmp::rt
)
