#include "Date.h"
#include <iostream>


//===CONSTRUCTOR==//

Date::Date(int year,int month,int day,int hour,int minute):year(year),month(month),day(day),minutes(minute),hour(hour){
}

//==FUNCTIONALITY==//

bool Date::is_after(int& year, int & month, int & day,int& hour,int& minutes){

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


void Date::Print_date() {
  std::cout<<this->day<<"-"<<this->month<<"-"<<this->year<<" "<<this->hour<<":"<<this->minutes;
}

