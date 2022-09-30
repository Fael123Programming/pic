#pragma once

#include <iostream>
#include "Token.hpp"
#include <map>

class Lexer {
    public:
        Lexer(std::string sourcePath);

        void scan(); // Fetches all tokens and place them into 'tokenTable'.

        std::map<std::string, Token> getTokenTable() const;

        void printTokenTable() const;

    private:
        static int nextTrn;
        
        std::map<std::string, Token> tokenTable; 

        std::string sourcePath;

        std::string fileContent;

        std::string word;

        Tag tag;

        int i;

        char current;

        std::string getFileContent();
        
        bool next();

        bool previous();

        bool match(std::string);
        
        bool matchLine(std::string);

        bool tokenLexemeAlreadyInTokenTable(std::string);

        void extractFileContent();

        void addTokenIntoTable(Token);

        void handleHashtag();

        void handleQuote(char quote);

        void handleNumber();

        void handleAlpha();

        void handleOther();
};
