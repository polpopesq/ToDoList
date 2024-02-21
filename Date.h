#pragma once
#include <iostream>

using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(int day, int month, int year);
	Date(string stringDate);
	string getDate() const;
	void setDate(string stringDate);
	void setDate(int day, int month, int year);
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	void setCurrentDate();
	Date& operator=(string stringDate);
	friend ostream& operator<<(ostream& out, Date d);
	friend istream& operator>>(istream& in, Date& d);
	void deserialize(ifstream& f);
	void serialize(ofstream& f);
};

class DateAndTime : public Date
{
private:
	int hour;
	int minute;
public:
	DateAndTime();
	void setCurrentClock();
	void setClock(int hour, int minute);
	void setHour(int hour);
	void setMinute(int minute);
	int getHour();
	int getMinute();
	void setDateTime(int day, int month, int year, int hour, int minute);

	DateAndTime& operator=(Date d);
	void deserialize(ifstream& f);
	void serialize(ofstream& f);
	friend ostream& operator<<(ostream& out, DateAndTime dt);
	friend istream& operator>>(istream& in, DateAndTime& dt);

};