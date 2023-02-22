
#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <iostream>
#include <string>

//template of a Tree that can store type T data

template <typename T>
class Tree {
friend class InfectionAnalyzer;

public:
   
    Tree() = default;

    //deep copy constructor
    Tree(const Tree& another);

    //destructor 
    ~Tree();

    //deep assignment
    const Tree& operator=(const Tree& another);

    //return true if the tree is empty, false otherwise
    bool isEmpty() const { return root==nullptr; };

    //search in the whole tree
    //and return the tree pointer to the tree with the root node that contains the specified data 
    //return nullptr if the specified data is not found
    Tree* find(const T& data);

    //const version of find
    const Tree* find(const T& data) const;

    //return the depth of the node that contains the specified data in this whole tree
    //return -1 if the tree is empty or the data is not found
    //root node has a depth of 0
    int getDepth(const T& data) const;

    //return the descendant count of the node that contains the specified data in this whole tree
    //return -1 if the tree is empty or the data is not found
    //any direct or indirect child of a node is considered as a descendant of a node
    int getDescendantCount(const T& data) const;

    //return the descendant count of the root node in this whole tree
    //return -1 if the tree is empty or the data is not found
    int getDescendantCount() const;

    //add a new root with the specified data to the tree, and return true at the end
    //if the tree already has a root (i.e. non-empty tree), then make a new root while keeping the existing tree
    bool addRoot(const T& data); 

    //add a new node (child with data being childData) to an existing node (parent with data being parentData) in the tree, and return true at the end
    //however, if the parent node is not found in the tree or if the child data is already in the tree, do nothing and return false
    bool addChild(const T& parentData, const T& childData);

    //print the tree to the ostream
    void print(std::ostream &os, bool atRoot = true, std::string indentation = "", bool lastChild = true) const
    {
        os << indentation;
        if (!atRoot) //add indentation for non-root nodes
        {
            if (lastChild)
            {
                os << "\\-";
                indentation += "  ";
            }
            else
            {
                os << "|-";
                indentation += "| ";
            }
        }
        os << root->data << std::endl;

        for (int i = 0; i < root->childCount; i++)
            root->children[i].print(os, false, indentation, i == root->childCount - 1);
    }

private:
    Node<T>* root = nullptr; //root node of the tree
};


#include "treeImplementation.h"

#endif