#include "xml-parser.hpp"

#include <iostream>



int main()
{
    XmlParser xmlParser("<hello></hello>");

    for (auto i : xmlParser.rootChildrenNames())
    {
        LOG(i)
    }

}