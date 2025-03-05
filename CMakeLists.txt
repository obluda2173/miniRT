cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(miniRT)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Building options
option(BUILD_TEST "Build tests" ON)
option(BUILD_MINIRT "Build miniRT (for_compile_commands)" OFF)

# testing ##################################################
# Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -fsanitize=address")

add_subdirectory(libft)

set(MLX_DIR "${CMAKE_SOURCE_DIR}/minilibx-linux")
link_directories(${MLX_DIR})

# Add libft subdirectory
# if(BUILD_TEST)
#   file(GLOB FDF_SOURCES "src/*.c")
#   file(GLOB TEST_FILES "tests/*.cpp")
#   set(TEST_NAME "run_tests")

#   add_executable(${TEST_NAME} ${FDF_SOURCES} ${TEST_FILES})
#   target_link_libraries(${TEST_NAME} gtest gmock gtest_main pthread ft mlx_Linux Xext X11)

#   target_include_directories(${TEST_NAME} PRIVATE ${MLX_DIR})
#   target_include_directories(${TEST_NAME} PRIVATE includes)
#   target_include_directories(${TEST_NAME} PRIVATE libft)
#   target_include_directories(${TEST_NAME} PRIVATE ${gtest_SOURCE_DIR}/googletest/include)

#   include(GoogleTest)
#   gtest_discover_tests(${TEST_NAME})
# endif()

# Building philo ##################################################
if(BUILD_MINIRT)
  file(GLOB MINIRT_SOURCES "src/*.c")
  add_executable(minirt ${MINIRT_SOURCES})

  target_link_libraries(minirt ft mlx_linux Xext X11)

  target_include_directories(minirt PRIVATE inc)
  target_include_directories(minirt PRIVATE libft)
  target_include_directories(minirt PRIVATE get_next_line)
  target_include_directories(minirt PRIVATE ${MLX_DIR})
endif()
