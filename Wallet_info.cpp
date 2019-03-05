#include "Wallet_info.h"
#include <cstdlib>
#include <cstring>

//==CONSTRUCTRO-DESTRUCTOR==//

Wallet_info::Wallet_info(char* id) {
  this->wallet_id = (char*)malloc(sizeof(char)*(strlen(id)+1));
  strcpy(this->wallet_id,id);
  this->bitcoins_owned = new List<Bitcoin_in_wallet*>();
}

Wallet_info::~Wallet_info() {
  free(this->wallet_id);
  delete this->bitcoins_owned;
}

//==ACCESSORS==//
List<Bitcoin_in_wallet*>* Wallet_info::get_list() {
  return this->bitcoins_owned;
}

char* Wallet_info::get_wallet_id() const {
  return this->wallet_id;
}


//===OPERATORS==//

bool Wallet_info::operator==(const char* id) {
  if(!strcmp(this->wallet_id,id))
    return true;
  else
    return false;
}
