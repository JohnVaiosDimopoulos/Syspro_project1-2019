#ifndef PROJECT1_VER3_TRANSACTION_TREE_H
#define PROJECT1_VER3_TRANSACTION_TREE_H
#include "Transaction_tree_node.h"
#include "Hash_Table.h"

class Transaction_tree {

 private:
  Transaction_tree_node* root;
  void Search_for_leaf(char*,List<Transaction_tree_node*>*,Transaction_tree_node*);

 public:
  //constructor-destructor
  Transaction_tree(int,char*);
  ~Transaction_tree();

  //accessors
  Transaction_tree_node* get_root() const;

  //Functionality
  void New_Transaction(Transaction_info*, char*,char*,int);
  void Print_transactions(Hash_Table<Transaction_info*>*,Transaction_tree_node*);

  };

#endif //PROJECT1_VER3_TRANSACTION_TREE_H
