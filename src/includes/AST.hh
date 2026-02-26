#pragma once

#include "EDF.hh"

namespace EDF::Types::AST {
  enum class Kinds : short;
  enum class Types : short;
  enum class Operators : short;

  class Base; // Abstract

  class Definition : public Base; // Abstract
  class Mixin : public Definition;
  class Const : public Definition;
  class Type : public Definition;
  class Alias : public Definition;

  class Expression : public Base; // Abstract
  class Unary_Expression : public Expression;
  class Binary_Expression : public Expression;

  class Statement : public Base; // Abstract
  class If : public Statement;

  class Value : public Base; // Abstract
  class Function_Call : public Value;
  class Reference : public Value;

  class Literal : public Value; // Abstract
  class Scalar : public Literal;
  class Array : public Literal;
  class Record : public Literal;
}

namespace AST = EDF::Types::AST;

enum class AST::Kinds : short {
  MIXIN,
  CONST,
  TYPE,
  ALIAS,
  UNARY_EXPRESSION,
  BINARY_EXPRESSION,
  IF,
  FUNCTION_CALL,
  REFERENCE,
  SCALAR,
  ARRAY,
  RECORD
};

enum class AST::Operators : short {
  PLUS,
  MINUS,
  MULT,
  DIV,
  LESS_THAN,
  GREATER_THAN,
  LESS_EQUALS,
  GREATER_EQUALS,
  EQUALS,
  NOT_EQUALS,
  NOT,
  AND,
  OR
};
