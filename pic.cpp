#include "src/lexer/Lexer.cpp"
#include <iostream>
#include <map>

const std::string PATH = "/home/leafar/documents/prg/code/c-projects/pic/code.py";

int main() {	Lexer lex(PATH);
  lex.scan();
  std::cout << "		        Token Table\n";
  std::cout << "---------------------------------------------------------\n";
  std::map<std::string, Token> tokenTable = lex.getTokenTable();
  for (
  	std::map<std::string, Token>::iterator it = tokenTable.begin();
  	it != tokenTable.end();
  	it++
  ) {
  	std::cout << it->second << std::endl;
  }
  return 0;
}