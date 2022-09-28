#include <iostream>
#include "../../src/lexer/Token.cpp"
#include <map>

class Lexer {
    public:
        Lexer(std::string sourcePath);

        void scan(); // Fetches all tokens and place them into 'tokenTable'.

        std::map<std::string, Token> getTokenTable() const;

        bool next();

        bool previous();

        bool match(std::string);

        bool matchLine(std::string);
        
        char getCurrent();
        
        int getCurrentPos();
        
        void extractFileContent();

        std::string getFileContent();
    private:
        std::map<std::string, Token> tokenTable; 

        std::string sourcePath;

        std::string fileContent;

        int i;

        char current;

        // bool next();

        // bool previous();

        bool next(std::string);

        bool previous(std::string);

        void addTokenIntoTable(Token);

        bool existsInTokenTable(std::string);

};
