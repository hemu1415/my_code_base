add_executable(main main.cpp TraceManager.cpp)

add_subdirectory(eventloop)

target_link_libraries(main
  PRIVATE
    eventloop
  )
    
