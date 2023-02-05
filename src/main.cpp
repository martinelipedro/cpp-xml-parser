#include "xml-parser.hpp"

#include <iostream>



int main()
{
    XmlLexer lexer("<hello attr=\"asd\"><test></test><test2></test2></hello>");
    lexer.collect();

    TokenList tokenList(lexer.tokenList);
    XmlAstBuilder xmlBuilder(tokenList);

    xmlBuilder.build();

    LOG(xmlBuilder.rootNode->attributes["attr"]);
    LOG(xmlBuilder.rootNode->childs[0]->name);
    LOG(xmlBuilder.rootNode->childs[1]->name);
}