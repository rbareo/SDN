#pragma once

#include "SDN.hh"

namespace SDN::Utils {
  std::string read_file(const std::string& file_name);
  int mainloop(std::string_view source);
}
