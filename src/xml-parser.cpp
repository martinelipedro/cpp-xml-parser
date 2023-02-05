#include "xml-parser.hpp"

XmlParser::XmlParser(std::string source)
{
    XmlLexer lexer(source);
    lexer.collect();
    TokenList tokenList(lexer.tokenList);
    XmlAstBuilder xmlBuilder(tokenList);
    xmlBuilder.build();
    
    rootNode = xmlBuilder.rootNode;
    
}