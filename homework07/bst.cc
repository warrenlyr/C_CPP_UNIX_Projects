#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
// TODO: Implement this
    key = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
}
// Constructor
Node::Node(int in) {
// TODO: Implement this
    key = in;
    parent = NULL;
    left = NULL;
    right = NULL;
}
// Destructor
Node::~Node() {
// TODO: Implement this
    /*
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
    delete parent;
    delete left;
    delete right;
     */
}

// Add parent 
void Node::add_parent(Node* in) {
// TODO: Implement this
    this->parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
// TODO: Implement this
    this->left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
// TODO: Implement this
    this->right = in;
}

// Get key
int Node::get_key()
{
// TODO: Implement this
    return this->key;
}
// Get parent node
Node* Node::get_parent()
{
// TODO: Implement this
    if(this->parent == NULL){
        return NULL;
    }
    return this->parent;
}
// Get left node
Node* Node::get_left()
{
// TODO: Implement this
    if(this->left == NULL){
        return NULL;
    }
    return this->left;
}
// Get right node
Node* Node::get_right()
{
// TODO: Implement this
    if(this->right == NULL){
        return NULL;
    }
    return this->right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
// TODO: Implement this
    if(in){
        inorder_walk(in->get_left(), to);
        in->print_info(to);
        inorder_walk(in->get_right(), to);
    }
}
// Constructor
BST::BST()
{
// TODO: Implement this
    root = NULL;
}
// Destructor
BST::~BST()
{
// TODO: Implement this
    while(this->tree_min()){
        delete_node(this->tree_min());
    }
    
}

//Self added function for destructor
void BST::destroy(Node *in){
    if(in){
        if(!in->get_left() and !in->get_right()){
            delete in;
        }
        else{
            destroy(in->get_left());
            destroy(in->get_right());
        }
    }
}

// Insert a node to the subtree
void BST::insert_node(Node* in)
{
// TODO: Implement this
    if(this->root == NULL){
        this->root = in;
    }
    else{
        Node *thisParent = nullptr;
        Node *thisNode = this->root;
        while(thisNode != NULL){
            if(thisNode->get_key() <= in->get_key()){
                thisParent = thisNode;
                thisNode = thisNode->get_right();
            }
            else{
                thisParent = thisNode;
                thisNode = thisNode->get_left();
            }
        }
        //Now we are at the right position to insert the node
        if(thisParent->get_key() <= in->get_key()){
            thisParent->add_right(in);
            in->add_parent(thisParent);
        }
        else{
            thisParent->add_left(in);
            in->add_parent(thisParent);
        }
    }
}
// Delete a node to the subtree
void BST::delete_node(Node* out)
{
// TODO: Implement this
    
    if(!tree_search(out->get_key())){
        cout << "Delete Error, Node Not found!" << endl;
        exit(-1);
    }
    
    //Case 1: this node have no child
    //Then simply point it's parent to NULL
    if((out->get_right() == NULL) and (out->get_left() == NULL)){
        if(out == this->root){
            this->root = NULL;
        }
        else{
            if(out == out->get_parent()->get_left()){
                out->get_parent()->add_left(NULL);
            }
            else{
                out->get_parent()->add_right(NULL);
            }
        }
    }
    //Case 2: this node have only one child
    //Then replace it by it's child
    else if((out->get_left() == NULL) or (out->get_right() == NULL)){
        if(out->get_left() == NULL){
            //Have only right child
            if(out != this->root){
                if(out == out->get_parent()->get_left()){
                    out->get_parent()->add_left(out->get_right());
                    out->get_right()->add_parent(out->get_parent());
                }
                else{
                    out->get_parent()->add_right(out->get_right());
                    out->get_right()->add_parent(out->get_parent());
                }
            }
            else{
                this->root = out->get_right();
                out->get_right()->add_parent(NULL);
            }
        }
        else{
            //Have only left child
            if(out != this->root){
                if(out == out->get_parent()->get_left()){
                    out->get_parent()->add_left(out->get_left());
                    out->get_left()->add_parent(out->get_parent());
                }
                else{
                    out->get_parent()->add_right(out->get_left());
                    out->get_left()->add_parent(out->get_parent());
                }
            }
            else{
                this->root = out->get_left();
                out->get_left()->add_parent(NULL);
            }
        }
    }
    //Case 3: this node have 2 children
    //Then replace it by it's successor
    else{
        Node *successor = get_succ(out);
        //Delete the successor from the tree first
        //this->delete_node(successor);
        if(successor == successor->get_parent()->get_left()){
            successor->get_parent()->add_left(successor->get_right());
            if(successor->get_right()){
                successor->get_right()->add_parent(successor->get_parent());
            }
        }
        else{
            successor->get_parent()->add_right(successor->get_right());
            if(successor->get_right()){
                successor->get_right()->add_parent(successor->get_parent());
            }
        }
        
        //If we r deleting the root
        if(out == this->root){
            this->root = successor;
            successor->add_parent(NULL);
            successor->add_left(out->get_left());
            successor->add_right(out->get_right());
        }
        else{
            if(out == out->get_parent()->get_left()){
                //out is the left child
                out->get_parent()->add_left(successor);
                successor->add_parent(out->get_parent());
                successor->add_left(out->get_left());
                successor->add_right(out->get_right());
            }
            else{
                //Out id the right child
                out->get_parent()->add_right(successor);
                successor->add_parent(out->get_parent());
                successor->add_left(out->get_left());
                successor->add_right(out->get_right());
            }
        }
        if(out->get_left()){
            out->get_left()->add_parent(successor);
        }
        if(out->get_right()){
            out->get_right()->add_parent(successor);
        }
    }
    delete out;
}
// minimum key in the BST
Node* BST::tree_min()
{
// TODO: Implement this
    Node *thisNode = this->root;
    if(thisNode != NULL){
        while(thisNode->get_left() != NULL){
            thisNode = thisNode->get_left();
        }
    }
    return thisNode;
}
// maximum key in the BST
Node* BST::tree_max()
{
// TODO: Implement this
    Node *thisNode = this->root;
    if(thisNode != NULL){
        while(thisNode->get_right() != NULL){
            thisNode = thisNode->get_right();
        }
    }
    return thisNode;
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
// TODO: Implement this
    Node *thisNode = in;
    if(thisNode != NULL){
        while(thisNode->get_left() != NULL){
            thisNode = thisNode->get_left();
        }
    }
    return thisNode;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
// TODO: Implement this
    Node *thisNode = in;
    if(thisNode != NULL){
        while(thisNode->get_right() != NULL){
            thisNode = thisNode->get_right();
        }
    }
    return thisNode;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{
// TODO: Implement this
    /*
    Node *thisNode = in->get_right();
    if(thisNode != NULL){
        while(thisNode->get_left() != NULL){
            thisNode = thisNode->get_left();
        }
    }
    return thisNode;
     */
    if(in->get_right() != NULL){
        return get_min(in->get_right());
    }
    Node *thisNode = in;
    Node *thisParent = in->get_parent();
    while((thisParent != NULL) and (thisNode == thisParent->get_right())){
        thisNode = thisParent;
        thisParent = thisParent->get_parent();
    }
    return thisParent;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
// TODO: Implement this
    /*
    Node *thisNode = in->get_left();
    if(thisNode != NULL){
        while(thisNode->get_right() != NULL){
            thisNode = thisNode->get_right();
        }
    }
    return thisNode;
     */
    if(in->get_left() != NULL){
        return get_max(in->get_left());
    }
    Node *thisNode = in;
    Node *thisParent = in->get_parent();
    while((thisParent != NULL) and (thisNode == thisParent->get_left())){
        thisNode = thisParent;
        thisParent = thisParent->get_parent();
    }
    return thisParent;
}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
// TODO: Implement this
    inorder_walk(this->root, to);
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
// TODO: Implement this
    Node *thisNode = this->root;
    while(thisNode != NULL){
        if(thisNode->get_key() == search_key){
            break;
        }
        if(thisNode->get_key() < search_key){
            thisNode = thisNode->get_right();
        }
        else{
            thisNode = thisNode->get_left();
        }
    }
    return thisNode;
}
// ---------------------------------------
