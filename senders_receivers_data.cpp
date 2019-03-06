#include "senders_receivers_data.h"
#include "cstring"
#include "cstdlib"

//==CONSTRUCTOR-DESTRUCTOR==//

senders_receivers_data::senders_receivers_data(char* id) {
  this->wallet_id = (char*)malloc(sizeof(char)*(strlen(id)+1));
  strcpy(this->wallet_id,id);
  transactions = new List<senders_receivers_list_data*>();
}

senders_receivers_data::~senders_receivers_data() {
  free(this->wallet_id);
  delete transactions;
}

//==ACCESSORS==//

char* senders_receivers_data::get_id() const {
  return this->wallet_id;
}

//==FUNCTIONALITY==/

void senders_receivers_data::Insert(Transaction_info* transaction) {
  senders_receivers_list_data* entry = new senders_receivers_list_data(transaction);
  this->transactions->Push(entry);
}