add_library(eventloop "")

target_sources(eventloop
  PRIVATE
    TcpServer.cpp
    TcpConnection.cpp
    Address.cpp
    Acceptor.cpp
    Buffer.cpp
    EventLoop.cpp
    MessageQueue.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/TcpServer.h
    ${CMAKE_CURRENT_LIST_DIR}/TcpConnection.h
    ${CMAKE_CURRENT_LIST_DIR}/Address.h
    ${CMAKE_CURRENT_LIST_DIR}/Acceptor.h
    ${CMAKE_CURRENT_LIST_DIR}/Buffer.h
    ${CMAKE_CURRENT_LIST_DIR}/EventLoop.h
    ${CMAKE_CURRENT_LIST_DIR}/MessageQueue.h
  )

target_include_directories(eventloop
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
