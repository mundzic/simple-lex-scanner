project (scanner)

add_library(${PROJECT_NAME} 
		Token.cpp
		Scanner.cpp
)
add_library(cmp::scan ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    cmp::cfg
)