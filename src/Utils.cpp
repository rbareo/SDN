#include "EDF.hh"

std::string EDF::Utils::read_file(const std::string& file_name) {
  std::ifstream file(file_name);
  
  std::ostringstream stream;
  stream << file.rdbuf();
  return stream.str();
}

int EDF::Utils::mainloop(std::string_view source) {
  /*EDF::Lexer lexer(source);
  std::vector<Token> tokens = lexer.tokenize();
  
  for (Token token : tokens) {
    std::cout << token.lexeme << "\n";
  }
  */
 
  return 0;
}
