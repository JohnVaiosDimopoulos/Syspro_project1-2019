#include "Bitcoin_System.h"
#include <fstream>
#include <iostream>


            //===========================//
//==============CONSTRUCTOR-DESTRUCTOR=======================//
          //============================//


Bitcoin_System::Bitcoin_System(int bucket_size,int senders_table_size,int receivers_table_size,int bitcoin_table_size,int wallet_table_size,int bitcoin_value):bitcoin_value(bitcoin_value),bucket_size(bucket_size){

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
  //TODO: after the Requet_Transaction is done complete this


}

void Bitcoin_System::Initialize_System(char* bitcoin_balances){
  std::fstream bitcoin_file;
  char* temp_ptr;
  //initialize two hash tables for checking

  //open the file
  bitcoin_file.open(bitcoin_balances,std::fstream::in);

    if(bitcoin_file.is_open()){

      char buffer[256];

      // read line by line
      while(bitcoin_file.getline(buffer,256)){

        // get the username
        temp_ptr = strtok(buffer," ");
        char* initial_owner = (char*)malloc(sizeof(char)*(strlen(temp_ptr)+1));
        strcpy(initial_owner,temp_ptr);

        // check if the username is valid
        // if the Search returns a value different than NULL it means that the user is already in the system
        if(this->wallets->Search(temp_ptr)!=NULL){
          std::cout<<"Error the value "<<temp_ptr<<" is an invalid username and will not be inserted in the system"<<std::endl;
          continue;
        }

        // put him inside wallet,senders,receivers
        senders_receivers_data* new_sender = new senders_receivers_data(temp_ptr);
        senders_receivers_data* new_receiver = new senders_receivers_data(temp_ptr);
        Wallet_info* new_wallet = new Wallet_info(temp_ptr);
        this->senders->Insert(new_sender,new_sender->get_id());
        this->receivers->Insert(new_receiver,new_receiver->get_id());
        this->wallets->Insert(new_wallet,new_wallet->get_wallet_id());

        // read each bitcoin in the line
        while (temp_ptr!=NULL){
          temp_ptr = strtok(NULL," ");
          //each time temp_ptr gets in the loop with the old value so we need to check its value after we get the string
          if(temp_ptr!=NULL){
            //check is the bicoin id is valid

            if(this->bitcoins_status->Search(temp_ptr)!=NULL){
              std::cout<<"Error the value "<<temp_ptr<<" is an invalid bitcoin id and will not be inserted in the system"<<std::endl;
              continue;
            }

            //the bitcoin is valid

            // this objects goes to the bicoin_status Hash_Table
            Bitcoin_Status* new_bitcoin_status =  new Bitcoin_Status(this->bitcoin_value,temp_ptr,initial_owner);
            // this object goes to the Bitcoin_list in the Wallets Hash Table
            Bitcoin_in_wallet* new_bitcoin_in_wallet = new Bitcoin_in_wallet(temp_ptr,this->bitcoin_value);
            // put bitcoin in the Bitcoin_Status Hash Table
            this->bitcoins_status->Insert(new_bitcoin_status,new_bitcoin_status->get_id());
            //put the bitcoin in the users wallet
            // get the list from the wallet
            List<Bitcoin_in_wallet*>* bitcoin_list = new_wallet->get_list();
            // put the bitcoin in the list;
            // the only duplicated info is the initial value of the bitcoin (which will change in the Wallet because it represents the amount the user has)
            bitcoin_list->Push(new_bitcoin_in_wallet);
          }
        }
        //free the string
        free(initial_owner);
      }
    }
    // close the file
    bitcoin_file.close();
  }



void Bitcoin_System::Begin_System() {
  //TODO:Do the UI method

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

void Bitcoin_System::Update_tree_and_wallets(Transaction_info* transaction_info,Wallet_info* sender_wallet,Wallet_info* receiver_wallet,char* bitcoin_id, int transaction_amount){

  //create the transaction in the tree of the bitcoin
  Bitcoin_Status* bitcoin_for_transaction = bitcoins_status->Search(bitcoin_id);
  bitcoin_for_transaction->New_Transaction(transaction_info,sender_wallet->get_wallet_id(),receiver_wallet->get_wallet_id(),transaction_amount);


  //update the senders and the receivers wallet and also the status of the bitcoin involved
  sender_wallet->update_bitcoin_amount(bitcoin_id,(-transaction_amount));
  receiver_wallet->update_bitcoin_amount(bitcoin_id,transaction_amount);

}


void Bitcoin_System::Request_Transaction(char* transaction_id,char* sender_id,char* receiver_id,int& amount,int& day,int& mounth,int& year,int& hour,int& minute) {

  //---1.Validation---//

  //check if the transaction_id is valid
  if((this->transactions->Search(transaction_id))!=NULL) {
    std::cout<<"Invalid Transaction Id"<<std::endl;
    return;
  }
  //check if the sender and the receiver actually exist
  // get a pointer to each wallet to avoid searching all the time
  Wallet_info* senders_wallet = this->wallets->Search(sender_id);
  Wallet_info* receivers_wallet = this->wallets->Search(receiver_id);

  if(senders_wallet==NULL||receivers_wallet==NULL){
    std::cout<<"Invalid sender or receiver id"<<std::endl;
    return;
  }
  //check if the sender actually has the money
  if(senders_wallet->get_total_money()<amount){
    std::cout<<"The sender does not have enough money to make the transaction"<<std::endl;
    return;
  }
  //check if the hour of the transaction is vallid
  //we compare it to the last transaction make which will be the head of our list
  List_node<Transaction_info*>* last_transaction =this->transactions->get_head();
  if(!(last_transaction->get_item()->is_after(year,mounth,day,hour,minute))){
    std::cout<<"invalid transaction date"<<std::endl;
  }



  //---2.Make the transaction info and connect it---//

  //put the transaction into the list and make the two hash_tables point to the transaction
  Transaction_info* new_transaction = new Transaction_info(sender_id,receiver_id,transaction_id,amount,year,mounth,day,hour,minute);
  this->transactions->Push(new_transaction);

  //connect the senders_hash_table
  senders_receivers_data* senders_data = this->senders->Search(sender_id);
  senders_data->Insert(new_transaction);
  //connect the receivers hash table
  senders_receivers_data* receivers_data = this->receivers->Search(receiver_id);
  receivers_data->Insert(new_transaction);




  //---3.Make the actual Transaction---//

  //-->check if the sender has a bitcoin that can make the transaction bu itself
  char* bitcoin_id = senders_wallet->Find_proper_bitcoin(amount);

  //there is such a bitcoin so we make the transaction
  if(bitcoin_id!=NULL){
    Update_tree_and_wallets(new_transaction,senders_wallet,receivers_wallet,bitcoin_id,amount);
  }


  else{


  }





}

