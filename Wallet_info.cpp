#include "Wallet_info.h"
#include <iostream>
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
List<Bitcoin_in_wallet*>* Wallet_info::get_list()  const{
  return this->bitcoins_owned;
}

char* Wallet_info::get_wallet_id() const {
  return this->wallet_id;
}

int Wallet_info::get_total_money() const {
  int total_money=0;
  //traverse the list and sum all the money
  List_node<Bitcoin_in_wallet*>* current = this->bitcoins_owned->get_head();
  while (current!=NULL){
    total_money += current->get_item()->get_value();
    current = current->get_next();
  }
  return total_money;
}


void Wallet_info::Print_all_bitcoins() {
  List_node<Bitcoin_in_wallet*>* current = bitcoins_owned->get_head();

  while (current!=NULL){
    std::cout<<"Bitcoin ID: "<<current->get_item()->get_id()<<"AMOUNT: "<<current->get_item()->get_value()<<std::endl;
    current = current->get_next();
  }
}


//==MUTATORS==//

void Wallet_info::update_bitcoin_amount(char *bitcoin_id, int amount) {
  Bitcoin_in_wallet* bitcoin = this->bitcoins_owned->Search(bitcoin_id);
  // the user does not have that bitcoin
  if(bitcoin==NULL){
    //give him that bitcoin
    bitcoin= new Bitcoin_in_wallet(bitcoin_id,amount);
    this->bitcoins_owned->Push(bitcoin);
    return;
  }
  // if it has the bitcoin update the amount
  bitcoin->update_value(amount);
  //if the user lost the bitcoin delete it from the list completely
  if(bitcoin->get_value()<=0)
    this->bitcoins_owned->Delete(bitcoin->get_id());
}


//===OPERATORS==//

bool Wallet_info::operator==(const char* id) {
  if(!strcmp(this->wallet_id,id))
    return true;
  else
    return false;
}


//===FUNCTIONALITY===//

//checks if there is a bitcoin that has cufficient ammount to make a transaction

char* Wallet_info::Find_proper_bitcoin(int& amount) {

  List_node<Bitcoin_in_wallet*>* current = this->bitcoins_owned->get_head();

  //traverse the list until you find a proper bitcoin and if you do return its id
  while (current!=NULL){
    if(current->get_item()->get_value()>=amount)
      return current->get_item()->get_id();
    else
      current=current->get_next();
  }
  // is no bitcoin can make the transaction by itself return NULL
  return NULL;

}