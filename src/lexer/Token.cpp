#include <iostream>
#include "../../include/lexer/Token.hpp"
// #include "../../include/lexer/Tag.hpp"
// #include <magic_enum.hpp>  // header plus plus

Token::Token(Tag tokenTag, std::string lexeme) : tag(tokenTag), lexeme(lexeme) {}

std::string Token::getTag() const { 
    switch (this->tag) {
        case Tag::INTEGER:
            return "INTEGER";
        case Tag::FLOAT:
            return "FLOAT";
        case Tag::BOOL:
            return "BOOL";
        case Tag::STRING:
            return "STRING";
        case Tag::ID:
            return "ID";
        case Tag::ASSIGNMENT:
            return "ASSIGNMENT";
        case Tag::PLUS_ASSIGNMENT:
            return "PLUS_ASSIGNMENT";
        case Tag::MINUS_ASSIGNMENT:
            return "MINUS_ASSIGNMENT";
        case Tag::MULT_ASSIGNMENT:
            return "MULT_ASSIGNMENT";
        case Tag::DIV_ASSIGNMENT:
            return "DIV_ASSIGNMENT";
        case Tag::MOD_ASSIGNMENT:
            return "MOD_ASSIGNMENT";
        case Tag::COMMA:
            return "COMMA";
        case Tag::OPENING_BRACKET:
            return "OPENING_BRACKET";
        case Tag::OPENING_PARENTHESIS:
            return "OPENING_PARENTHESIS";
        case Tag::CLOSING_BRACKET:
            return "CLOSING_BRACKET";
        case Tag::CLOSING_PARENTHESIS:
            return "CLOSING_PARENTHESIS";
        case Tag::OPENING_CURLY_BRACE:
            return "OPENING_CURLY_BRACE";
        case Tag::CLOSING_CURLY_BRACE:
            return "CLOSING_CURLY_BRACE";
        case Tag::COLON:
            return "COLON";
        case Tag::EQUAL:
            return "EQUAL";
        case Tag::UNEQUAL:
            return "UNEQUAL";
        case Tag::GREATER_THAN:
            return "GREATER_THAN";
        case Tag::GREATER_THAN_EQUAL:
            return "GREATER_THAN_EQUAL";
        case Tag::LESS_THAN:
            return "LESS_THAN";
        case Tag::LESS_THAN_EQUAL:
            return "LESS_THAN_EQUAL";
        case Tag::PLUS:
            return "PLUS";
        case Tag::MINUS:
            return "MINUS";
        case Tag::MULT:
            return "MULT";
        case Tag::DIV:
            return "DIV";
        case Tag::MOD:
            return "MOD";
        case Tag::POW:
            return "POW";
        case Tag::INT_DIV:
            return "INT_DIV";
        case Tag::AND:
            return "AND";
        case Tag::OR:
            return "OR";
        case Tag::NOT:
            return "NOT";
        case Tag::IN:
            return "IN";
        case Tag::IF:    
            return "IF";
        case Tag::ELSE:
            return "ELSE";
        case Tag::WHILE:
            return "WHILE";
        case Tag::FOR:
            return "FOR";
        case Tag::BREAK:
            return "BREAK";
        case Tag::CONTINUE:
            return "CONTINUE";
    }
    return "UNKNOWN";
}

int Token::getTrn() const { return trn; }

void Token::setTrn(int trn) {
    this->trn = trn;
}

std::string Token::getLexeme() const {
    return this->lexeme;
}

std::ostream& operator <<(std::ostream& out, const Token& token) {
    out << token.toString();
    return out;
}

 std::string Token::toString() const {
    return "<" + this->getTag() + ", " + this->lexeme + ", " + std::to_string(trn) + ">";
}
