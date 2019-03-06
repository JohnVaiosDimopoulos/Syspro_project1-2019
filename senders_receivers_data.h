#ifndef PROJECT1_VER3_SENDERS_RECEIVERS_DATA_H
#define PROJECT1_VER3_SENDERS_RECEIVERS_DATA_H

#include "senders_receivers_list_data.h"
#include "List.h"
class senders_receivers_data {

 private:
  char* wallet_id;
  List<senders_receivers_list_data*>* transactions;

 public:

  //constructor-destructor
  senders_receivers_data(char*);
  ~senders_receivers_data();

  //accessors
  char* get_id() const;

  //functionality
  void Insert(Transaction_info*);
};

#endif //PROJECT1_VER3_SENDERS_RECEIVERS_DATA_H

