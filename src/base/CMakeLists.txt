add_library(base "")

target_sources(base
  PRIVATE
    Address.cpp
    Acceptor.cpp
    TcpServer.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Address.h
    ${CMAKE_CURRENT_LIST_DIR}/Acceptor.h
    ${CMAKE_CURRENT_LIST_DIR}/TcpServer.h
    ${CMAKE_CURRENT_LIST_DIR}/TcpConnection.h
    ${CMAKE_CURRENT_LIST_DIR}/MessageQueue.h
    ${CMAKE_CURRENT_LIST_DIR}/Message.h
    ${CMAKE_CURRENT_LIST_DIR}/DataProviderStateMachine.h
    ${CMAKE_CURRENT_LIST_DIR}/ThreadPool.h
  )

target_include_directories(base
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/src/libevent
  )

target_link_libraries(base
  PRIVATE
    event
  )

