// ==========================================
// Name: Anurag Prashant Umale              =
// Student Id: 1887255                      =
// E-mail: aumale@ucsc.edu                  =
// File: Dictionary.cpp						=
// Class: CSE 101 Spring 2023               =
// ==========================================
#include "Dictionary.h" // Including the Dictionary Header file

#define RED 0 // Defining the RED as 0
#define BLACK 1 // Defining BLACK as 1

Dictionary::Node::Node(keyType k, valType v)
{
    parent = nullptr; // setting the parent pointer to null pointer
    right = nullptr; // settung the right pointer to right pointer
    left = nullptr; // settting the left pointer to left pointer
    key = k; // setting the key value to k
    val = v; // setting the val value to v
    color = RED; // color is set to RED
}

Dictionary::Dictionary()
{
    nil = new Node("nil", 0); // dynamically allocating memeory and setting the key to "nil" and value to 0
    nil->color = BLACK; // setting the nil's color to BLACK
    root = nil; // setting the root pointer to the nil Node
    current = nil; // current pointer is set to niil Node
    num_pairs = 0; // num_pairs is set to 0
}

void Dictionary::preOrderCopy(Node *R, Node *N)
{
    if (R == N) // checkig if R is euqal to N
    {
        return; // returning from thr funtion
    }
    setValue(R->key, R->val);  // setting the key to the val of R
    preOrderCopy(R->left, N);  // recursive call on params left node and the node N
    preOrderCopy(R->right, N); // recursive call on params right node and the node N
}

Dictionary::Dictionary(const Dictionary &D)
{
    nil = new Node("nil", 0); // dynamically allocating memeory and setting the key to "nil" and value to 0
    nil->color = BLACK; // setting the nil's color to BLACK
    root = nil; // setting the root pointer to the nil Node
    current = nil; // current pointer is set to niil Node
    num_pairs = 0; // num_pairs is set to 0
    preOrderCopy(D.root,D.nil); // Calling the preOrderCopy function and Dictionary D's root and this pointer's root
}

Dictionary::~Dictionary()
{
    postOrderDelete(root); // calling the postOrderDelete function and this pointer's root Node is passed
    delete nil; // deleting the nil pointer
}

int Dictionary::size() const
{
    return num_pairs; // returning the the num_pairs 
}

Dictionary::Node *Dictionary::search(Node *R, keyType k) const
{
    if (R == nil || k == R->key) // checking if the R Node is equal to nil or R Node's key value is equal to k
    {
        return R; // returning R
    }
    else if (k < R->key) // checking if the key value is less then R Node's key value
    {
        return search(R->left, k);  // returning the resursive call of the function and passing R node's left pointer and k as parameter
    }
    else // else
    {
        return search(R->right, k);  // returning the resursive call of the function and passing R node's right pointer and k as parameter
    }
}

bool Dictionary::contains(keyType k) const
{
    return search(root, k) != nil; // returning the boolean value of return value of search funtion not equal to nil
}

valType &Dictionary::getValue(keyType k) const
{
    if (contains(k)) // calling the function contains and pass params k (check if k is in the Dictionary)
    {
        Node *node = search(root, k); // calling the seach function and root and k is paased aps paramteres
        return node->val; // returning the node's value
    }
    else // else
    {
        throw std::length_error("Dictionary: getValue(): key \"" + k + "\" does not exist"); // error message
    }
}

bool Dictionary::hasCurrent() const
{

    return current != nil; // returning the boolean value of equal current pointer is not equal to nil
}

keyType Dictionary::currentKey() const
{
    if (hasCurrent()) // checking if the current pointer is defined or not
    {
        return current->key; // returning the key of the current pointer
    }
    else // else
    {
        throw std::length_error("Dictionary: currentKey(): current undefined"); // error message
    }
}

valType &Dictionary::currentVal() const
{
    if (hasCurrent()) // checking if the current pointer is defined or not
    {
        return current->val; // returning the value of the current pointer 
    }
    else // else
    {
        throw std::logic_error("Dictionary: currentVal(): current undefined"); // Error Message
    }
}

void Dictionary::postOrderDelete(Node *R)
{
    if (R != nil) // checking if the R node is not equal to nil
    {
        postOrderDelete(R->left); // recursive call to the function and R node's left pointer is passed as parameter
        postOrderDelete(R->right); // recursive call to the function and R node's right pointer is passed as parameter
        num_pairs--; // number of pairs is decremented by 1
        delete R; // deleting the node R
    }
    R = nil; // R is set to nil
}

void Dictionary::clear()
{
    postOrderDelete(root); // postOrderDelete fucntion is called and root is passed 
    num_pairs = 0; // num_pairs is set to 0
    current = nil; // current pointer is set to nil
    root = nil; // root is set to nil
}

void Dictionary::setValue(keyType k, valType v)
{
    Node *node_tobe_inserted = new Node(k, v); // creating the new Node and k and v are passed as params
    node_tobe_inserted->left = nil; // setting the left node to nil
    node_tobe_inserted->right = nil; // setting the right node to nil
    Node *temp = nil; // temp node is created and set to nil
    Node *temp_root = root; // creating a node for storing the copy of root
    while (temp_root != nil) // looping till temp_root is not equal to nil
    {
        temp = temp_root; // temp is set to root
        if (k < temp_root->key) // checking if k is less than temp_root's key
        {
            temp_root = temp_root->left; // temp_root is set to temp_root's left node
        }
        else // else
        {
            temp_root = temp_root->right; // temp_root is set to temp_root's right
        }
    }
    node_tobe_inserted->parent = temp; // new node's parent pointer is set to temp
    if (temp == nil) // checking if temp is equal to nil
    {
        root = node_tobe_inserted; // setting the root to new node
    }
    else if (k < temp->key) // checking if k is less than temp's key
    {
        temp->left = node_tobe_inserted; // temp's left node is set to new node
    }
    else if (k > temp->key) // checking if k is greater than temp's key
    {
        temp->right = node_tobe_inserted; // temp's right pointer is set to new node
    }
    else // else
    {
        temp->val = v; // temp's val is set to v
        delete node_tobe_inserted; // deleting the new node
        return; // returning from the fucntion
    }
    num_pairs++; // num_pairs is incremented by 1
    node_tobe_inserted->left = nil; // new node's left pointer is set to nil
    node_tobe_inserted->right = nil; // new node's right pointer is set to nil
    node_tobe_inserted->color = RED; // new node's color is set to RED
    RB_InsertFixUp(node_tobe_inserted); // RB_InsertFixUp is called and new Node is passed as parameter
}

Dictionary::Node *Dictionary::findMin(Node *R)
{
    if (R == nil) // checking if the R node is equal to nil
    {
        return R; // returning R
    }
    Node *min = R; // creating copy of R
    while (min->left != nil) // copy of R's left is not equal to nil
    {
        min = min->left; // copy of R is set to copy of R's left node
    }
    return min; // returning the copy
}

Dictionary::Node *Dictionary::findMax(Node *R)
{
    if (R == nil) // checking if the R node is equal to nil
    {
        return nil; // returning R
    }
    Node *max = R; // creating copy of R
    while (max->right != nil) // copy of R's right is not equal to nil
    {
        max = max->right; // copy of R is set to copy of R's right node
    }
    return max; // returning the copy
}

Dictionary::Node *Dictionary::findNext(Node *R)
{
    // Doubtful condition
    if (R == nil) // checking if R node is equal to 
    {
        return nil; // returning nil
    }
    //
    Node *next = R; // creating the copy of R
    if (next->right != nil) // checking if copy's right pointer is not equal to nil
    {
        return findMin(next->right); // returning the minimum value in right sub-tree
    }
    Node *temp = next->parent; // creating temp variable for storing the copy's parent
    while (temp != nil && next == temp->right) // looping while temp is not equal to nil and copy is equal to temp's right pointer
    {
        next = temp; // setting the copy to temp
        temp = temp->parent; // temp is set temp's parent
    }
    return temp; // returning the temp
}

Dictionary::Node *Dictionary::findPrev(Node *R)
{
    if (R == nil) // checking if R node is equal to 
    {
        return nil; // returning the nil pointer
    }
    Node *prev = R; // creating the copy of R
    if (prev->left != nil) // checking if copy's left pointer is not equal to nil
    {
        return findMax(prev->left); // returning the maximum value in left sub-tree
    }
    Node *temp = prev->parent; // creating temp variable for storing the copy's parent
    while (temp != nil && prev == temp->left) // looping while temp is not equal to nil and copy is equal to temp's left pointer
    {
        prev = temp; // setting the copy to temp
        temp = temp->parent; // temp is set temp's parent
    }
    return temp; // returning the temp variable
}

void Dictionary::remove(keyType k)
{
    if (contains(k)) // checking if k exisit in the Dictionary
    {
        Node *node_tobe_removed = search(root, k); // searching the node in the dictoonary with key k
        if (node_tobe_removed == current) // checking if the node to be removed is being pointed by current pointer
        {
            current = nil; // setting the current pointer to nil
        }
        RB_Delete(node_tobe_removed); // Calling the RB_Delete function and node to be removed is passed
        delete node_tobe_removed; // deleteing the node
        num_pairs--; // decrememting the num_pairs
    }
    else // else
    {
        throw std::length_error("Dictionary: remove(): key \"" + k + "\" does not exist"); // error message
    }
}

void Dictionary::begin()
{
    current = findMin(root); // setting the current pointer to min node in the dictionary
}

void Dictionary::end()
{
    current = findMax(root); // setting the current pointer to max node in the dictionary
}

void Dictionary::next()
{
    if (hasCurrent()) // checking if the current pointer is exits
    {
        if (current == findMax(root)) // checking if the current pointer is equal to max node in the dictionary
        {
            current = nil; // setting the current to nil
            return; // returning from the fucntion 
        }
        current = findNext(current); // setting the current pointer to Next node after the current
    }
    else // else
    {
        throw std::length_error("Dictionary: next(): current undefined"); // Error Message
    }
}

void Dictionary::prev()
{
    if (hasCurrent()) // checking if the current pointer is exits
    {
        if (current == findMin(root)) // checking if the current pointer is equal to min node in the dictionary
        {
            current = nil; // setting the current to nil
            return; // returning from the fucntion 
        }
        current = findPrev(current); // setting the current pointer to previous node before the current
    }
    else // else
    {
        throw std::length_error("Dictionary: prev(): current undefined"); // Error Mesasage
    }
}

void Dictionary::LeftRotate(Node *N)
{
    Node *temp = N->right; // creating a temp variable and storing the right pointer of Node n
    N->right = temp->left; // setting the N's right pointer to temp's left pointer
    if (temp->left != nil) // temp's left node
    {
        temp->left->parent = N;
    }

    temp->parent = N->parent;
    if (N->parent == nil)
    {
        root = temp;
    }
    else if (N == N->parent->left)
    {
        N->parent->left = temp;
    }
    else
    {
        N->parent->right = temp;
    }

    temp->left = N;
    N->parent = temp;
}

void Dictionary::RightRotate(Node *N)
{
    Node *temp = N->left;

    N->left = temp->right;
    if (temp->right != nil)
    {
        temp->right->parent = N;
    }
    temp->parent = N->parent;
    if (N->parent == nil)
    {
        root = temp;
    }
    else if (N == N->parent->right)
    {
        N->parent->right = temp;
    }
    else
    {
        N->parent->left = temp;
    }

    temp->right = N;
    N->parent = temp;
}


// Got help from Section TA Amaan
void Dictionary::RB_InsertFixUp(Node *N)
{
    while (N->parent->color == RED)
    {
        if (N->parent == N->parent->parent->left)
        {
            Node *temp = N->parent->parent->right;
            if (temp->color == RED)
            {
                N->parent->color = BLACK;
                temp->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else
            {
                if (N == N->parent->right)
                {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }
        else
        {
            Node *temp = N->parent->parent->left;
            if (temp->color == RED)
            {
                N->parent->color = BLACK;
                temp->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else
            {
                if (N == N->parent->left)
                {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_Transplant(Node *u, Node *v)
{
    if (u->parent == nil)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_Delete(Node *N)
{
    Node *temp = N;
    Node *x;
    int y_original_color = temp->color;
    if (N->left == nil)
    {
        x = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil)
    {
        x = N->left;
        RB_Transplant(N, N->left);
    }
    else
    {
        temp = findMin(N->right);
        y_original_color = temp->color;
        x = temp->right;
        if (temp->parent == N)
        {
            x->parent = temp;
        }
        else
        {
            RB_Transplant(temp, temp->right);
            temp->right = N->right;
            temp->right->parent = temp;
        }
        RB_Transplant(N, temp);
        temp->left = N->left;
        temp->left->parent = temp;
        temp->color = N->color;
    }
    if (y_original_color == BLACK)
    {
        RB_DeleteFixUp(x);
    }
}

// Got help from Section TA Amaan
void Dictionary::RB_DeleteFixUp(Node *N)
{
    while (N != root && N->color == BLACK)
    {

        if (N == N->parent->left)
        {
            Node *w = N->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                N = N->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        }
        else
        {
            Node *w = N->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                N = N->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}

void Dictionary::inOrderString(std::string &s, Node *R) const
{
    if (R != nil)
    {
        inOrderString(s, R->left);
        std::string entry = (R->key + " : " + std::to_string(R->val) + "\n");
        s += entry;
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s.append(R->key);
        if(R->color == RED){
            s.append(" (RED)");
        }
        s.append("\n");
        preOrderString(s, R->left);
	    preOrderString(s, R->right);

    }
}

std::string Dictionary::to_string() const
{
    std::string s = "";
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const
{
    std::string s = "";
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary &D) const
{

    std::string s1 = to_string();
    std::string s2 = D.to_string();
    return (s1 == s2);
}

std::ostream &operator<<(std::ostream &stream, Dictionary &D)
{
    return stream << D.to_string();
}

bool operator==(const Dictionary &A, const Dictionary &B)
{
    return A.equals(B);
}

Dictionary &Dictionary::operator=(const Dictionary &D)
{
    if (this != &D)
    {
        Dictionary tempD = D;
        std::swap(nil, tempD.nil);
        std::swap(root, tempD.root);
        std::swap(current, tempD.current);
        std::swap(num_pairs, tempD.num_pairs);
    }
    return (*this);
}