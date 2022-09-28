#include <iostream>
#include "../../include/lexer/Token.h"

int Token::nextTrn = 1;

Token::Token(Tag tokenTag, std::string tokenLexeme) : tag(tokenTag), lexeme(tokenLexeme), trn(Token::nextTrn++) {}

std::string Token::getTag() const { 
    switch(tag) {
        case INTEGER:
            return "INTEGER";
        case FLOAT:
            return "FLOAT";
        case BOOL:
            return "BOOL";
        case STRING:
            return "STRING";
        case ID:
            return "ID";
        case IF:
            return "IF";
        case ELSE:
            return "ELSE";
        case FOR:
            return "FOR";
        case WHILE:
            return "WHILE";
        case ASSIGNMENT:
            return "ASSIGNMENT";
        case PLUS_ASSIGNMENT:
            return "PLUS_ASSIGNMENT";
        case MINUS_ASSIGNMENT:
            return "MINUS_ASSIGNMENT";
        case MULT_ASSIGNMENT:
            return "MULT_ASSIGNMENT";
        case DIV_ASSIGNMENT:
            return "DIV_ASSIGNMENT";
        case MOD_ASSIGNMENT:
            return "MOD_ASSIGNMENT";
        case COMMA:
            return "COMMA";
        case OPENING_BRACKET:
            return "OPENING_BRACKET";
        case OPENING_PARENTHESIS:
            return "OPENING_PARENTHESIS";
        case CLOSING_BRACKET:
            return "CLOSING_BRACKET";
        case CLOSING_PARENTHESIS:
            return "CLOSING_PARENTHESIS";
        case OPENING_CURLY_BRACE:
            return "OPENING_CURLY_BRACE";
        case CLOSING_CURLY_BRACE:
            return "CLOSING_CURLY_BRACE";
        case COLON:
            return "COLON";
        case EQUAL:
            return "EQUAL";
        case UNEQUAL:
            return "UNEQUAL";
        case GREATER_THAN:
            return "GREATER_THAN";
        case GREATER_THAN_EQUAL:
            return "GREATER_THAN_EQUAL";
        case LESS_THAN:
            return "LESS_THAN";
        case LESS_THAN_EQUAL:
            return "LESS_THAN_EQUAL";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case MULT:
            return "MULT";
        case DIV:
            return "DIV";
        case INT_DIV:
            return "INT_DIV";
        case MOD:
            return "MOD";
        case POW:
            return "POW";
        case AND:
            return "AND";
        case OR:
            return "OR";
        case NOT:
            return "NOT";
    } 
    return "UNKNOWN";
}

std::string Token::getLexeme() const { return lexeme; }

int Token::getTrn() const { return trn; }

std::string Token::asString() const {
    return "<" + getTag() + ", " + lexeme + ", " + std::to_string(trn) + ">";
}

std::ostream& operator <<(std::ostream& out, const Token& token) {
    out << token.asString();
    return out;
}
