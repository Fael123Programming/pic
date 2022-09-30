#pragma once

#include <iostream>
#include "Tag.hpp"

class Token {
    public:
        Token(Tag tag, std::string lexeme);

        Token();

        std::string getTag() const;

        std::string getLexeme() const;

        int getTrn() const;

        void setTrn(int trn);

        friend std::ostream& operator <<(std::ostream&, const Token&);

        std::string asString() const;
    private:
        Tag tag;
        
        std::string lexeme;
        
        int trn; //Table row number.
};
