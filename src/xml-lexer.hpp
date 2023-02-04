#ifndef XML_LEXER_HPP
#define XML_LEXER_HPP

#include <string>
#include <vector>

struct Token
{
    enum TokenType
    {
        TOK_STARTTAG,
        TOK_ENDTAG,
        TOK_ID,
        TOK_EQUALS,
        TOK_SLASH,

    } type;
    std::string value;

    Token(int TokenType, std::string value) : type(type), value(value) {}
};

class XmlLexer
{
public:
    unsigned int index;
    char currentChar;
    std::string source;
    std::vector<Token*> tokenList;

    void advance();
    void collect();
    void collectID();


    XmlLexer(std::string source) : source(source), currentChar(source[0]), index(0) {}
};


#endif