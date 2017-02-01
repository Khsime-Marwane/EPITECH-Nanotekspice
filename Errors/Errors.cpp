//
// Errors.cpp for Errors in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/Errors/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Tue Jan 31 20:22:31 2017 Marwane Khsime
// Last update Tue Jan 31 20:27:25 2017 Marwane Khsime
//

#include "Errors.hh"

bool OpenFile(const std::string &path) {
  std::ifstream file(path);

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::cout << line << std::endl;
    }
    return true;
  }
  return false;
}

int main(int argc, char **argv) {
  OpenFile(argv[1]);
  (void)argc;
  return 0;
}
