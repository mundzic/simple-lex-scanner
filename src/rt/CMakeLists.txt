project (runtime)

add_library(${PROJECT_NAME} 
		RunTime.cpp
)
add_library(cmp::rt ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    cmp::cfg
	cmp::scan
)