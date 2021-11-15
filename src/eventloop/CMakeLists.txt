add_library(eventloop "")

target_sources(eventloop
  PRIVATE
    eventloop.cpp
  PUBLIC
     ${CMAKE_CURRENT_LIST_DIR}/eventloop.hpp
  )

target_include_directories(eventloop
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
