#include "SDN.hh"

std::string SDN::Utils::read_file(const std::string& file_name) {
  std::ifstream file(file_name);
  
  std::ostringstream stream;
  stream << file.rdbuf();
  return stream.str();
}

int SDN::Utils::mainloop(std::string_view source) {
  SDN::Lexer lexer(source);
  std::vector<Token> tokens = lexer.tokenize();
  
  for (Token token : tokens) {
    std::cout << token.lexeme << "\n";
  }
  
  return 0;
}
