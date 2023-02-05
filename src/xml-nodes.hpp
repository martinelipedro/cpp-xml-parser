#ifndef XML_NODES_HPP
#define XML_NODES_HPP

class Visitor;
#include <vector>
#include <string>
#include <map>

enum NodeType
{
    TAG_NODE,
    TEXT_NODE
};

class Node
{
public:
    NodeType type;
    std::string name;
    std::map<std::string, std::string> attributes;
    Node(NodeType type, std::string name) : type(type), name(name) {}
};

class TagNode : public Node
{
public:
    std::vector<Node*> children;


    TagNode(std::string name) : Node(TAG_NODE, name) {}

    void addChild(Node* child)
    {
        children.push_back(child);
    }


    // TODO: retornar o mesmo valor, porém usando o template
    // com o valor do enum NodeType
    // para facilitar checagens
    template <typename T>
    T* getChildAs(unsigned int childPosition)
    {
        return (T*)children[childPosition];
    }

    Node* getChild(unsigned int childPosition)
    {
        return children[childPosition];
    }

};

class TextNode : public Node
{
public:
    TextNode(std::string name) : Node(TEXT_NODE, name) {}
};


#endif