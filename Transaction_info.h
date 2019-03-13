#ifndef PROJECT1_VER3_TRANSACTION_INFO_H
#define PROJECT1_VER3_TRANSACTION_INFO_H

#include "Date.h"
class Transaction_info {

 private:
  char* sender_id;
  char* receiver_id;
  char* transaction_id;
  const int amount;
  Date date;

 public:
  //constructor-destructor
  Transaction_info(char*,char*,char*,int&,int&,int&,int&,int&,int&);
  ~Transaction_info();

  //accessors
  char* get_sender();
  char* get_receiver();
  int get_amount();
  void print_info();
  char* get_transaction_id();

  //other
  bool is_after(int&,int&,int&,int&,int&);

  //opperator
  bool operator==(const char*);
};

#endif //PROJECT1_VER3_TRANSACTION_INFO_H
