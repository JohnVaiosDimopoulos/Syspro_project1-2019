#ifndef PROJECT1_VER3_WALLET_INFO_H
#define PROJECT1_VER3_WALLET_INFO_H

#include "List.h"
#include "Bitcoin_in_wallet.h"

class Wallet_info {
 private:
  char* wallet_id;
  List<Bitcoin_in_wallet*>* bitcoins_owned;

 public:
  //constructor-destructor
  Wallet_info(char*);
  ~Wallet_info();

  //mutators
  void update_bitcoin(char*,int);

  //accessors
  char* get_wallet_id() const;
  List<Bitcoin_in_wallet*>* get_list();

  //operrator

  bool operator==(const char*);

};

#endif //PROJECT1_VER3_WALLET_INFO_H
