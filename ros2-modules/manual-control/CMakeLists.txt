cmake_minimum_required(VERSION 3.8)
project(manual-control)

option(ENABLE_TESTS "Enable tests" OFF)
option(ENABLE_COMPILER_OPTIONS "Enable advanced complier options/warnings" OFF)
option(ENABLE_LATEST_CPP_STANDARD "Enable latest c++ standard" OFF)

message(STATUS "Enable tests - " ${ENABLE_TESTS})
message(STATUS "Enable advanced complier options/warnings - " ${ENABLE_COMPILER_OPTIONS})
message(STATUS "Enable latest C++ standard - " ${ENABLE_LATEST_CPP_STANDARD})

if (ENABLE_COMPILER_OPTIONS)
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough)
endif()

if (ENABLE_LATEST_CPP_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(common REQUIRED)
find_package(interfaces REQUIRED)

include_directories(include)

add_executable(manual_control src/main.cpp
                              src/ros_module.cpp
                              src/network/socket.cpp
                              src/network/tcp_server.cpp
)

ament_target_dependencies(manual_control common)

ament_export_include_directories(include)

install(
  DIRECTORY include/manual-control
  DESTINATION include
)

install(TARGETS
        manual_control
        DESTINATION
        lib/${PROJECT_NAME}
)

if(ENABLE_TESTS)
  enable_testing()
  #find_package(ament_lint_auto REQUIRED)
  #set(ament_cmake_copyright_FOUND TRUE)
  #set(ament_cmake_cpplint_FOUND TRUE)
  #ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gmock REQUIRED)
  ament_add_gmock(tcp_client_tests tests/tcp_client_tests.cpp
                                   src/network/tcp_client.cpp)

  target_include_directories(tcp_client_tests PUBLIC
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                             $<INSTALL_INTERFACE:include>
  )

  ament_add_gmock(tcp_server_tests tests/tcp_server_tests.cpp
                                   src/network/tcp_server.cpp)

  target_include_directories(tcp_server_tests PUBLIC
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                             $<INSTALL_INTERFACE:include>
  )

endif()

ament_package()

add_executable(${PROJECT_NAME}-app
               src/manual_control_app.cpp
               src/network/socket.cpp
               src/network/tcp_client.cpp
)
