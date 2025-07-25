add_subdirectory(ops)
add_subdirectory(fsops)
add_subdirectory(utils)

add_executable(${PROJECT_NAME} parse.c)

target_link_libraries(${PROJECT_NAME} PRIVATE jansson)

target_link_libraries(${PROJECT_NAME} PRIVATE ops fsops utils)
