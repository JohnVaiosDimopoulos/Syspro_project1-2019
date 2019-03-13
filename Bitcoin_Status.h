#ifndef PROJECT1_VER3_BITCOIN_STATUS_H
#define PROJECT1_VER3_BITCOIN_STATUS_H

#include "Transaction_tree.h"

class Bitcoin_Status {
 private:
  char* bitcoin_id;
  char* initial_owner;
  const int initial_value;
  int unspend_amount;
  int transactions_number;
  Transaction_tree* transaction_tree;

 public:
  //constructor-destructor
  Bitcoin_Status(int,char*,char*);
  ~Bitcoin_Status();

  //acessors
  int get_initial_value() const;
  int get_unspend_amount() const;
  int get_transactions_number() const;
  char* get_id() const;
  char* get_initial_owners_id() const;
  Transaction_tree* get_transaction_tree() const;

  //mutators
  void update_unspend_amount(int&);
  void increase_transaction_number();

  //functionality
  void New_Transaction(Transaction_info*,char*,char*,int);
  void Print_Transactions(int);

  //opperator
  bool operator==(const char*);

};

#endif //PROJECT1_VER3_BITCOIN_STATUS_H
