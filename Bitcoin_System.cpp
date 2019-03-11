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

void Bitcoin_System::Request_Transaction() {
  //TODO: after the tree is done implement the transaction method

}

