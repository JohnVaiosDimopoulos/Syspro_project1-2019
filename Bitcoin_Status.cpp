#include "Bitcoin_Status.h"
#include "Hash_Table.h"
#include <cstring>
#include <cstdlib>

//==CONSTRACTOR-DESTRUCTOR==//

Bitcoin_Status::Bitcoin_Status(int initial_value, char* id,char* initial_owner):initial_value(initial_value),unspend_amount(initial_value) {
  this->bitcoin_id = (char*)malloc(sizeof(char)*(strlen(id)+1));
  strcpy(this->bitcoin_id,id);

  this->initial_owner= (char*)malloc(sizeof(char)*(strlen(initial_owner)+1));
  strcpy(this->initial_owner,initial_owner);

  transaction_tree = new Transaction_tree(this->initial_value,initial_owner);
}

Bitcoin_Status::~Bitcoin_Status() {
  free(bitcoin_id);
  free(initial_owner);
  delete transaction_tree;
}

//==ACCESSORS==//
Transaction_tree * Bitcoin_Status::get_transaction_tree() const {
  return this->transaction_tree;
}

int Bitcoin_Status::get_transactions_number() const {
  return this->transactions_number;
}

int Bitcoin_Status::get_unspend_amount() const {
  return this->unspend_amount;
}

int Bitcoin_Status::get_initial_value() const {
  return this->initial_value;
}

char* Bitcoin_Status::get_id() const {
  return this->bitcoin_id;
}

char* Bitcoin_Status::get_initial_owners_id() const {
  return this->initial_owner;
}

//==MUTATORS==//

void Bitcoin_Status::increase_transaction_number() {
  this->transactions_number++;
}

void Bitcoin_Status::update_unspend_amount(int& amount) {

  //if all the amount is spended we cant change it anymore
  if(this->unspend_amount > 0) {
    this->unspend_amount -= amount;
    // if it became less than 0 make it 0
    if(this->unspend_amount<0)
      this->unspend_amount=0;
  }

}


//==FUNCTIONALITY==//

void Bitcoin_Status::New_Transaction(Transaction_info* info,char* sender,char* receiver,int transaction_amount) {
  this->transaction_tree->New_Transaction(info,sender,receiver,transaction_amount);
}


void Bitcoin_Status::Print_Transactions(int bucket_size){

  // we need a hash_table to use it a blocked set for the transactions

  //first calculate the size of the table
  int table_size;
  if(transactions_number!=0){
    // we want 70% loading factor
    int entries_per_bucket = (bucket_size- (sizeof(Hash_Bucket<Transaction_info*>)+ sizeof(unsigned int)/ sizeof(Transaction_info*)));
    table_size = transactions_number/(0.7*entries_per_bucket);
    if(table_size==0)
      table_size=1;
  }
  else
    table_size = 1;

  //create the table
  Hash_Table<Transaction_info*>* visited = new Hash_Table<Transaction_info*>(bucket_size,table_size);
  //Print the transactions
  this->transaction_tree->Print_transactions(visited,this->transaction_tree->get_root());
  //Nullify the table and delete it
  visited->Nullify();
  delete visited;


}


//===OPPERATOR==//

bool Bitcoin_Status::operator==(const char *id) {
  if(!strcmp(this->bitcoin_id,id)){
    return true;
  } else
    return false;
}
