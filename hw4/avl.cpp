#pragma once
#include "exception.cpp"
#include <string>
#include <sstream>
#include <iostream>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

template <typename DATA_TYPE>
class avlTree
{
    // By placing this class definition inside the private section of the tree class, it is only accessible to the tree class
    class TreeNode
    {
    public:
        DATA_TYPE data;
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;

        // avl data
        int total_height;
        int left_height;
        int right_height;

        TreeNode() { parent = left = right = nullptr; total_height = left_height = right_height = 0; }
    };

    // This is the member variable that will be used to hold the comparison function
    int (*compare)(const DATA_TYPE& item1, const DATA_TYPE& item2);

    // This function searches the tree for the node that either contains a duplicate of the item, or the node that would be the parent of the item.
    TreeNode* findParentOrDuplicate(const DATA_TYPE& item);

    //
    void privateRotateRight(TreeNode* node);
    
    //
    void privateRotateLeft(TreeNode* node);
    
    //
    void postOrderDelete(TreeNode* node);
    
    //
    void privatePrintInOrder(TreeNode* node, int level = 0);

    // Private members
    TreeNode* root;
    int nodeCount;

public:
    // The constructor takes as a parameter the comparison function that will be used to determine the structure of the tree
    avlTree(int (*cmp)(const DATA_TYPE& item1, const DATA_TYPE& item2));
    ~avlTree();

    //
    int size();

    //
    void insert(DATA_TYPE item);
    
    //
    void remove(const DATA_TYPE& item);

    //
    DATA_TYPE search(const DATA_TYPE& item);

    //
    void printTree();

    //
    void rotateRight(DATA_TYPE item);

    //
    void rotateLeft(DATA_TYPE item);
};

// Private methods
template <typename DATA_TYPE>
typename avlTree<DATA_TYPE>::TreeNode* avlTree<DATA_TYPE>::findParentOrDuplicate(const DATA_TYPE& item)
//find parent or duplicate or node
{
    TreeNode* current = root;
    TreeNode* parent = current;

    while (current)
    {
        // -1 right (greater)
        // 1 left (less)
        // 0 item found
        parent = current;
        if (!compare(current->data, item))
            break;
        // Next, decide if we need to go left or right.
        if (compare(current->data, item) == 1) // Go left
            current = current->left;
        else // Go right. Duplicate is detected in the test of the while
            current = current->right;
    }

    return parent;
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::privateRotateRight(TreeNode* node)
{
    //rotating node passed in around its parent
    //left child stays the same
    //right child becomes new left child of original parent
    //nodes grandparent becomes nodes parent

    TreeNode* P = node->parent;
    TreeNode* GP = node->parent->parent;
    TreeNode* RC = node->right;
    TreeNode* LC = node->left;

    if(node == root || P->left != node)//node is the root or node isnt rotatable left (there is nothing to rotate)
    {
        return;
    }
    else if(GP)// node has a grandparent
    {
        if(RC)//node has a right child
        {            
            P->left = RC;
            RC->parent = P;

            node->right = P;
            P->parent = node;

            node->parent = GP;
            if(GP->right == P)
            {
                GP->right = node;
            }
            else if(GP->left == P)
            {
                GP->left = node;
            }
        }
        else if(!RC)//node does not have a right child
        {
            P->left = nullptr;

            node->right = P;
            P->parent = node;

            node->parent = GP;
            if(GP->right == P)
            {
                GP->right = node;
            }
            else if(GP->left == P)
            {
                GP->left = node;
            }

        }
    }
    else if(!GP && P == root)//node does not have a grandparent (nodes parent is root)
    {
        if(RC)//node has a right child
        {
            P->left = RC;
            RC->parent = P;

            node->right = P;
            P->parent = node;

            node->parent = nullptr;
            root = node;
        }
        else if(!node->right)// node does not have a right child
        {
            P->left = nullptr;

            node->right = P;
            P->parent = node;
            
            node->parent = nullptr;
            root = node;
        }

    }



}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::privateRotateLeft(TreeNode* node)
{
    //rotating node passed in around its parent
    //right child stays the same
    //left child becomes new right child of original parent
    //nodes grandparent becomes nodes parent

    TreeNode* P = node->parent;
    TreeNode* GP = node->parent->parent;
    TreeNode* RC = node->right;
    TreeNode* LC = node->left;

    if(node == root || P->right != node)//node is the root or node isnt rotatable right (there is nothing to rotate)
    {
        return;
    }
    else if(GP)// node has a grandparent
    {
        if(LC)//node has a left child
        {            
            P->right = LC;
            LC->parent = P;

            node->left = P;
            P->parent = node;

            node->parent = GP;
            if(GP->left == P)
            {
                GP->left = node;
            }
            else if(GP->right == P)
            {
                GP->right = node;
            }
        }
        else if(!LC)//node does not have a left child
        {
            P->right = nullptr;

            node->left = P;
            P->parent = node;

            node->parent = GP;
            if(GP->left == P)
            {
                GP->left = node;
            }
            else if(GP->right == P)
            {
                GP->right = node;
            }

        }
    }
    else if(!GP && P == root)//node does not have a grandparent (nodes parent is root)
    {
        if(LC)//node has a left child
        {
            P->right = LC;
            LC->parent = P;

            node->left = P;
            P->parent = node;

            node->parent = nullptr;
            root = node;
        }
        else if(!node->left)// node does not have a left child
        {
            P->right = nullptr;
            
            node->left = P;
            P->parent = node;
            
            node->parent = nullptr;
            root = node;
        }

    }


}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::postOrderDelete(TreeNode* node)
{
    if (!node)
        return;

    postOrderDelete(node->left);
    postOrderDelete(node->right);
    delete node;
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::privatePrintInOrder(TreeNode* node, int level)
{
    if (!node)
    {
        level--;
        return;
    }

    level++;
    cout << "Level: " << level << " Data: " << node->data << " " << endl;  // visit
    privatePrintInOrder(node->left,level);
    privatePrintInOrder(node->right,level);
}

// Public methods
template <typename DATA_TYPE>
int avlTree<DATA_TYPE>::size()
{
    return nodeCount;
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::printTree()
{
    privatePrintInOrder(root);
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::rotateRight(DATA_TYPE item)

{
    TreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->data, item))
    {
        // Throw ItemNotFoundException
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    privateRotateRight(findParentOrDuplicate(item));
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::rotateLeft(DATA_TYPE item)
{
    TreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->data, item))
    {
        // Throw ItemNotFoundException
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    privateRotateLeft(findParentOrDuplicate(item));
}

template <typename DATA_TYPE>
avlTree<DATA_TYPE>::avlTree(int (*cmp)(const DATA_TYPE& item1, const DATA_TYPE& item2))
{
    compare = cmp;
    nodeCount = 0;
    root = nullptr;
}

template <typename DATA_TYPE>
avlTree<DATA_TYPE>::~avlTree()
{
    postOrderDelete(root);
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::insert(DATA_TYPE item)
{
    if(!root) // Insert into an empty tree
    {
        root = new TreeNode();
        root->data = item;
        nodeCount++;
        return;
    }

    // Find the parent node, or identify a duplicate entry
    TreeNode* searchNode = findParentOrDuplicate(item);
    if (!compare(searchNode->data, item)) // Check to see if the item already exists
    {
        // Duplicate item detected, throw an exception
        DuplicateItemException exception(__LINE__, "Duplicate item detected. Unable to insert");
        throw exception;
    }

    // Item didn't exist, we can proceed as normal. searchNode now points to the parent node
    
    // Create new node
    TreeNode* node = new TreeNode();
    node->data = item;

    // Link the parent
    node->parent = searchNode;

    // Determine if the node will be a left or right child
    // Attach the node to the appropriate side
    if (compare(searchNode->data, item) == 1) // left child
        searchNode->left = node;
    else
        searchNode->right = node;

    // Increment the node counter
    nodeCount++;
}

template <typename DATA_TYPE>
void avlTree<DATA_TYPE>::remove(const DATA_TYPE& item)
{
    // Find the item to remove
    TreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->data, item))
    {
        // Throw item not found exception
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    // Check to see if it is a simple or hard case
    if (searchResult->left && searchResult->right)
    {
        // If hard
        // reduce to a simple case, then reset the pointer
        // Find the immediate predecessor
        TreeNode* current = searchResult->left;
        while (current->right)
            current = current->right;
        // Swap the data item
        DATA_TYPE tmp = searchResult->data;
        searchResult->data = current->data;
        current->data = tmp;

        // Set searchResult to the immediate predecessor
        searchResult = current;
    }

    TreeNode* child = searchResult->right ? searchResult->right : searchResult->left;
    TreeNode* parent = searchResult->parent;
    
    if(parent)
    {
        // I'm using a double pointer here rather than having a separate if/else for this.
        TreeNode** side = parent->right== searchResult ? &(parent->right) : &(parent->left);
        *side = child;
        if(child) 
            child->parent = parent;
    }
    else
    {
        // Node was the root
        root = child;
    }

    delete searchResult;
    
    nodeCount--;
}

template <typename DATA_TYPE>
DATA_TYPE avlTree<DATA_TYPE>::search(const DATA_TYPE& item)
{
    TreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->data, item))
    {
        // Throw ItemNotFoundException
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    return searchResult->data; 
}

