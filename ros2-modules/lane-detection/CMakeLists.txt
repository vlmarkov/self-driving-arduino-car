cmake_minimum_required(VERSION 3.8)
project(lane-detection)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -std=c++23)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(common REQUIRED)
find_package(interfaces REQUIRED)
find_package(OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp
                               src/ros_module.cpp
                               src/lane.cpp
                               src/lane_detection_module.cpp
)
ament_target_dependencies(${PROJECT_NAME} common)

ament_export_include_directories(include)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

install(
  DIRECTORY include/${PROJECT_NAME}
  DESTINATION include
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  INCLUDES DESTINATION include
)

install(TARGETS
        ${PROJECT_NAME}
        DESTINATION
        lib/${PROJECT_NAME}
)

enable_testing()

if(BUILD_TESTING)
  #find_package(ament_lint_auto REQUIRED)
  #set(ament_cmake_copyright_FOUND TRUE)
  #set(ament_cmake_cpplint_FOUND TRUE)
  #ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(${PROJECT_NAME}_lane_tests tests/lane_tests.cpp
                                             src/lane.cpp)

  target_include_directories(${PROJECT_NAME}_lane_tests PUBLIC
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                             $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${PROJECT_NAME}_lane_tests ${OpenCV_LIBS})

  ament_add_gtest(${PROJECT_NAME}_module_tests tests/lane_detection_module_tests.cpp
                                                     src/lane_detection_module.cpp
                                                     src/lane.cpp)
  target_include_directories(${PROJECT_NAME}_module_tests PUBLIC
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                             $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${PROJECT_NAME}_module_tests ${OpenCV_LIBS})

endif()

ament_package()

add_executable(${PROJECT_NAME}-app
               src/lane_detection_app.cpp
               src/lane.cpp
               src/lane_detection_module.cpp
)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}-app ${OpenCV_LIBS})
