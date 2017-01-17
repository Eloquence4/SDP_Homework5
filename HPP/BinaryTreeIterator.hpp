#ifndef BinaryTreeIteratorDef
#define BinaryTreeIteratorDef

class TreeIterator
{
    friend class BinaryTree;

public:

    // O(1), returns the data of the node the iterator is holding
    // Unstable, throws INVALID_ITERATOR
    VarType& data()
    {
        if(ptr == nullptr)
            throw INVALID_ITERATOR;

        return ptr->Data;
    }

    // O(logN) and O(N) in the worst case, returns and iterator to the target, does not change this iterator
    // Unstable, throws ITERATOR_NOT_FOUND
    TreeIterator search(const VarType& key)
    {
        return search(ptr, key);
    }

    // O(1), returns the data as a constant
    // Unstable, throws INVALID_ITERATOR
    const VarType& data() const
    {
        if(ptr == nullptr)
            throw INVALID_ITERATOR;

        return ptr->Data;
    }

    // O(1), the iterator goes to the left child
    // Unstable, throws IT_NO_LEFT_CHILD
    TreeIterator& operator++()
    {
        if(ptr->Left == nullptr)
            throw IT_NO_LEFT_CHILD;

        ptr = ptr->Left;
		
		return *this;
    }

    // O(1), the iterator goes to the left child
    // Unstable, throws IT_NO_LEFT_CHILD
    void GoLeft()
    {
        ++(*this);
    }

    // O(1), the iterator goes to the right child
    // Unstable, throws IT_NO_RIGHT_CHILD
    TreeIterator operator++(int)
    {
        if(ptr->Right == nullptr)
            throw IT_NO_RIGHT_CHILD;

        ptr = ptr->Right;
		
		return *this;
    }

    // O(1), the iterator goes to the right child
    // Unstable, throws IT_NO_RIGHT_CHILD
    void GoRight()
    {
        (*this)++;
    }

    // O(1), checks if the target of the iterator is a leaf
    bool leaf() const
    {
        if(ptr->Left || ptr->Right)
            return false;
        
        return true;
    }

    // O(1) or O(logN) if there are children on both sides, removes left child
    void remove_left()
    {
        if(ptr->Left == nullptr)
            return;
        remove(ptr->Left);
    }

    // O(1) or O(logN) if there are children on both sides, removes right child
    void remove_right()
    {
        if(ptr->Right == nullptr)
            return;
        remove(ptr->Right);
    }

    // O(1) or O(logN), if node has no children, return to the top
    void remove()
    {
        if(ptr->Occurrences > 1)
            ptr->Occurrences--;
        else if(ptr->Left && ptr->Right)
        {
            // Some randomness when chosing which side to reduce by 1, no idea if this works
            Tree_Node<VarType>* temp = (size_t)&ptr & 16 ? FindSmallest(ptr->Right) : FindBiggest(ptr->Left);

            ptr->Data = std::move(temp->Data);

            delete temp;
        }
        else if(ptr->Left || ptr->Right)
        {
            Tree_Node<VarType>* temp = ptr->Left ? ptr->Left : ptr->Right;

            ptr->Data = std::move(temp->Data);
			
			ptr->Left = temp->Left;
			ptr->Right = temp->Right;

            delete temp;
        }
        else
        {
            delete ptr;

            if(top == ptr)
                top = nullptr;

            ptr = top;
        }
    }

private:

    TreeIterator(Tree_Node<VarType>* _ptr)
        : top(_ptr)
        , ptr(_ptr)
    { }

    TreeIterator(Tree_Node<VarType>* _top, Tree_Node<VarType>* _ptr)
        : top(_top)
        , ptr(_ptr)
    { };

    TreeIterator search(Tree_Node<VarType>* node, const VarType& key)
    {
        if(node == nullptr)
            throw NOT_FOUND;

        if(key > node->Data)
            return search(node->Right, key);
        else if(key < node->Data)
            return search(node->Left, key);
        else
            return TreeIterator(top, node);
    }

    Tree_Node<VarType>* FindSmallest(Tree_Node<VarType>*& node)
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

    Tree_Node<VarType>* FindBiggest(Tree_Node<VarType>*& node)
    {
        if(node->Right != nullptr)
            return FindSmallest(node->Left);
        else
        {
            Tree_Node<VarType>* temp = node;

            node = nullptr;

            return temp;
        }
    }

    void remove(Tree_Node<VarType>*& node)
    {
        if(node->Occurrences > 1)
            node->Occurrences--;
        else if(node->Left && node->Right)
        {
            Tree_Node<VarType>* temp = node;

            // Some randomness when it choses Left or Right, no idea if this works
            node = (size_t)&node & 16 ? FindSmallest(node->Right) : FindBiggest(node->Left);

            node->Left = temp->Left;
            node->Right = temp->Right;

            delete temp;
        }
        else if(node->Left || node->Right)
        {
            Tree_Node<VarType>* temp = node;
            
            node = node->Left ? node->Left : node->Right;

            delete temp;
        }
        else
        {
            delete node;

            if(top == node)
                top == nullptr;

            node = nullptr;
        }
    }

    Tree_Node<VarType>*& top;
    Tree_Node<VarType>*  ptr;

};

#endif // BinaryTreeIteratorDef
