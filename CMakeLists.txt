cmake_minimum_required(VERSION 3.13)
project(pico_read_writer_mutex LANGUAGES C VERSION 1.0.0)

set(CMAKE_C_STANDARD 11)

set(PROJECT_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/read_writer_mutex.h)

add_library(pico_read_writer_mutex src/read_writer_mutex.c)

set_target_properties(pico_read_writer_mutex PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(pico_read_writer_mutex PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(pico_read_writer_mutex PROPERTIES PUBLIC_HEADER ${PROJECT_HEADERS})

target_include_directories(
  pico_read_writer_mutex PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(pico_read_writer_mutex PUBLIC pico_stdlib)


install(
  TARGETS pico_read_writer_mutex
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)