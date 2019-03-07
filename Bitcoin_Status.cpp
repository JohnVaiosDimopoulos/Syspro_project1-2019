#include "Bitcoin_Status.h"
#include <cstring>
#include <cstdlib>

//==CONSTRACTOR-DESTRUCTOR==//

Bitcoin_Status::Bitcoin_Status(int initial_value, char* id):initial_value(initial_value) {
  this->bitcoin_id = (char*)malloc(sizeof(char)*(strlen(id)+1));
  strcpy(this->bitcoin_id,id);

  transaction_tree = new Transaction_tree();
}

Bitcoin_Status::~Bitcoin_Status() {
  free(bitcoin_id);
  delete transaction_tree;
}

//==ACCESSORS==//
Transaction_tree * Bitcoin_Status::get_transaction_tree() const {
  return this->transaction_tree;
}

int Bitcoin_Status::get_transactions_number() const {
  return this->transactions_number;
}

int Bitcoin_Status::get_unspend_amount() const {
  return this->unspend_amount;
}

int Bitcoin_Status::get_initial_value() const {
  return this->initial_value;
}

char* Bitcoin_Status::get_id() const {
  return this->bitcoin_id;
}

//==MUTATORS==//

void Bitcoin_Status::increase_transaction_number() {
  this->transactions_number++;
}

void Bitcoin_Status::update_unspend_amount(int& amount) {

  this->unspend_amount = this->unspend_amount-amount;
}


//===OPPERATOR==//

bool Bitcoin_Status::operator==(const char *id) {
  if(!strcmp(this->bitcoin_id,id)){
    return true;
  } else
    return false;
}
