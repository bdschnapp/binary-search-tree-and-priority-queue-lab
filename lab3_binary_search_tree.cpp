#include <iostream>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

//Max and min functions are written assuming the tree is in BST format.

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if (size == 0)
		return BinarySearchTree::TaskItem(-1, "N/A");
	TaskItem* temp = root;
	while(temp->right){
		temp = temp->right;
	}
	return temp;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if (size == 0)
		return BinarySearchTree::TaskItem(-1, "N/A");
	TaskItem* temp = root;
	while(temp->left){
		temp = temp->left;
	}
	return temp;
	
}

unsigned int BinarySearchTree::height_recur(TaskItem* val) const {
	if(val == NULL){
		return 0;
	}
	return 1 + max(height_recur(val->left), height_recur(val->right));
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	TaskItem* val = new TaskItem(root);
	return height_recur(val);
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	vector<string> vals;
	int h = height;
	int i = 0;
	while (i < 2*h - 1){
		vals.push_back("");
	}
	vals[0] = to_string(root->priority);
	TaskItem* next = new TaskItem(root);
	TaskItem* cur = new TaskItem(root);
	TaskItem* temp = new TaskItem(root);
	i = 1;
	int j = 1;
	do{
		while(cur->left){
			i++;	
		}
		j++;
		cur = temp = temp->right;
		next = cur->left;
	}while(cur->right);
	
	
}


// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	TaskItem* value = new TaskItem(val);
	TaskItem* temp = root;
	
	while(temp){
		if(*temp == *value)
			return true;
		if(temp->priority > value->priority)
			temp = temp->right;
		temp = temp->left;
	}
	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	return 0;
}

bool BinarySearchTree::insert_recur(TaskItem* val, TaskItem* cur){
	TaskItem* value = new TaskItem(val);
	TaskItem* curent = new TaskItem(cur);
	if(value->priority < cur->priority){
		if(curent->left != NULL)
			return insert_recur(value, cur->left);
		else{
			curent->left = value;
			return true;
		}		
	}
	if(value->priority > cur->priority){
		if(curent->right != NULL)
			return insert_recur(value, cur->right);
		else{
			curent->right = value;
			return true;
		}		
	}
	return false;	
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
	TaskItem* value = new TaskItem(val);
	
	if(root == NULL){
		root = value;
		return true;
	}
	
	return (insert_recur(value, root));
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
	TaskItem* value = new TaskItem(val);
	TaskItem* temp = root;
	
	if(!(value->exists()))
    	return false;
    
    while(!((temp->right==value) || (temp->left==value))){
    	if(value->priority > temp->priority)
    		temp = temp->right;
    	else
    		temp = temp->left;
	}
	
	TaskItem* temp2 = temp;
	if(temp2->right == value)
		temp2 = temp2->right;
	else
		temp2 = temp2->left;
	temp2 = temp2->left;
	
	
	while(temp2->right){
		if(!(temp2->right->right))
			
		temp2 = temp2->right;
		
	}
	TaskItem* temp3 = temp2;
	
	if(temp2->left){
		temp2 = temp2->left;
		temp3->left = NULL;
	}	
	else{
		temp2 = temp2->right;
		temp3->right = NULL;
	}
		
	temp2->right = temp->right;
	temp2->left = temp->left;
	if(temp->right == value)
		temp->right = temp2;
	else
		temp->left = temp2;
	return true;
}
