#ifndef BinaryTreeDec
#define BinaryTreeDec

enum TreeExceptions
{
    NO_SMALLER_ELEMENT,
    INVALID_ITERATOR,
    IT_NO_LEFT_CHILD,
    IT_NO_RIGHT_CHILD,
    NOT_FOUND
};

template <typename VarType>
struct Tree_Node
{
    size_t Occurrences;
    VarType Data;
    Tree_Node* Left;
    Tree_Node* Right;

    Tree_Node(const VarType& _Data = VarType(), Tree_Node* _Left = nullptr, Tree_Node* _Right = nullptr, size_t _Occurrences = 1)
        : Data(_Data)
        , Left(_Left)
        , Right(_Right)
        , Occurrences(_Occurrences)
    { }
};

// A binary tree, reaquires the VarType class to have operator>, < and == defined.

template <typename VarType>
class BinaryTree
{
public:
    // G4
    BinaryTree();
    ~BinaryTree();
    BinaryTree(const BinaryTree<VarType>& source);
    BinaryTree<VarType>& operator=(const BinaryTree<VarType>& rhs);
    /////

    // O(logN), up to O(N) in the worst case scenario, adds an element
    void Add(const VarType& what);
    void Add(VarType&& what);
    // O(logN) or O(2logN) or O(N) in the worst case scenario, removes and element, O(logN) to find it, and another O(logN) to find a replacement if it has 2 children
    // Returns true if it found and removed an element, false if it did not find one
    bool Remove(const VarType& key);

#include "../HPP/BinaryTreeIterator.hpp"

    // O(1), creates and iterator that targets the top element
    TreeIterator Top()
    {
        return TreeIterator(top);
    }

    // O(logN) or O(N) in the worst case scenario, finds an element
    // Unstable, throws NOT_FOUND if it does not find an element with the key
    TreeIterator Search(const VarType& key)
    {
        return search(top, key);
    }

private:

    Tree_Node<VarType>*& Find(Tree_Node<VarType>*& node, const VarType& key);

    Tree_Node<VarType>* FindSmallest(Tree_Node<VarType>*& node);

    Tree_Node<VarType>* FindBiggest(Tree_Node<VarType>*& node);

    void add(const VarType& what, Tree_Node<VarType>*& node);

    void add(VarType&& what, Tree_Node<VarType>*& node);

    void remove_node(Tree_Node<VarType>*& cur);

    void copy_node(Tree_Node<VarType>*& destination, Tree_Node<VarType>* source);

    TreeIterator search(Tree_Node<VarType>* node, const VarType& key)
    {
        if(node == nullptr)
            throw NOT_FOUND;

        if(key > node->Data)
            return search(node->Right, key);
        if(key < node->Data)
            return search(node->Left, key);

        return TreeIterator(top, node);
    }

    Tree_Node<VarType>* top;
};

#include "../HPP/BinaryTree.hpp"

#endif // BinaryTreeDec
