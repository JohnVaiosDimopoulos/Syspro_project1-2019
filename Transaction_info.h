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
  char* get_sender() const;
  char* get_receiver() const ;
  int get_amount() const ;
  void print_info() const ;
  char* get_transaction_id() const ;
  Date get_date() const;

  //opperator
  bool operator==(const char*);
};

#endif //PROJECT1_VER3_TRANSACTION_INFO_H
