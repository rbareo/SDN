#include "SDN.hh"

int main(void) {
  std::string file_name = "sample.sdn";

  const std::string source = SDN::Utils::read_file(file_name);
  
  return !SDN::Utils::mainloop(source);
}
