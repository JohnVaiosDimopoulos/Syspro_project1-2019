#ifndef PROJECT1_VER3_BITCOIN_IN_WALLET_H
#define PROJECT1_VER3_BITCOIN_IN_WALLET_H

class Bitcoin_in_wallet {

 private:
  char* bitcoin_id;
  int value;

 public:
  //constructor-destructor
  Bitcoin_in_wallet(char* ,int);
  ~Bitcoin_in_wallet();

  //accessors
  char* get_id() const;
  int get_value() const;

  //mutators
  void update_value(int);

  //operator
  bool operator==(const char*);

};

#endif //PROJECT1_VER3_BITCOIN_IN_WALLET_H
