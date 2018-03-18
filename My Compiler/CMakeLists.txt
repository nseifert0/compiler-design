set (CMAKE_CXX_STANDARD 11)
project (my-compiler)
add_executable(my-compiler main.cpp parser.cpp lexer.cpp token.cpp symbols.cpp)