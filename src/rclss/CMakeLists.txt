cmake_minimum_required(VERSION 3.2)
set(NAME_SUBPROJECT rclss)

set(COMMON_PATH ${CMAKE_SOURCE_DIR}/src/common)

add_executable(${NAME_SUBPROJECT} main.cpp
    ${COMMON_PATH}/property_description.h
    ${COMMON_PATH}/utils.h)

target_include_directories(${NAME_SUBPROJECT} PRIVATE ${COMMON_PATH})

set_target_properties(${NAME_SUBPROJECT} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# максимально строгие настройки компилятора
if (MSVC)
    target_compile_options(${NAME_SUBPROJECT} PRIVATE
        /W4
    )
else ()
    target_compile_options(${NAME_SUBPROJECT} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

target_link_libraries(${NAME_SUBPROJECT}
    dlib::dlib
    blas
    lapack
    Threads::Threads
    stdc++fs
)


# бинарник кладем в каталог bin
install(TARGETS ${NAME_SUBPROJECT} RUNTIME DESTINATION bin)
