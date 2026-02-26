#pragma once

#include "EDF.hh"

class EDF::Parser {
  private:
    const std::vector<Token>& tokens;

  public:
    std::vector<std::unique_ptr<AST::Base>> parse();

    Parser(std::vector<Token>& tokens) : tokens(tokens) {};
    ~Parser() = default;
};
