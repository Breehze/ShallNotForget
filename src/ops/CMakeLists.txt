add_library(ops STATIC ops.c)
target_link_libraries(ops PRIVATE fsops)
target_link_libraries(ops PRIVATE utils)
