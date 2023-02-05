#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include "xml-ast-builder.hpp"

class XmlParser
{   
public:
    TagNode* rootNode;

    XmlParser(std::string source);

    /* Root Node Functions */
    size_t rootChildrenLen() 
    {
        return rootNode->children.size();
    }

    std::string rootName()
    {
        return rootNode->name;
    }

    std::map<std::string, std::string> rootAttributes()
    {
        return rootNode->attributes;
    }

    std::vector<std::string> rootChildrenNames()
    {
        std::vector<std::string> buffer;

        for (auto* el : rootNode->children)
        {
            buffer.push_back(el->name);
        }

        return buffer;
    }
};


#endif