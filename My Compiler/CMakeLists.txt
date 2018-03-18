set (CMAKE_CXX_STANDARD 11)
project (my-compiler)
add_executable(Lexer main.cpp lexer.cpp token.cpp symbols.cpp)