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
  bool is_after(int&,int&,int&,int&,int&);
  void Print_date();

};

#endif //PROJECT1_VER3_DATE_H
