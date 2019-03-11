#include "Transaction_tree.h"
#include "List.h"
#include <cstdlib>
#include <cstring>


//==CONSTRUCTOR-DESTRUCTOR==//

Transaction_tree::Transaction_tree(int amount,char* owner ) {
  this->root = new Transaction_tree_node(NULL,amount,owner);
}

Transaction_tree::~Transaction_tree() {
  delete this->root;
}



//===ACCESSORS===//

Transaction_tree_node* Transaction_tree::get_root() const {
  return this->root;
}


//===PRIVATE==//
 void Transaction_tree::Search_for_leaf(char* owner,List<Transaction_tree_node*>* list,Transaction_tree_node* current) {

  // we want to get a list of all the leaf nodes that the owner of the bitcoin token is the sender

  // if it is a leaf
  if(current->get_left()==NULL && current->get_left()==NULL){
    // check the owner
    if(!strcmp(current->get_owner(),owner) && current->get_amount()!=0) {
      // if it is the one we are looking and there are money left in this token for push the token in the list
      list->Push(current);
      return;
    } else
      //else return
      return;
  }

  // if it is not a leaf search recursively in the tree
  if(current->get_left()!=NULL)
    Search_for_leaf(owner,list,current->get_left());
  if(current->get_right()!=NULL)
    Search_for_leaf(owner,list,current->get_right());

}




//===FUNCTIONALITY==//
void Transaction_tree::New_Transaction(Transaction_info* info, char* sender,char* receiver,int transaction_amount){

  // get a list with all the leaf nodes that can make the transaction
  List<Transaction_tree_node*>* leaf_list = new List<Transaction_tree_node*>();
  Search_for_leaf(sender,leaf_list,this->root);

  // check if there is a token that can make the transaction by itself
  Transaction_tree_node* transaction_leaf =leaf_list->Search(transaction_amount);

  if(transaction_leaf!=NULL){
    // we have our node
    // make its children
    Transaction_tree_node* left_child = new Transaction_tree_node(NULL,transaction_leaf->get_amount()-transaction_amount,sender);
    Transaction_tree_node* right_child = new Transaction_tree_node(info,transaction_amount,receiver);

    // set up the pointers
    transaction_leaf->set_left(left_child);
    transaction_leaf->set_right(right_child);
  }

  // there is'nt any node that can complete the transaction by itself
  else{
    // traverse the list until you have enough
      List_node<Transaction_tree_node*>* current = leaf_list->get_head();
      int amount_left = transaction_amount;

      while (current!=NULL && amount_left>0){

        if(current->get_item()->get_amount()<amount_left){

          Transaction_tree_node* left_child = new Transaction_tree_node(NULL,0,sender);
          Transaction_tree_node* right_child = new Transaction_tree_node(info,current->get_item()->get_amount(),receiver);

          current->get_item()->set_left(left_child);
          current->get_item()->set_right(right_child);

          amount_left = amount_left-current->get_item()->get_amount();

        }

        else{
          Transaction_tree_node* left_child = new Transaction_tree_node(NULL,current->get_item()->get_amount()-amount_left,sender);
          Transaction_tree_node* right_child = new Transaction_tree_node(info,amount_left,receiver);

          current->get_item()->set_left(left_child);
          current->get_item()->set_right(right_child);

          amount_left = amount_left- current->get_item()->get_amount();

        }
        current=current->get_next();

      }
  }

  //clear the list and delete it
  leaf_list->Nullify();
  delete leaf_list;
  return;
}




void Transaction_tree::Print_transactions(Hash_Table<Transaction_info*>* visited,Transaction_tree_node* current){

  // if the transaction of the token is not visited print it
  if((visited->Search(current->get_transaction()->get_transaction_id()))==NULL) {
    current->Print_transaction();
    visited->Insert(current->get_transaction(), current->get_transaction()->get_transaction_id());
  }

  if(current->get_left()!=NULL)
    Print_transactions(visited,current->get_left());
  if(current->get_right()!=NULL)
    Print_transactions(visited,current->get_right());


}