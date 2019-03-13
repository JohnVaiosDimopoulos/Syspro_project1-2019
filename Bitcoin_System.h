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
  Hash_Table<Wallet_info*>* wallets;
  Hash_Table<Bitcoin_Status*>* bitcoins_status;
  Hash_Table<senders_receivers_data*>* senders;
  Hash_Table<senders_receivers_data*>* receivers;
  List<Transaction_info*>* transactions;

  void Trace_bitcoin(char*);
  void Bitcoin_Stat(char*);
  void Find_Earnings_and_Payments(Hash_Table<senders_receivers_data*>* table,char *wallet_id,char *time1,char *time,char *date1,char *date2);
  void Wallet_Status(char*);
  void Request_Transaction(char*,char*,char*,int&,int&,int&,int&,int&,int&,int);
  void Update_tree_and_wallets(Transaction_info*,Wallet_info*,Wallet_info*,char*,int);
  void Get_current_date(int*,int*,int*,int*,int*);

 public:
  // constructor-destructor
  Bitcoin_System(int,int,int,int,int,int);
  ~Bitcoin_System();

  //Initialization
  void Initialize_System(char*);
  void Transactions_from_file(char *);

  //Begin
  void Begin_System();

};

#endif //PROJECT1_VER3_BITCON_SYSTEM_H
