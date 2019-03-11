#ifndef PROJECT1_VER3_TRANSACTION_TREE_NODE_H
#define PROJECT1_VER3_TRANSACTION_TREE_NODE_H
#include "Transaction_info.h"

class Transaction_tree_node {

 private:
  Transaction_info* info;
  Transaction_tree_node* left;
  Transaction_tree_node* right;
  char* owner;
  int amount;

 public:
  //constructor-destructor
  Transaction_tree_node(Transaction_info*,int,char*);
  ~Transaction_tree_node();

  //accessors
  char* get_owner();
  int get_amount();
  void Print_transaction();
  Transaction_tree_node* get_right();
  Transaction_tree_node* get_left();
  Transaction_info* get_transaction();

  //mutators
  void set_left(Transaction_tree_node*);
  void set_right(Transaction_tree_node*);

  //opperator
  bool operator==(int&);





};

#endif //PROJECT1_VER3_TRANSACTION_TREE_NODE_H
