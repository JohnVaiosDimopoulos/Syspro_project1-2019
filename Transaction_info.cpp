#include "Transaction_info.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

//====Constructor-Destructor====//

Transaction_info::Transaction_info(char* sender, char* receiver,char* transaction,int& amount, int& year, int& month, int& day,int& hour,int& minutes):amount(amount),year(year),month(month),day(day),hour(hour),minutes(minutes){
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

int Transaction_info::get_year() {
  return this->year;
}

int Transaction_info::get_mounth() {
  return this->month;
}

int Transaction_info::get_day() {
  return this->day;
}

int Transaction_info::get_hour() {
  return this->hour;
}

int Transaction_info::get_minutes() {
  return this->minutes;
}

char* Transaction_info::get_transaction_id() {
  return this->transaction_id;
}


void Transaction_info::print_info() {
  std::cout<<"Transaction: "<<this->transaction_id<<" Sender: "<<this->sender_id<<" Receiver: "<<this->receiver_id<<" Amount: "<<this->amount<<"Date: "<<this->day<<"-"<<this->month<<"-"<<this->year<<" Time:"<<this->hour<<":"<<this->minutes<<std::endl;
}

//===OTHER==//

bool Transaction_info::is_after(int& year, int & month, int & day,int& hour,int& minutes){

  // compare the year
  if(this->year<year)
    // the input date is after the current one
    return true;
  else if(this->year==year){
    // we need to check month
    if(this->month<month)
      return true;
    else if(this->month == month){
      // we need to check day
      if(this->day<day)
        return true;
      else if(this->day == day){
        // we need to check hours
        if(this->hour<hour)
          return true;
          // we need to check minutes
        else if(this->hour==hour){
          if(this->minutes<minutes)
            return true;
          else
            return false;
        }else
          return false;
      }else
        return false;
    }else
      return false;
  }else
    return false;
}