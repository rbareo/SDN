#pragma once

#include "EDF.hh"

namespace EDF::Types {
  enum class Errors : short;
  enum class States : short;

  struct Error;
  struct Lexer_State_Block;
  struct Token;
}

enum class EDF::Types::States : short {
  UNKNOWN = -1,
  START,
  
  EQUALS_PARTIAL,
  AND_PARTIAL,

  IDENTIFIER,
  INTEGER_LITERAL,
  FLOAT_LITERAL,
  TEMPLATE_LITERAL,
  STRING_LITERAL,
  CHAR_LITERAL,

  TEMPLATE_START,
  TEMPLATE_BODY,
  TEMPLATE_END,
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
  AT,
  POUND,
  DOLLAR,
  QUESTION,
  
  COLON,
  TYPE_OR,

  PLUS,
  MINUS,
  MULT,
  DIV,
  MOD,

  AND,
  OR,
  NOT,

  GREATER_THAN,
  LESS_THAN,
  GREATER_EQUALS,
  LESS_EQUALS,
  EQUALS,
  NOT_EQUALS,
  
  NUMBER_STATES
};

struct EDF::Types::Token {
  EDF::Types::States state;
  std::string_view lexeme;
  size_t line_number;
  
  Token(EDF::Types::States state, std::string_view lexeme, size_t line_number)
    : state(state), lexeme(lexeme), line_number(line_number) {};
  ~Token() = default;
};

using States = EDF::Types::States;
using Token = EDF::Types::Token;
