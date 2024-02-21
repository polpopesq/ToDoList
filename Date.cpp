#include "Date.h"
#include <chrono>
#include <ctime>
#include <fstream>

using namespace std;

Date::Date()
{
	try
	{
		setCurrentDate();
	}
	catch (exception e)
	{
		cerr << e.what();
	}
}
Date::Date(int day, int month, int year)
{
	if (day > 0 && day < 32 && month > 0 && month < 13 &&
		year > 1989 && year < 2151)
	{
		this->day = day;
		this->month = month;
		this->year = year;
	}
	else
	{
		try
		{
			setCurrentDate();
		}
		catch (exception e)
		{
			cerr << e.what();
		}
	}
}
Date::Date(string stringDate)
{
	int err = 0;
	int slashCounter = 0;
	for (int i = 0; i < stringDate.length(); i++)
	{
		if (stringDate[i] == '/')
		{
			slashCounter++;
		}
		else
		{
			if (stringDate[i] < '0' && stringDate[i] > '9')
			{
				err = 1;
			}
		}
	}
	if (slashCounter != 2)
	{
		err = 1;
	}

	int parser = 0;
	int day = 0;
	int month = 0;
	int year = 0;
	while (stringDate[parser] != '/')
	{
		day = day * 10 + (stringDate[parser] - '0');
		parser++;
	}
	parser++;
	if (day < 1 || day > 31)
	{
		err = 1;
	}
	while (stringDate[parser] != '/')
	{
		month = month * 10 + (stringDate[parser] - '0');
		parser++;
	}
	parser++;
	if (month < 1 || month > 12)
	{
		err = 1;
	}
	while (parser < stringDate.length())
	{
		year = year * 10 + (stringDate[parser] - '0');
		parser++;
	}
	if (year < 1990 || year > 2150)
	{
		err = 1;
	}
	if (err == 0)
	{
		this->day = day;
		this->month = month;
		this->year = year;
	}
	else
	{
		setCurrentDate();
	}
}
string Date::getDate() const
{
	int err = 0;
	if (day < 1 || day > 31)
	{
		err = 1;
	}
	if (month < 1 || month > 12)
	{
		err = 1;
	}
	if (year < 1900 || year > 2150)
	{
		err = 1;
	}
	if (month == 2 && day > 29)
	{
		err = 1;
	}
	if (err == 1)
	{
		return "Invalid date!";
	}
	string dateString = "";
	if (day < 10)
	{
		dateString += '0';
	}
	else
	{
		dateString += '0' + day / 10 % 10;
	}
	dateString += '0' + day % 10;

	dateString += '/';

	if (month < 10)
	{
		dateString += '0';
	}
	else
	{
		dateString += '0' + month / 10 % 10;
	}
	dateString += '0' + month % 10;

	dateString += '/';

	dateString += '0' + year / 1000 % 10;
	dateString += '0' + year / 100 % 10;
	dateString += '0' + year / 10 % 10;
	dateString += '0' + year % 10;

	return dateString;
}
void Date::setDate(string stringDate)
{
	int slashCounter = 0;
	for (int i = 0; i < stringDate.length(); i++)
	{
		if (stringDate[i] == '/')
		{
			slashCounter++;
		}
		else
		{
			if (stringDate[i] < '0' && stringDate[i] > '9')
			{
				throw exception("Setezi o data invalida!");
			}
		}
	}
	if (slashCounter != 2)
	{
		throw exception("Setezi o data invalida!");
	}

	int parser = 0;
	int day = 0;
	int month = 0;
	int year = 0;
	while (stringDate[parser] != '/')
	{
		day = day * 10 + (stringDate[parser] - '0');
		parser++;
	}
	parser++;
	if (day < 1 || day > 31)
	{
		throw exception("Setezi o data invalida!");
	}
	while (stringDate[parser] != '/')
	{
		month = month * 10 + (stringDate[parser] - '0');
		parser++;
	}
	parser++;
	if (month < 1 || month > 12)
	{
		throw exception("Setezi o data invalida!");
	}
	while (parser < stringDate.length())
	{
		year = year * 10 + (stringDate[parser] - '0');
		parser++;
	}
	if (year < 1990 || year > 2150)
	{
		throw exception("Setezi o data invalida!");
	}
	this->day = day;
	this->month = month;
	this->year = year;
}
void Date::setDate(int day, int month, int year)
{
	if (day > 0 && day < 32 && month > 0 && month < 13 &&
		year > 1989 && year < 2151)
	{
		this->day = day;
		this->month = month;
		this->year = year;
	}
	else
	{
		try
		{
			setCurrentDate();
		}
		catch (exception e)
		{
			cerr << e.what();
		}
	}
}
void Date::setDay(int day)
{
	if (day > 0 && day < 32)
	{
		this->day = day;
	}
}
void Date::setMonth(int month)
{
	if (month > 0 && month < 13)
	{
		this->month = month;
	}
}
void Date::setYear(int year)
{
	if (year > 1989 && year < 2151)
	{
		this->year = year;
	}
}
int Date::getDay() const
{
	return day;
}
int Date::getMonth() const
{
	return month;
}
int Date::getYear() const
{
	return year;
}
void Date::setCurrentDate()
{
	// Get the current time point
	chrono::system_clock::time_point now = chrono::system_clock::now();

	// Convert the time point to a time_t object
	time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// Convert the time_t object to a tm struct using localtime_s
	tm timeInfo;
	if (localtime_s(&timeInfo, &currentTime) == 0) {
		// Extract the day, month, and year from the tm struct
		day = timeInfo.tm_mday;
		month = timeInfo.tm_mon + 1; // Months are zero-based, so add 1
		year = timeInfo.tm_year + 1900; // Years since 1900
	}
	else {
		throw exception("Nu se poate seta data curenta!");
	}
}
Date& Date::operator=(string stringDate)
{
	try
	{
		this->setDate(stringDate);
	}
	catch (exception e)
	{
		cerr << e.what();
	}
	return *this;
}
ostream& operator<<(ostream& out, Date d)
{
	if (d.day < 10)
	{
		out << "0";
	}
	out << d.day << "/";
	if (d.month < 10)
	{
		out << "0";
	}
	out << d.month << "/" << d.year;
	return out;
}
istream& operator>>(istream& in, Date& d)
{
	int err = 0;
	int day;
	int month;
	int year;
	cout << "Ziua: ";
	in >> day;
	cout << "Luna: ";
	in >> month;
	cout << "Anul: ";
	in >> year;
	if (day < 1 || day > 31)
	{
		err = 1;
	}
	if (month < 1 || month > 12)
	{
		err = 1;
	}
	if (year < 1990 || year > 2150)
	{
		err = 1;
	}
	if (err == 0)
	{
		d.day = day;
		d.month = month;
		d.year = year;
	}
	else
	{
		throw exception("Data nu e citita bine!");
	}
	return in;
}
void Date::deserialize(ifstream& f)
{
	f.read((char*)&day, sizeof(day));
	f.read((char*)&month, sizeof(month));
	f.read((char*)&year, sizeof(year));
}
void Date::serialize(ofstream& f)
{
	f.write((char*)&day, sizeof(day));
	f.write((char*)&month, sizeof(month));
	f.write((char*)&year, sizeof(year));
}

DateAndTime::DateAndTime() : Date()
{
	try 
	{
		setCurrentClock();
	}
	catch (exception e)
	{
		cerr << e.what();
	}
}
void DateAndTime::setCurrentClock()
{
	auto now = chrono::system_clock::now();

	// Convert the time point to a time_t object
	time_t currentTime = chrono::system_clock::to_time_t(now);

	// Declare a tm struct to store the result
	tm localTime;

	// Use localtime_s for thread safety
	if (localtime_s(&localTime, &currentTime) == 0) {
		// Extract the hour and minute from the tm struct
		hour = localTime.tm_hour;
		minute = localTime.tm_min;
	}
	else {
		throw exception("Nu se poate seta ora curenta!");
	}
}
void DateAndTime::setClock(int hour, int minute)
{
	setHour(hour);
	setMinute(minute);
	if (this->hour != hour || this->minute != minute)
	{
		throw exception("Ceasul e gresit!");
	}
}
void DateAndTime::setHour(int hour)
{
	if (hour > -1 && hour < 25)
	{
		this->hour = hour;
	}
}
void DateAndTime::setMinute(int minute)
{
	if (minute > -1 && minute < 61)
	{
		this->minute = minute;
	}
}
int DateAndTime::getHour()
{
	return hour;
}
int DateAndTime::getMinute()
{
	return minute;
}
void DateAndTime::setDateTime(int day, int month, int year, int hour, int minute)
{
	if (day > 0 && day < 32 && month > 0 && month < 13 &&
		year > 1989 && year < 2151)
	{
		setDate(day, month, year);
	}
	else
	{
		try
		{
			setCurrentDate();
		}
		catch (exception e)
		{
			cerr << e.what();
		}
	}

	try 
	{
		setClock(hour, minute);
	}
	catch (exception e)
	{
		cerr << e.what();
	}
}
DateAndTime& DateAndTime::operator=(Date d)
{
	this->setDay(d.getDay());
	this->setMonth(d.getMonth());
	this->setYear(d.getYear());

	return *this;
}
ostream& operator<<(ostream& out, DateAndTime dt)
{
	out << (Date)dt;
	out << " ";
	if (dt.getHour() < 10)
	{
		out << "0";
	}
	out << dt.getHour() << ":";
	if (dt.getMinute() < 10)
	{
		out << "0";
	}
	out << dt.getMinute();
	return out;
}
istream& operator>>(istream& in, DateAndTime& dt) 
{
	in >> (Date&)dt;
	int err = 0;
	int hour, minute;
	cout << "Hour: ";
	in >> hour;
	cout << "Minute: ";
	in >> minute;
	if (hour > -1 && hour < 25 && minute > -1 && minute < 61)
	{
		dt.hour = hour;
		dt.minute = minute;
	}
	else
	{
		throw exception("Hour not read well!");
	}
	return in;
}
void DateAndTime::deserialize(ifstream& f)
{
	Date::deserialize(f);
	f.read((char*)&hour, sizeof(hour));
	f.read((char*)&minute, sizeof(minute));
}
void DateAndTime::serialize(ofstream& f)
{
	Date::serialize(f);
	f.write((char*)&hour, sizeof(hour));
	f.write((char*)&minute, sizeof(minute));
}