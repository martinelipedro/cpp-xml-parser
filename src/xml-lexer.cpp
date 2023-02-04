#include "xml-lexer.hpp"

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
