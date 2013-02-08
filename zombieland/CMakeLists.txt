set(SRC zombieland.cpp entity.cpp factory.cpp graph.cpp utils.cpp object.cpp obstacle.cpp vector.cpp)

add_library(libzombieland STATIC ${SRC}) # or SHARED

install(TARGETS libzombieland DESTINATION ${PROJECT_SOURCE_DIR}/bin)