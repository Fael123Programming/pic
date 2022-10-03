#include <iostream>
#include <string>
#include "include/lexer/Lexer.hpp"
#include "include/lexer/Tag.hpp"

const std::string PATH = "/home/leafar/documents/prg/code/py/scripts/script09.py";

int main() {
  Lexer lex(PATH);
  lex.scan();
  lex.printTokenTable();
  return 0;
}
