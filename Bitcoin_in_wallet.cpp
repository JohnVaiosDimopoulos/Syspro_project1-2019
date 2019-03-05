#include "Bitcoin_in_wallet.h"
#include <cstring>
#include <cstdlib>

//==CONSTRUCTOR-DESTRUCTOR==//


Bitcoin_in_wallet::Bitcoin_in_wallet(char* id, int value) {
  this->bitcoin_id = (char*)malloc(sizeof(char)*(strlen(id)+1));
  strcpy(bitcoin_id,id);
  this->value = value;
}

Bitcoin_in_wallet::~Bitcoin_in_wallet() {
  free (this->bitcoin_id);
}

//===ACCESSORS===//

char* Bitcoin_in_wallet::get_id() const {
  return this->bitcoin_id;
}

int Bitcoin_in_wallet::get_value() const {
  return this->value;
}

//==MUTATROS==//

void Bitcoin_in_wallet::update_value(int value) {
  this->value = value;
}

//==OPERATOR==//

bool Bitcoin_in_wallet::operator==(const char* id) {
  if (!strcmp(this->bitcoin_id,id))
    return true;
  else
    return false;
}