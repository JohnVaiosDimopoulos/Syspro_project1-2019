#include "Date.h"
#include <iostream>


//===CONSTRUCTOR==//

Date::Date(int year,int month,int day,int hour,int minute):year(year),month(month),day(day),minutes(minute),hour(hour){
}

//==FUNCTIONALITY==//

bool Date::is_after(int year, int month, int day,int hour,int minutes){

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

bool Date::is_after_date(Date date) {
  if(this->year<date.get_year())
    return true;
  else if(this->year==date.get_year()){
    //check month
    if(this->month<date.get_month())
      return true;
    else if(this->month==date.get_month()){
      //check day
      if(this->day<date.get_day())
        return true;
      else
        return false;
    } else
      return false;
  } else
    return false;
}

bool Date::is_after_time(Date date) {
  if(this->hour<date.get_hour())
    return true;
  else if(this->hour==date.get_hour()){
    if(this->minutes<date.minutes)
      return true;
    else
      return false;
  }
  return false;
}

void Date::Print_date() const {
  std::cout<<this->day<<"-"<<this->month<<"-"<<this->year<<" "<<this->hour<<":"<<this->minutes;
}

//===ACCESSORS==//

int Date::get_year() const {
  return this->year;
}

int Date::get_month() const {
  return this->month;
}

int Date::get_day() const {
  return this->day;
}

int Date::get_hour() const {
  return this->hour;
}

int Date::get_minutes() const {
  return this->minutes;
}