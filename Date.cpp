#include "Date.h"
#include <iostream>


//===CONSTRUCTOR==//

Date::Date(int year,int month,int day,int hour,int minute):year(year),month(month),day(day),minutes(minute),hour(hour){
  //calc timestamp;
  struct tm tm;
  time_t rawtime;
  time(&rawtime);
  tm =*localtime(&rawtime);
  tm.tm_year=year-1900;
  tm.tm_mon =month-1;
  tm.tm_mday = day;
  tm.tm_hour=hour;
  tm.tm_min =minute;
  this->timestamp = mktime(&tm);

}

//==FUNCTIONALITY==//

bool Date::is_after(Date date){

  if(date.get_year()==0){
    // we compare only the times
    if(this->hour>date.hour)
      return true;
    else if(this->hour==date.hour){
      if(this->minutes>date.minutes)
        return true;
      else
        return false;
    }
    return false;
  }

  if(this->timestamp > date.timestamp)
    return true;
  else
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