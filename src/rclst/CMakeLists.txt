cmake_minimum_required(VERSION 3.2)
set(NAME_SUBPROJECT rclst)

add_executable(${NAME_SUBPROJECT} main.cpp)

set_target_properties(${NAME_SUBPROJECT} PROPERTIES
    CXX_STANDARD 14
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
)

# бинарник кладем в каталог bin
install(TARGETS ${NAME_SUBPROJECT} RUNTIME DESTINATION bin)
