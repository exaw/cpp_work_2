cmake_minimum_required(VERSION 3.5)

project ( SR2 VERSION 2 )
set ( CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install )
enable_testing()

add_executable(basket_allocator_sample
        basket_allocator.h
        basket_allocator.cpp
        assoc_list.h
        assoc_list.cpp
        main.cpp
        pretty.h
        )

add_executable(basket_allocator_test
        basket_allocator_test.cpp
        basket_allocator.cpp
        assoc_list.cpp
        )

set_target_properties(basket_allocator_sample basket_allocator_test PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_link_libraries(basket_allocator_test
        gtest pthread
        )

if (MSVC)
    target_compile_options(basket_allocator_sample PRIVATE
            /W4
            )
    target_compile_options(basket_allocator_test PRIVATE
            /W4
            )
else ()
    target_compile_options(basket_allocator_sample PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    target_compile_options(basket_allocator_test PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif ()

add_test(test basket_allocator_test)

install(TARGETS basket_allocator_sample RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dev.taynovai@gmail.com)
include(CPack)



