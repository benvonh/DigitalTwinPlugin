cmake_minimum_required(VERSION 3.31.3)
project(digital_twin_plugin)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# https://forum.aousd.org/t/issue-building-simple-app-using-usd-c-librairies/1761
add_compile_definitions(NOMINMAX)
# warning C4996: 'std::atomic_compare_exchange_weak_explicit':
# warning STL4029: std::atomic_*() overloads for shared_ptr are deprecated in C++20.
# The shared_ptr specialization of std::atomic provides superior functionality.
add_compile_definitions(_SILENCE_CXX20_OLD_SHARED_PTR_ATOMIC_SUPPORT_DEPRECATION_WARNING)

include(FetchContent)

FetchContent_Declare(ImGUI
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG v1.91.8-docking)

FetchContent_Declare(Termcolor
  GIT_REPOSITORY https://github.com/ikalnytskyi/termcolor
  GIT_TAG v2.1.0)

FetchContent_MakeAvailable(ImGUI Termcolor)

set(ImGUI_SOURCE_DIR ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/_deps/imgui-src)
set(Termcolor_SOURCE_DIR ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/_deps/termcolor-src)

find_package(OpenGL REQUIRED)
find_package(pxr REQUIRED PATHS C:/usd)
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(sensor_msgs REQUIRED)

add_library(plugin
  ${ImGUI_SOURCE_DIR}/imgui.cpp
  ${ImGUI_SOURCE_DIR}/imgui_draw.cpp
  ${ImGUI_SOURCE_DIR}/imgui_tables.cpp
  ${ImGUI_SOURCE_DIR}/imgui_widgets.cpp
  src/sample.cpp)

add_library(digital_twin::plugin ALIAS plugin)

target_compile_features(plugin PUBLIC c_std_99 cxx_std_23)

target_include_directories(plugin PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/DigitalTwin/include>
  ${Termcolor_SOURCE_DIR}/include/termcolor
  ${ImGUI_SOURCE_DIR}
  ${PXR_INCLUDE_DIRS})

target_link_libraries(plugin
  ${PXR_LIBRARIES}
  OpenGL::GL)

ament_target_dependencies(
  plugin
  sensor_msgs
)

install(
  TARGETS plugin
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_libraries(
  plugin
)

ament_export_targets(
  export_${PROJECT_NAME}
)

ament_package()