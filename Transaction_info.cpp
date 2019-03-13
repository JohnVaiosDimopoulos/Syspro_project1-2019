#include "Transaction_info.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

//====Constructor-Destructor====//

Transaction_info::Transaction_info(char* sender, char* receiver,char* transaction,int& amount, int& year, int& month, int& day,int& hour,int& minutes):amount(amount),date(year,month,day,hour,minutes){
  this->sender_id = (char*)malloc(sizeof(char)*(strlen(sender)+1));
  this->receiver_id = (char*)malloc(sizeof(char)*(strlen(receiver)+1));
  this->transaction_id = (char*)malloc(sizeof(char*)*(strlen(transaction)+1));
  strcpy(this->sender_id,sender);
  strcpy(this->receiver_id,receiver);
  strcpy(this->transaction_id,transaction);
}

Transaction_info::~Transaction_info() {
  free(this->sender_id);
  free(this->receiver_id);
  free(this->transaction_id);
}

//==ACCESSORS==//

char* Transaction_info::get_sender() {
  return this->sender_id;
}

char* Transaction_info::get_receiver() {
  return this->receiver_id;
}

int Transaction_info::get_amount() {
  return this->amount;
}

char* Transaction_info::get_transaction_id() {
  return this->transaction_id;
}


void Transaction_info::print_info() {
  std::cout<<"Transaction: "<<this->transaction_id<<" Sender: "<<this->sender_id<<" Receiver: "<<this->receiver_id<<" Amount: "<<this->amount<<"Date:";
  this->date.Print_date();
  std::cout<<std::endl;
}

//===OTHER==//

bool Transaction_info::is_after(int& year, int & month, int & day,int& hour,int& minutes){

  if(this->date.is_after(year,month,day,hour,minutes))
    return true;
  else
    return false;
}