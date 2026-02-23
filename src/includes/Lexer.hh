#pragma once

#include "EDF.hh"

class EDF::Lexer {
  private:
    std::string_view source;
    States last = States::START;
    States state;
    char current;
    std::vector<Token> tokens = {};
    std::string_view lexeme;
    bool ignored_state = true;
    size_t line_number = 1;
    size_t column = 1;
    size_t position = 0;
    size_t start_position = 0;

    void handle_special_states();
    void handle_interpolation();
    void handle_single_line_comments();
    void handle_multiline_comments();
    
  public:
    std::vector<Token> tokenize();
    
    Lexer(std::string_view source) : source(source) {};
    ~Lexer() = default;
};
