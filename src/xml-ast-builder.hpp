#ifndef XML_AST_BUILDER
#define XML_AST_BUILDER

#include "xml-lexer.hpp"
#include "xml-nodes.hpp"

#define LOG(X) std::cout << X << '\n';

struct TagHeader
{
    std::string tagName;
    std::map<std::string, std::string> tagAttributes;
};


class XmlAstBuilder
{
public:
    TagNode* rootNode;
    TokenList tokens;

    XmlAstBuilder(TokenList tokenList) : tokens(tokenList) {}

    void build();
    TagNode* buildTag();
    TagHeader buildTagHeader();
    bool isEndTagOpening();

    std::map<std::string, std::string> buildAttributes();
};

#endif