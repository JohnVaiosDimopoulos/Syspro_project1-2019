#include "Transaction_tree_node.h"
#include <cstdlib>
#include <cstring>
#include <iostream>


//==CONSTRUSTOR-DESTRUCTOR==//
Transaction_tree_node::Transaction_tree_node(Transaction_info* info,int amount,char* owner) {
  this->info = info;
  this->amount=amount;
  this->owner = (char*)malloc(sizeof(char)*(strlen(owner)+1));
  strcpy(this->owner,owner);
}

Transaction_tree_node::~Transaction_tree_node() {
  delete this->left;
  delete this->right;
  free(this->owner);
  this->info=NULL;
}

//==ACCESSORS==//
Transaction_tree_node* Transaction_tree_node::get_left() {
  return this->left;
}

Transaction_tree_node* Transaction_tree_node::get_right() {
  return this->right;
}

Transaction_info* Transaction_tree_node::get_transaction() {
  return this->info;
}

void Transaction_tree_node::Print_transaction() {
  this->info->print_info();
}

char* Transaction_tree_node::get_owner() {
  return this->owner;
}


int Transaction_tree_node::get_amount() {
  return this->amount;
}

//===MUTATORS==//

void Transaction_tree_node::set_left(Transaction_tree_node* left) {
  this->left = left;
}

void Transaction_tree_node::set_right(Transaction_tree_node* right) {
  this->right = right;
}

//==OPPERATOR==//
bool Transaction_tree_node::operator==(int& value){
  if(value<=amount)
    return true;
  else
    return false;
}