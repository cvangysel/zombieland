set(SRC main.cpp handler.cpp factory.cpp)

include_directories(../zombieland)
set(LIBS ${LIBS} libzombieland)

add_executable(zombieland ${SRC})

find_package(SFML 2 COMPONENTS system window graphics)

include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(zombieland ${SFML_LIBRARIES})
target_link_libraries(zombieland ${LIBS})

install(TARGETS zombieland RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)