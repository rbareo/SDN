#include "EDF.hh"

std::string EDF::Utils::read_file(const std::string& file_name) {
  std::ifstream file(file_name);
  
  std::ostringstream stream;
  stream << file.rdbuf();
  return stream.str();
}

int EDF::Utils::mainloop(std::string_view source) {
  EDF::Lexer lexer(source);
  auto tokens = lexer.tokenize();

  EDF::Utils::testing(tokens);
  
  return 0;
}

template <typename T>
void EDF::Utils::testing(const T val) {
  /* NOTE: Remove before build */
  for (auto token : val) {
    std::cout << (size_t) token.state << "\n";
  }
}
