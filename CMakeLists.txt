cmake_minimum_required(VERSION  2.8.12)

project("myalloc")

add_library(myalloc STATIC
  src/alloc.cpp
  src/free.cpp
  src/main.cpp
  src/malloc.cpp
  )

add_executable(test
  src/main.cpp)

target_include_directories(test PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  )

target_link_libraries(test PRIVATE myalloc)

target_include_directories(myalloc PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  )
