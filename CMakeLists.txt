project(software-identify)

file(
    "src/*.h"
    "src/*.cpp"
)

target_link_libraries(${PROJECT_NAME} archive)

add_executable(${PROJECT_NAME} src/main.cpp)
