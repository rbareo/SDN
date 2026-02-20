#pragma once

#include "SDN.hh"

namespace SDN::Types {
  enum class States : short;
  struct Token;
  
  class Lexer;
}

enum class SDN::Types::States : short {
  UNKNOWN = -1,
  START,
  
  NEWLINE,
  WHITESPACE,
  
  IDENTIFIER,
  INTEGER,
  STRING_START,
  STRING_BODY,
  STRING_END,
  CHAR_START,
  CHAR_BODY,
  CHAR_END,
  
  LEFT_PARENTHESIS,
  RIGHT_PARENTHESIS,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  
  COLON,
  DECIMAL,
  
  NUMBER_STATES
};

struct SDN::Types::Token {
  SDN::Types::States state;
  std::string_view lexeme;
  
  Token(SDN::Types::States state, std::string_view lexeme) : state(state), lexeme(lexeme) {};
  ~Token() = default;
};

using States = SDN::Types::States;
using Token = SDN::Types::Token;
