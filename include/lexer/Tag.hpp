#pragma once

enum Tag {
    // Data types.
    INTEGER = 256, FLOAT, BOOL, STRING,
    // Variables and functions.
    ID,
    // Assignment.
    ASSIGNMENT, PLUS_ASSIGNMENT, MINUS_ASSIGNMENT, MULT_ASSIGNMENT, DIV_ASSIGNMENT, MOD_ASSIGNMENT,
    // Bounds.
    COMMA, OPENING_BRACKET, OPENING_PARENTHESIS, CLOSING_BRACKET, CLOSING_PARENTHESIS,
    OPENING_CURLY_BRACE, CLOSING_CURLY_BRACE, COLON,
    // Relational operators.
    EQUAL, UNEQUAL, GREATER_THAN, GREATER_THAN_EQUAL, LESS_THAN, LESS_THAN_EQUAL,
    // Arithmetic operators.
    PLUS, MINUS, MULT, DIV, MOD, POW, INT_DIV,
    //Logic operators.
    AND, OR, NOT,
    IN,
    // Control flow.
    IF, ELSE, WHILE, FOR 
};
