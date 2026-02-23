#include "EDF.hh"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "ERROR: Incorrect number of arguments given.\n";
    return 1;
  }

  std::string file_name = argv[1];

  const std::string source = EDF::Utils::read_file(file_name);
  
  return !EDF::Utils::mainloop(source);
}
