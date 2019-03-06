#ifndef PROJECT1_VER3_SENDERS_RECEIVER_LIST_DATA_H
#define PROJECT1_VER3_SENDERS_RECEIVER_LIST_DATA_H

#include "Transaction_info.h"

class senders_receivers_list_data {

 private:
  Transaction_info* transaction;

 public:

  //constructor-destructor
  senders_receivers_list_data(Transaction_info*);
  ~senders_receivers_list_data();

  //accessor
  Transaction_info* get_info() const;

};

#endif //PROJECT1_VER3_SENDERS_RECEIVER_LIST_DATA_H
