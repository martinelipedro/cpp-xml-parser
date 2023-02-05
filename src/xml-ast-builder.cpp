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

    if (tokens.current()->type == Token::TOK_ID)
    {
        std::string buffer;

        while (tokens.current()->type == Token::TOK_ID)
        {
            buffer.append(" " + tokens.eat(Token::TOK_ID)->value);
        }

        buffer.erase(0, 1);

        children.push_back(new TextNode(buffer));

        eatEndOfTag();

        TagNode* tag = new TagNode(header.tagName);
        tag->attributes = header.tagAttributes;
        tag->children = children;

        return tag;
    }


    while (tokens.current()->type == Token::TOK_STARTTAG && !isEndTagOpening())
    {
        children.push_back(buildTag());
    }

    

    


    TagNode* tag = new TagNode(header.tagName);
    tag->attributes = header.tagAttributes;
    tag->children = children;

    eatEndOfTag();

    return tag;
}

TagHeader XmlAstBuilder::buildTagHeader()
{
    TagHeader header;

    tokens.eat(Token::TOK_STARTTAG);
    header.tagName = tokens.eat(Token::TOK_ID)->value;
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

void XmlAstBuilder::eatEndOfTag()
{
    tokens.eat(Token::TOK_STARTTAG);
    tokens.eat(Token::TOK_SLASH);
    /* TODO: checar com o nome do header da tag */
    tokens.eat(Token::TOK_ID);
    tokens.eat(Token::TOK_ENDTAG);
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