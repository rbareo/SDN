#include "EDF.hh"

std::unique_ptr<AST::Base> EDF::Parser::parse() {
  simplify_tokens();
  std::unique_ptr<AST::Base> root;
}

void EDF::Parser::simplify_tokens() {
  std::vector<Token> simplifed_tokens = {};
}
