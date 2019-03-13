#ifndef PROJECT1_VER3_DATE_H
#define PROJECT1_VER3_DATE_H

class Date {
 private:
  const int year;
  const int month;
  const int day;
  const int hour;
  const int minutes;
 public:
  //constructor
  Date(int year=0,int month=0,int day=0,int hour=0,int minute=0);

  //functionality
  bool is_after(int,int,int,int,int);
  bool is_after_time(Date date);
  bool is_after_date(Date date);
  void Print_date() const;

  //accessors
  int get_year() const;
  int get_month() const;
  int get_day() const;
  int get_hour() const;
  int get_minutes() const;

};

#endif //PROJECT1_VER3_DATE_H
