#include "xml-parser.hpp"

#include <iostream>


#define LOG(X) std::cout << X << '\n';

int main()
{
    XmlLexer lexer("<hello>Content</hello>");
    lexer.collect();

    for (Token* tok : lexer.tokenList)
    {
        LOG(tok->value);
    }


}