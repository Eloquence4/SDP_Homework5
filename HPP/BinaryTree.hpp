#ifndef BinaryTreeDef
#define BinaryTreeDef

////////////////////////////////////////////// G4

template<typename VarType>
inline BinaryTree<VarType>::BinaryTree()
    : top(nullptr)
{ }

template<typename VarType>
inline BinaryTree<VarType>::~BinaryTree()
{
    remove_node(top);
}

template<typename VarType>
inline BinaryTree<VarType>::BinaryTree(const BinaryTree<VarType>& source)
    : top(nullptr)
{
    copy_node(top, source.top);
}

template<typename VarType>
inline BinaryTree<VarType>& BinaryTree<VarType>::operator=(const BinaryTree<VarType>& rhs)
{
    if(this != &rhs)
        copy_node(top, rhs.top);
    return *this;
}

////////////////////////////////////////////// Public

template<typename VarType>
inline void BinaryTree<VarType>::Add(const VarType& what)
{
    add(what, top);
}

template<typename VarType>
inline void BinaryTree<VarType>::Add(VarType && what)
{
    add(std::move(what), top);
}

template<typename VarType>
inline bool BinaryTree<VarType>::Remove(const VarType& key)
{
    try
    {
        Tree_Node<VarType>*& target = Find(top, key);

        if(target->Occurrences > 1)
            target->Occurrences--;
        else if(target->Left && target->Right)
        {
            Tree_Node<VarType>* temp = target;

            // Some randomness when it choses Left or Right (No idea if it works)
            target = (size_t)&target & 16 ? FindSmallest(target->Right) : FindBiggest(target->Left);

            target->Left = temp->Left;
            target->Right = temp->Right;

            delete temp;
        }
        else if(target->Left || target->Right)
        {
            Tree_Node<VarType>* temp = target;

            target = target->Left ? target->Left : target->Right;

            delete temp;
        }
        else
        {
            delete target;

            target = nullptr;
        }

        return true;
    }
    catch(TreeExceptions& err)
    {
        if(err == NOT_FOUND)
            return false;
        else
            throw err;
    }
}

////////////////////////////////////////////// Private

template<typename VarType>
inline Tree_Node<VarType>*& BinaryTree<VarType>::Find(Tree_Node<VarType>*& node, const VarType& key)
{
    if(node == nullptr)
        throw NOT_FOUND;

    if(key > node->Data)
        return Find(node->Right, key);
    if(key < node->Data)
        return Find(node->Left, key);

    return node;
}

template<typename VarType>
inline Tree_Node<VarType>* BinaryTree<VarType>::FindSmallest(Tree_Node<VarType>*& node)
{
    if(node->Left != nullptr)
        return FindSmallest(node->Left);
    else
    {
        Tree_Node<VarType>* temp = node;

        node = nullptr;

        return temp;
    }
}

template<typename VarType>
inline Tree_Node<VarType>* BinaryTree<VarType>::FindBiggest(Tree_Node<VarType>*& node)
{
    if(node->Right != nullptr)
        return FindBiggest(node->Right);
    else
    {
        Tree_Node<VarType>* temp = node;

        node = nullptr;

        return temp;
    }
}

template<typename VarType>
inline void BinaryTree<VarType>::add(const VarType& what, Tree_Node<VarType>*& node)
{
    if(node == nullptr)
        node = new Tree_Node<VarType>(what);
    else
        if(what < node->Data)
            add(what, node->Left);
        else if(what > node->Data)
            add(what, node->Right);
        else node->Occurrences++;
}

template<typename VarType>
inline void BinaryTree<VarType>::add(VarType&& what, Tree_Node<VarType>*& node)
{
    if(node == nullptr)
        node = new Tree_Node<VarType>(std::move(what));
    else
        if(what < node->Data)
            add(what, node->Left);
        else if(what > node->Data)
            add(what, node->Right);
        else node->Occurrences++;
}

template<typename VarType>
inline void BinaryTree<VarType>::remove_node(Tree_Node<VarType>*& cur)
{
    if(cur == nullptr)
        return;

    if(cur->Left != nullptr)
        remove_node(cur->Left);
    if(cur->Right != nullptr)
        remove_node(cur->Right);
    delete cur;
}

template<typename VarType>
inline void BinaryTree<VarType>::copy_node(Tree_Node<VarType>*& destination, Tree_Node<VarType>* source)
{
    if(source == nullptr)
    {
        remove_node(destination);
        destination = nullptr;
    }
    else
    {
        if(!destination)
            destination = new Tree_Node<VarType>(source->Data);
        else
            destination->Data = source->Data;

        copy_node(destination->Left, source->Left);
        copy_node(destination->Right, source->Right);
    }
    
}

#endif // BinaryTreeDec
