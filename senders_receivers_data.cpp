#include "senders_receivers_data.h"
#include <cstring>
#include <cstdlib>

//==CONSTRUCTOR-DESTRUCTOR==//

senders_receivers_data::senders_receivers_data(char* id) {
  this->wallet_id = (char*)malloc(sizeof(char)*(strlen(id)+1));
  strcpy(this->wallet_id,id);
  transactions = new List<senders_receivers_list_data*>();
}

senders_receivers_data::~senders_receivers_data() {
  free(this->wallet_id);
  delete transactions;
}

//==ACCESSORS==//

char* senders_receivers_data::get_id() const {
  return this->wallet_id;
}


void senders_receivers_data::printList() {
  List_node<senders_receivers_list_data*>* current = transactions->get_head();
  while (current!=NULL){
    current->get_item()->get_info()->print_info();
    current = current->get_next();
  }
}


void senders_receivers_data::print_in_range_of_time(Date date1, Date date2) {

  List_node<senders_receivers_list_data*>* current = this->transactions->get_head();

  while (current!=NULL){
    if((current->get_item()->get_info()->get_date().is_after_time(date1)) && (date2.is_after_time(current->get_item()->get_info()->get_date())))
      current->get_item()->get_info()->print_info();
    current = current->get_next();
  }

}

void senders_receivers_data::print_in_range_of_date(Date date1, Date date2) {

  List_node<senders_receivers_list_data*>* current = this->transactions->get_head();

  while (current!=NULL){
    if((current->get_item()->get_info()->get_date().is_after_date(date1)) && (date2.is_after_date(current->get_item()->get_info()->get_date())))
      current->get_item()->get_info()->print_info();
    current = current->get_next();
  }

}

void senders_receivers_data::print_in_range_of_full_date(Date date1, Date date2) {
  List_node<senders_receivers_list_data*>* current = this->transactions->get_head();

  while (current!=NULL){
    Date temp = current->get_item()->get_info()->get_date();

    if((current->get_item()->get_info()->get_date().is_after(date1.get_year(),date1.get_month(),date1.get_day(),date1.get_hour(),date1.get_minutes())) && (date2.is_after(temp.get_year(),temp.get_month(),temp.get_day(),temp.get_hour(),temp.get_minutes())));
      current->get_item()->get_info()->print_info();
    current = current->get_next();
  }

}

//==FUNCTIONALITY==/

void senders_receivers_data::Insert(Transaction_info* transaction) {
  senders_receivers_list_data* entry = new senders_receivers_list_data(transaction);
  this->transactions->Push(entry);
}


//===OPPERATOR===/

bool senders_receivers_data::operator==(const char* id) {
  if(!strcmp(this->wallet_id,id))
    return true;
  else
    return false;

}