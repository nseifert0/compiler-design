set (CMAKE_CXX_STANDARD 11)

add_library(lang
  symbols.cpp
  token.cpp
  lexer.cpp
  parser.cpp
  codegen.cpp)
target_link_libraries(lang ${LLVM_LIBS})

add_executable(my-compiler main.cpp)
target_link_libraries(my-compiler lang)
