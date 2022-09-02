
set(CMAKE_BUILD_TYPE Debug)

add_executable(main main.cpp)

add_subdirectory(base)

target_link_libraries(main
  PRIVATE
    base
  )
    
