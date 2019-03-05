#ifndef PROJECT1_VER3_TRANSACTION_INFO_H
#define PROJECT1_VER3_TRANSACTION_INFO_H

class Transaction_info {

 private:
  char* sender_id;
  char* receiver_id;
  char* transaction_id;
  const int amount;
  const int year;
  const int month;
  const int day;
  const int hour;
  const int minutes;

 public:
  //constructor-destructor
  Transaction_info(char*,char*,char*,int&,int&,int&,int&,int&,int&);
  ~Transaction_info();

  //accessors
  char* get_sender();
  char* get_receiver();
  int get_amount();
  int get_year();
  int get_mounth();
  int get_day();
  char* get_transaction_id();

  //other
  bool is_after(int&,int&,int&,int&,int&);
};

#endif //PROJECT1_VER3_TRANSACTION_INFO_H
