#pragma once

#include "SDN.hh"

class SDN::Lexer {
  private:
    std::string_view source;
    States last_state = States::START;
    States state;
    char current;
    std::string_view lexeme;
    size_t line_number = 1;
    size_t column = 1;
    size_t start_position = 0;
    
    bool handle_whitespace();
    
  public:
    std::vector<Token> tokenize();
    
    Lexer(std::string_view source) : source(source) {};
    ~Lexer() = default;
};
