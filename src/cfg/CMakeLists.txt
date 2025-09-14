project (config)

add_library(${PROJECT_NAME} 
		Rule.cpp
		KernelBuilder.cpp
		Cfg.cpp
)

add_library(cmp::cfg ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    cmp::scan
)