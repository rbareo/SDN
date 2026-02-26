#pragma once

#include "EDF.hh"

namespace EDF::Types::AST {
  enum class Kinds : short;
  enum class Types : short;
  enum class Operators : short;

  class Base; // Abstract

  class Definition; // Abstract
  class Mixin;
  class Const;
  class Type;
  class Alias;

  class Expression; // Abstract
  class Unary_Expression;
  class Binary_Expression;

  class Statement; // Abstract
  class If;

  class Value; // Abstract
  class Function_Call;
  class Reference;

  class Literal; // Abstract
  class Scalar;
  class Array;
  class Record;
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

// Abstract
class AST::Base {
};

 // Abstract
class AST::Definition : public AST::Base {
};

class AST::Mixin : public AST::Definition {
};

class vConst : public AST::Definition {
};
class vType : public AST::Definition {
};

class AST::Alias : public AST::Definition {

};

// Abstract
class AST::Expression : public AST::Base {
};

class AST::Unary_Expression : public AST::Expression {
};

class AST::Binary_Expression : public AST::Expression {
};

// Abstract
class AST::Statement : public AST::Base {
};

class AST::If : public AST::Statement {
};

// Abstract
class AST::Value : public AST::Base {
};

class AST::Function_Call : public AST::Value {
};
class AST::Reference : public AST::Value {
};

// Abstract
class AST::Literal : public AST::Value {
};

class AST::Scalar : public AST::Literal {
};

class AST::Array : public AST::Literal {
};

class AST::Record : public AST::Literal {
};
