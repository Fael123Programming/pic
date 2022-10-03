#pragma once

#include <iostream>
#include "Tag.hpp"

class Token {
    public:
        Token(Tag, std::string);

        Token();

        std::string getTag() const;

        int getTrn() const;

        void setTrn(int trn);

        std::string getLexeme() const;

        friend std::ostream& operator <<(std::ostream&, const Token&);

        std::string toString() const;
    private:
        Tag tag;
        
        int trn; //Table row number.

        std::string lexeme;
};
