#include "xml-parser.hpp"

#include <iostream>


#define LOG(X) std::cout << X << '\n';

int main()
{
    TagNode* a_tag = new TagNode("root");
    TextNode* text_part = new TextNode("textTag", "hello");

    a_tag->addChild(text_part);
    
    LOG(a_tag->getChildAs<TextNode>(0)->content);
    






}