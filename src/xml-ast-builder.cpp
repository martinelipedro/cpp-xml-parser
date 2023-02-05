#include "xml-ast-builder.hpp"

#include <iostream>


void XmlAstBuilder::build()
{

    if (tokens.current()->type != Token::TOK_STARTTAG)
    {
        std::cerr << "Error, the source dont start with '<'" << '\n';
        exit(1);
    }
    
    rootNode = buildTag();

}

TagNode* XmlAstBuilder::buildTag()
{
    TagHeader header = buildTagHeader();
    std::vector<Node*> children;


    while (tokens.current()->type == Token::TOK_STARTTAG && !isEndTagOpening())
    {
        children.push_back(buildTag());
    }

    if (tokens.current()->type == Token::TOK_ID)
    {
        children.push_back(new TextNode("a content"));
    }

    tokens.eat(Token::TOK_STARTTAG);
    tokens.eat(Token::TOK_SLASH, "slash eat");
    /* TODO: checar com o nome do header da tag */
    tokens.eat(Token::TOK_ID, "apos todo");
    tokens.eat(Token::TOK_ENDTAG);


    TagNode* tag = new TagNode(header.tagName);
    tag->attributes = header.tagAttributes;
    tag->childs = children;


    return tag;
}

TagHeader XmlAstBuilder::buildTagHeader()
{
    TagHeader header;


    tokens.eat(Token::TOK_STARTTAG);
    header.tagName = tokens.eat(Token::TOK_ID, "NO HEADER")->value;
    header.tagAttributes = buildAttributes();
    tokens.eat(Token::TOK_ENDTAG);

    return header;
}

bool XmlAstBuilder::isEndTagOpening()
{
    if (tokens.current()->type == Token::TOK_STARTTAG && tokens.next()->type == Token::TOK_SLASH)
        return true;
    
    return false;
}

std::map<std::string, std::string> XmlAstBuilder::buildAttributes()
{
    std::map<std::string, std::string> buffer;

    while (tokens.current()->type == Token::TOK_ID)
    {
        std::string attrName = tokens.eat(Token::TOK_ID)->value;
        tokens.eat(Token::TOK_EQUALS);
        std::string attrValue = tokens.eat(Token::TOK_ID)->value;

        buffer.insert({attrName, attrValue});
    }

    return buffer;
}