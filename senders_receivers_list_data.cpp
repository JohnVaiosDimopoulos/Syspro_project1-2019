#include "senders_receivers_list_data.h"
#include <cstdlib>

//==CONSTRUCTOR-DESTRUCTOR==//

senders_receivers_list_data::senders_receivers_list_data(Transaction_info* transaction){
  this->transaction = transaction;
}

senders_receivers_list_data::~senders_receivers_list_data() {
  this->transaction = NULL;
}

//==ACCESSOR==//

Transaction_info* senders_receivers_list_data::get_info() const {
  return this->transaction;
}
