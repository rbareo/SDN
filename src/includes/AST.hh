#pragma once
/*
#include "EDF.hh"

namespace EDF::Types::AST {
  enum class Kinds : short;
  enum class Types : short;
  enum class Operators : short;

  class Base;
  class Identifier;
  class Literal;
  class Binary_operator;
}

namespace AST = EDF::Types::AST;

enum class AST::Kinds : short {
  IDENTIFIER,
  LITERAL,
  BINARY_OPERATOR
};

enum class AST::Types : short {
  INTEGER,
  FLOAT,
  STRING,
  RECORD
};

enum class AST::Operators : short {
  COLON
};

class AST::Base {
  public:
    const AST::Kinds kind;

    Base(AST::Kinds kind) : kind(kind) {};
    ~Base() = default;
};

class AST::Identifier : public AST::Base {
  public:
    std::string_view name;
    AST::Types type;

    Identifier(std::string_view name, AST::Types type) : Base(AST::Kinds::IDENTIFIER), name(name), type(type) {};
    ~Identifier() = default;
};

class AST::Literal : public AST::Base {
  public:
    std::string_view value;
    AST::Types type;

    Literal(std::string_view value, AST::Types type) : Base(AST::Kinds::LITERAL), value(value), type(type) {};
    ~Literal() = default;
};

class AST::Binary_operator : public AST::Base {
  public:
    const std::unique_ptr<AST::Base> left;
    const std::unique_ptr<AST::Base> right;
    const AST::Operators op;

    Binary_operator(std::unique_ptr<AST::Base> left, std::unique_ptr<AST::Base> right, AST::Operators op)
      : Base(AST::Kinds::BINARY_OPERATOR), left(std::move(left)), right(std::move(right)), op(op) {};
    ~Binary_operator() = default;
};
*/