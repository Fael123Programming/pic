#include <iostream>
#include "../../src/lexer/Tag.cpp"


class Token {
    public:
        Token(Tag tag, std::string lexeme);

        Token();

        std::string getTag() const;

        std::string getLexeme() const;

        int getTrn() const;

        friend std::ostream& operator <<(std::ostream&, const Token&);

        std::string asString() const;
    private:
        Tag tag;
        
        std::string lexeme;
        
        int trn; //Table row number.

        static int nextTrn; //Static variable to computer what is the next table row number.
};
