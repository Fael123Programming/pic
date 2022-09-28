#include <bits/types/FILE.h>
#include <cctype>
#include <iostream>
#include <fstream>
#include "../../include/lexer/Lexer.h"

bool isPresent(std::string str, char ch) {
    return str.find(ch) < str.size();
}

Lexer::Lexer(std::string sourcePath) : sourcePath(sourcePath) {}

void Lexer::addTokenIntoTable(Token tk) {
    if (existsInTokenTable(tk.getLexeme())) {
        return;
    }
    tokenTable.insert(std::pair<std::string, Token>(tk.getLexeme(), tk));
}

bool Lexer::existsInTokenTable(std::string lexeme) {
    return tokenTable.count(lexeme) > 0;
}

bool Lexer::next() {
    int fileContentSize = fileContent.size();
    if (fileContentSize == 0 || i == fileContentSize - 1) {
        return false;
    }
    current = fileContent[++i];
    return true;
}

bool Lexer::previous() {
    unsigned int fileContentSize = fileContent.size();
    if (fileContentSize == 0 || i == -1) {
        return false;
    }
    current = fileContent[--i];
    return true;
}

std::string Lexer::getFileContent() {
    return fileContent;
}

bool Lexer::match(std::string str) {
    int strSize = str.size();
    int j = 0;
    while (this->next()) {
        if (j == strSize) {
            return true;
        }
        if (this->current == str[j]) {
            j++;
        } else {
            j = 0;
        }
    }
    return false;
}

bool Lexer::matchLine(std::string str) {
    int strSize = str.size();
    int j = 0;
    while (this->next()) {
        if (j == strSize) {
            return true;
        }
        if (this->current == '\n') {
            break;
        }
        if (this->current == str[j]) {
            j++;
        } else {
            j = 0;
        }
    }
    return false;
}

char Lexer::getCurrent() {
    return current;
}

void Lexer::scan() {
    this->extractFileContent(); // Lazy load of the file content.
    const int fileContentSize = fileContent.size();
    int wordSize;
    std::string word = "";
    bool error = false;
    Tag tag;
    while (this->i < fileContentSize - 1) {
        this->next();
        if (this->current == ' ' || this->current == '\n') {
            continue;
        }
        if (this->current == '#') {
            this->match("\n"); // Ignore everything until a `\n` is found.
            this->previous();
        } else if (this->current == '\'') {
            this->next();
            if (this->current == '\'') {
                this->next();
                if (this->current == '\'') { // Comment block.
                    if (!this->match("'''")) {
                        std::cout << "# Lexical error caught on comment #\n";
                        std::cout << "# Comment block was not closed #\n";
                        error = true;
                        return;
                    }
                    while (this->current != '\n') {
                        if (this->current != ' ') {
                            std::cout << "# Lexical error caught on '" << this->current << "' #\n";
                            std::cout << "# Comment block cannot have anything after its closure #\n";
                            error = true;
                            return;
                        }
                        this->next();
                    }
                } else {
                    this->addTokenIntoTable(Token(STRING, ""));
                }
            } else {
                word = this->current;
                while (this->next()) {
                    if (this->current == '\'') {
                        break;
                    } else if (this->current == '\n') {
                        std::cout << "# Lexical error caught on: '" << word << "'\n";
                        std::cout << "# Invalid lexeme: unclosed string\n";
                        error = true;
                        return;
                    } 
                    word += this->current;
                }
                this->addTokenIntoTable(Token(STRING, word));
            }
        } else if (this->current == '"') {
            if (this->current == '"') {
                this->next();
                if (this->current == '"') {
                    this->next();
                    if (this->current == '"') { // Comment block.
                        if (!this->match("\"\"\"")) {
                            std::cout << "# Lexical error caught on comment #\n";
                            std::cout << "# Comment block was not closed #\n";
                            error = true;
                            return;
                        }
                        while (this->current != '\n') {
                            if (this->current != ' ') {
                                std::cout << "# Lexical error caught on '" << this->current << "' #\n";
                                std::cout << "# Comment block cannot have anything after its closure #\n";
                                error = true;
                                return;
                            }
                            this->next();
                        }
                    } else {
                        this->addTokenIntoTable(Token(STRING, ""));
                    }
                } else {
                word = this->current;
                while (this->next()) {
                    if (this->current == '"') {
                        break;
                    } else if (this->current == '\n') {
                        std::cout << "# Lexical error caught on: '" << word << "'\n";
                        std::cout << "# Invalid lexeme: unclosed string\n";
                        error = true;
                        return;
                    } 
                    word += this->current;
                }
                this->addTokenIntoTable(Token(STRING, word));
            }
            }
        } else if (std::isdigit(this->current) || this->current == '.') {
            while (std::isdigit(this->current) || this->current == '.') {
                if (this->current == '.' && isPresent(word, '.')) {
                    std::cout << "# Lexical error caught on '" << word << ".' #\n";
                    std::cout << "# Numbers may have only one dot. #\n";
                    error = true;
                    return;
                }
                word += this->current;
                this->next();
            }
            if (isPresent(word, '.')) {
                tag = FLOAT;
            } else {
                tag = INTEGER;
            }
            this->addTokenIntoTable(Token(tag, word));
        } else if (std::isalpha(this->current)) {
            while (std::isalnum(this->current)) {
                word += this->current;
                this->next();
            }
            this->previous();
            tag = ID;
            if (word == "if") {
                tag = IF;
            } else if (word == "else") {
                tag = ELSE;
            } else if (word == "for") {
                tag = FOR;
            } else if (word == "while") {
                tag = WHILE;
            } else if (word == "True" || word == "False") {
                tag = BOOL;
            } else if (word == "and") {
                tag = AND;
            } else if (word == "or") {
                tag = OR;
            } else if (word == "not") {
                tag = NOT;
            }
            this->addTokenIntoTable(Token(tag, word));
        } else {
            switch (this->current) {
                case '=':
                    word = "=";
                    tag = ASSIGNMENT; 
                    this->next();
                    if (this->current == '=') {
                        word += "=";
                        tag = EQUAL;
                    } else {
                        this->previous();
                    }
                    break;
                case '+':
                    word = "+";
                    tag = PLUS;
                    this->next();
                    if (this->current == '=') {
                        word += "=";
                        tag = PLUS_ASSIGNMENT;
                    } else {
                        this->previous();
                    }
                    break;
                case '-':
                    word = "-";
                    tag = MINUS;
                    this->next();
                    if (this->current == '=') {
                        word += "=";
                        tag = MINUS_ASSIGNMENT;
                    } else {
                        this->previous();
                    }
                    break;
                case '*':
                    word = "*";
                    tag = MULT;
                    this->next();
                    if (this->current == '=') {
                        word += "=";
                        tag = MULT_ASSIGNMENT;
                    } else if (this->current == '*') {
                        word += "*";
                        tag = POW;
                    } else {
                        this->previous();
                    }
                    break;
                case '/':
                    word = "/";
                    tag = DIV;
                    this->next();
                    if (this->current == '=') {
                        word += "=";
                        tag = DIV_ASSIGNMENT;
                    } else if (this->current == '/') {
                        word += "/";
                        tag = INT_DIV;
                    } else {
                        this->previous();
                    }
                    break;
                case '%':
                    word = "%";
                    tag = MOD;
                    this->next();
                    if (this->current == '=') {
                        word += "=";
                        tag = MOD_ASSIGNMENT;
                    } else {
                        this->previous();
                    }
                    break;
                case '!': 
                    this->next();
                    if (this->current == '=') {
                        tag = UNEQUAL;
                        word = "!=";
                        break;
                    } else {
                        std::cout << "# Lexical error caught on '!" << this->current << "' #\n";
                        std::cout << "# Unknown operator. Do you mean '!=' ? #\n";
                        error = true;
                        return;
                    }
                case ',':
                    word = ",";
                    tag = COMMA;
                    break;
                case '[':
                    word = "[";
                    tag = OPENING_BRACKET;
                    break;
                case '(':
                    word = "(";
                    tag = OPENING_PARENTHESIS;
                    break;
                case '{':
                    word = "{";
                    tag = OPENING_CURLY_BRACE;
                    break;
                case ']':
                    word = "]";
                    tag = CLOSING_BRACKET;
                    break;
                case ')':
                    word = ")";
                    tag = CLOSING_PARENTHESIS;
                    break;
                case '}':
                    word = "}";
                    tag = CLOSING_CURLY_BRACE;
                    break;
                case ':':
                    word = ":";
                    tag = COLON;
                    break;
                case '<':
                    word = "<";
                    tag = LESS_THAN;
                    this->next();
                    if (this->current == '=') {
                        word += "=";
                        tag = LESS_THAN_EQUAL;
                    } else {
                        this->previous();
                    }
                    break;
                case '>':
                    word = ">";
                    tag = GREATER_THAN;
                    this->next();
                    if (this->current == '=') {
                        word += "=";
                        tag = GREATER_THAN_EQUAL;
                    } else {
                        this->previous();
                    }
            }
            this->addTokenIntoTable(Token(tag, word));
        }        
        word = "";
    }
    if (error) {
        tokenTable.clear();
    }
    std::cout << "# Scan done successfully #\n";
}

std::map<std::string, Token> Lexer::getTokenTable() const {
    return tokenTable;
}

void Lexer::extractFileContent() {
    std::string temp;
    std::ifstream in(sourcePath);
    while (std::getline(in, temp)) {
        fileContent += temp + "\n";
    }
    i = -1; // Mark of what character is next.
}

int Lexer::getCurrentPos() {
    return i;
}
