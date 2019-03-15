#ifndef PROJECT1_VER3_BITCON_SYSTEM_H
#define PROJECT1_VER3_BITCON_SYSTEM_H
#include "Wallet_info.h"
#include "Bitcoin_Status.h"
#include "Transaction_info.h"
#include "senders_receivers_data.h"
#include "Hash_Table.h"

class Bitcoin_System {
 private:
  const int bucket_size;
  const int bitcoin_value;
  Date* most_recent;
  int max_transaction_id=0;
  Hash_Table<Wallet_info*>* wallets;
  Hash_Table<Bitcoin_Status*>* bitcoins_status;
  Hash_Table<senders_receivers_data*>* senders;
  Hash_Table<senders_receivers_data*>* receivers;
  List<Transaction_info*>* transactions;

  void Trace_bitcoin(char*);
  void Bitcoin_Stat(char*);
  void Transactions_from_file(char *, bool);
  void Find_Earnings_and_Payments(Hash_Table<senders_receivers_data*>* table,char *wallet_id,char *time1,char *time,char *date1,char *date2);
  void Wallet_Status(char*);
  void Request_Transaction(char *transaction_id,char *sender_id,char *receiver_id,int &amount,int &day,int &mounth,int &year,int &hour,int &minute,bool check_date);
  void Update_tree_and_wallets(Transaction_info*,Wallet_info*,Wallet_info*,char*,int);
  void Get_current_date(int*,int*,int*,int*,int*);
  bool Find_Earnings_and_Payments_get_args(char**,char**,char**,char**,char**);
  void Redirect_input_to_file(char *filename) const;
  bool Is_input_a_file(char *filename) const;




 public:
  // constructor-destructor
  Bitcoin_System(int,int,int,int,int,int);
  ~Bitcoin_System();

  //Initialization
  void Initialize_System(char*);
  void Initial_Transactions(char*);
  void set_max_transaction_id();

  //Begin
  void Begin_System();

};

#endif //PROJECT1_VER3_BITCON_SYSTEM_H
