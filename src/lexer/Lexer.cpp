#include <cctype>
#include <iostream>
#include <fstream>
#include <ostream>
#include <algorithm>
#include <vector>
#include "../../include/lexer/Lexer.hpp"

bool isPresent(std::string str, char ch) {
    return str.find(ch) < str.size();
}

bool sortByTokenTableEntryNumber(const std::pair<std::string, Token> &pair1, const std::pair<std::string, Token> &pair2) {
    return pair1.second.getTrn() < pair2.second.getTrn();
}

std::pair<std::string, Token> makePair(std::string lexeme, Token tk) {
    return std::pair<std::string, Token> (lexeme, tk);
}

int Lexer::nextTrn = 1;

Lexer::Lexer(std::string sourcePath) : sourcePath(sourcePath) {}

void Lexer::scan() {
    this->extractFileContent(); // Lazy load of the file content.
    const int fileContentSize = fileContent.size();
    int wordSize;
    while (this->i < fileContentSize - 1) {
        this->next();
        switch (this->current) {
            case '#':
                this->handleHashtag();
                break;
            case '\'':
                this->handleQuote('\'');
                break;
            case '"':
                this->handleQuote('"');
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                this->handleNumber();
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
            case '_':
                this->handleAlpha();
                break;
            default:
                this->handleOther();
        }   
        word = "";
    }
    std::cout << "# Scan done successfully #\n";
}

std::map<std::string, Token> Lexer::getTokenTable() const {
    return tokenTable;
}

void Lexer::printTokenTable() const {
    if (tokenTable.empty()) {
        std::cout << "# Token table is empty #\n";
        return;
    }
    std::vector<std::pair<std::string, Token>> tempVec;
    for (
        std::map<std::string, Token>:: const_iterator it = tokenTable.begin(); 
        it != tokenTable.end(); 
        it++
    )  {
        tempVec.push_back(makePair(it->first, it->second));
    }
    std::sort(tempVec.begin(), tempVec.end(), sortByTokenTableEntryNumber);
    std::cout << "---------------------------------------------------------\n";
    std::cout << "		        Token Table\n";
    std::cout << "---------------------------------------------------------\n";
    for (int i = 0; i < tempVec.size(); i++) {
        std::cout << tempVec[i].second << std::endl;
    }
}

void Lexer::extractFileContent() {
    std::string temp;
    std::ifstream in(sourcePath);
    while (std::getline(in, temp)) {
        fileContent += temp + "\n";
    }
    i = -1; // Mark of what character is next.
}

std::string Lexer::getFileContent() {
    return fileContent;
}

void Lexer::addTokenIntoTable(Token tk) {
    if (!this->tokenLexemeAlreadyInTokenTable(tk.getLexeme())) {
        tk.setTrn(Lexer::nextTrn++);
        tokenTable.insert(std::pair<std::string, Token>(tk.getLexeme(), tk));
    }
}

bool Lexer::tokenLexemeAlreadyInTokenTable(std::string lexeme) {
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

void Lexer::handleHashtag() {
    this->match("\n"); // Ignore everything until a `\n` is found.
    this->previous();
}

void Lexer::handleQuote(char quote) {
    this->next();
    if (this->current == quote) {
        this->next();
        if (this->current == quote) { // Comment block.
            std::string s(1, quote);
            if (!this->match(s + s + s)) {
                std::cout << "# Syntax error caught on comment #\n";
                std::cout << "# Comment block was not closed #\n";
                exit(1);
            }
            while (this->current != '\n') {
                if (this->current != ' ') {
                    std::cout << "# Syntax error caught on '" << this->current << "' #\n";
                    std::cout << "# Comment block cannot have anything after its closure #\n";
                    exit(1);
                }
                this->next();
            }
        } else {
            this->addTokenIntoTable(Token(Tag::STRING, ""));
        }
    } else {
        while (this->current != '\n') {
            if (this->current == quote) {
                this->addTokenIntoTable(Token(Tag::STRING, word));
                return;
            }
            word += this->current;
            this->next();
        }
        std::cout << "# Syntax error caught on: " << quote << " #\n";
        std::cout << "# Invalid lexeme: unclosed string #\n";
        exit(1);
    }
}

void Lexer::handleNumber() {
    while (std::isdigit(this->current) || this->current == '.') {
        if (this->current == '.' && isPresent(word, '.')) {
            std::cout << "# Lexical error caught on '" << word << ".' #\n";
            std::cout << "# Numbers may have only one dot. #\n";
            exit(1);
        }
        word += this->current;
        this->next();
    }
    this->previous();
    if (isPresent(word, '.')) {
        tag = Tag::FLOAT;
    } else {
        tag = Tag::INTEGER;
    }
    this->addTokenIntoTable(Token(tag, word));
}

void Lexer::handleAlpha() {
    while (std::isalnum(this->current) || this->current == '_') {
        word += this->current;
        this->next();
    }
    this->previous();
    tag = Tag::ID;
    if (word == "if") {
        tag = Tag::IF;
    } else if (word == "else") {
        tag = Tag::ELSE;
    } else if (word == "for") {
        tag = Tag::FOR;
    } else if (word == "while") {
        tag = Tag::WHILE;
    } else if (word == "True" || word == "False") {
        tag = Tag::BOOL;
    } else if (word == "and") {
        tag = Tag::AND;
    } else if (word == "or") {
        tag = Tag::OR;
    } else if (word == "not") {
        tag = Tag::NOT;
    } else if (word == "in") {
        tag = Tag::IN;
    }
    this->addTokenIntoTable(Token(tag, word));
}

void Lexer::handleOther() {
    switch (this->current) {
        case '=':
            word = "=";
            tag = Tag::ASSIGNMENT; 
            this->next();
            if (this->current == '=') {
                word += "=";
                tag = Tag::EQUAL;
            } else {
                this->previous();
            }
            break;
        case '+':
            word = "+";
            tag = Tag::PLUS;
            this->next();
            if (this->current == '=') {
                word += "=";
                tag = Tag::PLUS_ASSIGNMENT;
            } else {
                this->previous();
            }
            break;
        case '-':
            word = "-";
            tag = Tag::MINUS;
            this->next();
            if (this->current == '=') {
                word += "=";
                tag = Tag::MINUS_ASSIGNMENT;
            } else {
                this->previous();
            }
            break;
        case '*':
            word = "*";
            tag = Tag::MULT;
            this->next();
            if (this->current == '=') {
                word += "=";
                tag = Tag::MULT_ASSIGNMENT;
            } else if (this->current == '*') {
                word += "*";
                tag = Tag::POW;
            } else {
                this->previous();
            }
            break;
        case '/':
            word = "/";
            tag = Tag::DIV;
            this->next();
            if (this->current == '=') {
                word += "=";
                tag = Tag::DIV_ASSIGNMENT;
            } else if (this->current == '/') {
                word += "/";
                tag = Tag::INT_DIV;
            } else {
                this->previous();
            }
            break;
        case '%':
            word = "%";
            tag = Tag::MOD;
            this->next();
            if (this->current == '=') {
                word += "=";
                tag = Tag::MOD_ASSIGNMENT;
            } else {
                this->previous();
            }
            break;
        case '!': 
            this->next();
            if (this->current == '=') {
                tag = Tag::UNEQUAL;
                word = "!=";
                break;
            } else {
                std::cout << "# Lexical error caught on '!" << this->current << "' #\n";
                std::cout << "# Unknown operator. Do you mean '!=' ? #\n";
                exit(1);
            }
        case ',':
            word = ",";
            tag = Tag::COMMA;
            break;
        case '[':
            word = "[";
            tag = Tag::OPENING_BRACKET;
            break;
        case '(':
            word = "(";
            tag = Tag::OPENING_PARENTHESIS;
            break;
        case '{':
            word = "{";
            tag = Tag::OPENING_CURLY_BRACE;
            break;
        case ']':
            word = "]";
            tag = Tag::CLOSING_BRACKET;
            break;
        case ')':
            word = ")";
            tag = Tag::CLOSING_PARENTHESIS;
            break;
        case '}':
            word = "}";
            tag = Tag::CLOSING_CURLY_BRACE;
            break;
        case ':':
            word = ":";
            tag = Tag::COLON;
            break;
        case '<':
            word = "<";
            tag = Tag::LESS_THAN;
            this->next();
            if (this->current == '=') {
                word += "=";
                tag = Tag::LESS_THAN_EQUAL;
            } else {
                this->previous();
            }
            break;
        case '>':
            word = ">";
            tag = Tag::GREATER_THAN;
            this->next();
            if (this->current == '=') {
                word += "=";
                tag = Tag::GREATER_THAN_EQUAL;
            } else {
                this->previous();
            }
            break;
        default:
            if (this->current != ' ' && this->current != '\n') {
                std::cout << "# Lexical error caught on '" << this->current << "'" << std::endl;
                std::cout << "# Unknown lexeme #\n";
                exit(1);
            }
    }
    if (!word.empty()) {
        this->addTokenIntoTable(Token(tag, word));
    }
}
