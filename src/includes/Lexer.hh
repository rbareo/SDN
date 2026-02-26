#pragma once

#include "EDF.hh"

class EDF::Lexer {
  private:
    struct Finalized_Return;

    const std::string_view source;
    size_t line_number = 1;

    size_t handle_whitespace(size_t start_position);
    size_t handle_single_line_comments(size_t start_position);
    size_t handle_multiline_comments(size_t start_position);
    size_t handle_unwanted(size_t start_position);
    Finalized_Return finalize_state(States state, size_t start_position, size_t position);

  public:
    std::vector<Token> tokenize();
    
    Lexer(std::string_view source) : source(source) {};
    ~Lexer() = default;
};
struct EDF::Lexer::Finalized_Return {
  const States state;
  const std::string_view lexeme;

  Finalized_Return(States state, std::string_view lexeme) : state(state), lexeme(lexeme) {};
  ~Finalized_Return() = default;
};
