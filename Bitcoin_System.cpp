#include "Bitcoin_System.h"


            //===========================//
//==============CONSTRUCTOR-DESTRUCTOR=======================//
          //============================//


Bitcoin_System::Bitcoin_System(int bucket_size,int senders_table_size,int receivers_table_size,int bitcoin_table_size,int wallet_table_size,int bitcoin_value):bitcoin_value(bitcoin_value){

  // creating all the new elements
  this->wallets = new Hash_Table<Wallet_info*>(bucket_size,wallet_table_size);
  this->bitcoins_status = new Hash_Table<Bitcoin_Status*>(bucket_size,bitcoin_table_size);
  this->senders = new Hash_Table<senders_receivers_data*>(bucket_size,senders_table_size);
  this->receivers = new Hash_Table<senders_receivers_data*>(bucket_size,receivers_table_size);
  this->transactions = new List<Transaction_info*>();


}
Bitcoin_System::~Bitcoin_System(){

  //delete all the structures
  delete this->wallets;
  delete this->bitcoins_status;
  delete this->senders;
  delete this->receivers;
  delete this->transactions;
}



                //===========================//
//================PUBLIC-INITIALIZATION/BEGIN=============//
              //============================//

void Bitcoin_System::Initial_Transactions(char* transaction_file) {


}

void Bitcoin_System::Initialize_System(char* bitcoin_balances){

}

void Bitcoin_System::Begin_System() {

}



                          //=========================//
//============================PRIVATE-FUNCTIONALITY=========================////
                          //=========================//



void Bitcoin_System::Find_Earnings() {


}

void Bitcoin_System::Find_Receivings() {

}

void Bitcoin_System::Bitcoin_Stat() {

}

void Bitcoin_System::Wallet_Status() {

}

void Bitcoin_System::Trace_bitcoin() {

}

void Bitcoin_System::Request_Transaction() {

}

