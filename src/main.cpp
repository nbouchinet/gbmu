#include "Gameboy.hpp"
#include <iostream>

int main(int ac, char *av[]) {
  std::string rom = av[1];

  (void)ac;
  //  std::cout << rom << std::endl;
  Gameboy g(rom);

  return g.run();
}
