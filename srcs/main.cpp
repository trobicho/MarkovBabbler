#include <cstdlib>
#include <fstream>
#include "tokenTable.hpp"
#include <random>
#include <chrono>
#include <iostream>


int main(int ac, char** av) {
  std::srand(std::time({}));

  TokenTable      table;
  std::ifstream   ifstream;
  std::string     filename = "";

  if (ac > 1) {
		filename = av[1];
  }
  else
    return (0);

  try {
    ifstream.open(filename);
    if (!ifstream.good()) {
      return (0);
    }
  }
  catch (std::ifstream::failure e) {
    std::cerr << "unable to open file: " << filename << " " << e.what() << std::endl;
    return (1);
  }
  Lex lex(&ifstream);
  table.initTokenTable(lex);
  int state = rand() % table.size(); 

  for (int i = 0; i < 100; i++) {
    std::cout << table.babble(state) << " ";
  }

  return (0);
}
