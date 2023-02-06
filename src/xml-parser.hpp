#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include "xml-ast-builder.hpp"

#include <optional>
#include <iterator>

class XmlParser
{
public:
    TagNode *rootNode;

    XmlParser(std::string source);

    TagNode *root() const { return rootNode; }

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

        for (auto *el : rootNode->children)
        {
            buffer.push_back(el->name);
        }

        return buffer;
    }

    size_t getTagChildrenSize(Node *node)
    {
        if (node->type == TAG_NODE)
        {
            return static_cast<TagNode *>(node)->children.size();
        }

        return -1;
    }

    /* Find functions */

    // TODO: essa função n tá gerando o número certo de tags, ela ainda n procura mais a fundo.
    // TODO: seria interessante torna-lá recursiva
    size_t getNodeCount() const
    {
        // Root Node
        size_t count = 1;

        for (Node *el : root()->children)
        {
            if (el->type == TAG_NODE)
            {
                for (int i = 0; i < static_cast<TagNode *>(el)->children.size(); i++)
                {
                    TagNode *tag = static_cast<TagNode *>(el);
                    count += tag->children.size();
                }
            }
            count += 1;
        }

        return count;
    }


    std::optional<TagNode *> findTag(std::string tagName, TagNode *tagToSearch) const
    {
        for (int j = 0; j < tagToSearch->children.size(); j++)
        {
            if (tagToSearch->children[j]->name == tagName)
            {
                return static_cast<TagNode *>(tagToSearch->children[j]);
            }

            if (tagToSearch->children[0])
            {
                for (int i = 0; i < tagToSearch->children.size(); i++)
                {
                    std::optional<TagNode *> maybeValue = findTag(tagName, static_cast<TagNode *>(tagToSearch->children[i]));

                    if (maybeValue.has_value())
                    {
                        return maybeValue;
                    }
                }
            }
        }

        return std::nullopt;
    }

    // TODO: Find all

    std::vector<std::string> getTagAttrValues(TagNode *node) const
    {
        std::vector<std::string> buffer;

        for (std::map<std::string, std::string>::iterator it = node->attributes.begin(); it != node->attributes.end(); ++it)
        {
            buffer.push_back(it->second);
        }

        return buffer;
    }
    std::vector<std::string> getTagAttrNames(TagNode *node) const
    {
        std::vector<std::string> buffer;

        for (std::map<std::string, std::string>::iterator it = node->attributes.begin(); it != node->attributes.end(); ++it)
        {
            buffer.push_back(it->first);
        }

        return buffer;
    }

    size_t getTagAttributesSize(TagNode *node) const
    {
        return node->attributes.size();
    }
};

#endif