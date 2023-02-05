#include "xml-lexer.hpp"

#include <iostream>

void XmlLexer::advance()
{
    if (currentChar)
    {
        index++;
        currentChar = source[index];
    }
}

void XmlLexer::collect()
{
    while (currentChar)
    {
        if (isalnum(currentChar))
        {
            collectID();
        }

        switch (currentChar)
        {
        case ' ': advance(); break;
        case '\n': advance(); break;
        case '\r': advance(); break;

        case '>': tokenList.push_back(new Token(Token::TOK_ENDTAG, ">")); advance(); break;
        case '<': tokenList.push_back(new Token(Token::TOK_STARTTAG, "<")); advance(); break;
        case '=': tokenList.push_back(new Token(Token::TOK_EQUALS, "=")); advance(); break;
        case '/': tokenList.push_back(new Token(Token::TOK_SLASH, "/")); advance(); break;
        
        default:
            advance();
            break;
        }
    }
}

void XmlLexer::collectID()
{
    std::string buffer;

    while (isalnum(currentChar))
    {
        buffer.push_back(currentChar);
        advance();
    }

    tokenList.push_back(new Token(Token::TOK_ID, buffer));
}



Token* TokenList::at(unsigned int index)
{
    return tokenList[index];
}

Token* TokenList::last()
{
    return tokenList[currentIndex - 1];
}

Token* TokenList::current()
{
    return tokenList[currentIndex];
}

Token* TokenList::next()
{
    return tokenList[currentIndex + 1];
}

Token* TokenList::advance()
{
    currentIndex++;
    return current();
}

Token* TokenList::eat(Token::TokenType type, std::string where)
{

    if (current()->type != type)
    {
        std::cerr << "ERROR, Expected: " << type << '\n' << "At: " << where;
        exit(1);
    }
    advance();
    return last();

}
