add_executable(${PROJECT_NAME} main.c parse.h parse.c ops.h operations.c fsops.c fsops.h)

target_link_libraries(${PROJECT_NAME} PRIVATE jansson)
