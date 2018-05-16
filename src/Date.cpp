#include <iostream>
#include "Date.hpp"
#include <stdio.h>
#include <sstream>
#include <iomanip>

using namespace std;

// default constructor
Date::Date() {
  m_year = 0;
  m_month = 0;
  m_day = 0;
  m_hour = 0;
  m_minute = 0;
}

// constructor
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
  m_year = t_year;
  m_month = t_month;
  m_day = t_day;
  m_hour = t_hour;
  m_minute = t_minute;
}

// constructor with a string
Date::Date(const std::string &dateString) {

	if (dateString.size() != 16) {
		m_year = 0;
  		m_month = 0;
  		m_day = 0;
  		m_hour = 0;
  		m_minute = 0;
	}
	else if (dateString[4] != '-' || dateString[7] != '-' || dateString[10] != '/' || dateString[13] != ':') {
		m_year = 0;
  		m_month = 0;
  		m_day = 0;
  		m_hour = 0;
  		m_minute = 0;
	}
	else {

		char *str = (char *)dateString.data();

		sscanf(str, "%d-%d-%d/%d:%d", &m_year, &m_month, &m_day, &m_hour, &m_minute);
		//sscanf(str, "\"%d-%d-%d/%d:%d\"", &m_year, &m_month, &m_day, &m_hour, &m_minute);
		Date tmp(m_year, m_month, m_day, m_hour, m_minute);

		if (!isValid(tmp)) {
			m_year = 0;
  			m_month = 0;
  			m_day = 0;
  			m_hour = 0;
  			m_minute = 0;		
		}
		//delete[] str;		
	}

}

int Date::getYear(void) const {
	return m_year;
}

void Date::setYear(const int t_year) {
	m_year = t_year;
}

int Date::getMonth(void) const {
	return m_month;
}

void Date::setMonth(const int t_month) {
	m_month = t_month;
}

int Date::getDay(void) const {
	return m_day;
}

void Date::setDay(const int t_day) {
	m_day = t_day;
}

int Date::getHour(void) const {
	return m_hour;
}

void Date::setHour(const int t_hour) {
	m_hour = t_hour;
}

int Date::getMinute(void) const {
	return m_minute;
}

void Date::setMinute(const int t_minute) {
	m_minute = t_minute;
}

bool Date::isValid(const Date &t_date) {

	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ( (t_date.getYear() % 4 == 0 && t_date.getYear() % 100 != 0) || (t_date.getYear() % 400 == 0) )
		daysInMonth[1] = 29;

	if (t_date.getYear() < 1000 || t_date.getYear() >= 10000)
		return false;
	
	if (t_date.getMonth() < 1 || t_date.getMonth() > 12)
		return false;
		
	if (t_date.getDay() < 1 || t_date.getDay() > daysInMonth[t_date.getMonth() - 1]) {
		//cout << "!!!" << endl;
		return false;
	}
	
	if (t_date.getHour() < 0 || t_date.getHour() > 23) 
		return false;
	
	if (t_date.getMinute() < 0 || t_date.getMinute() > 59)
		return false;
	
	return true;
}

Date Date::stringToDate(const std::string &t_dateString) {

	if (t_dateString.size() != 16)
		return Date("0000-00-00/00:00");

	if (t_dateString[4] != '-' || t_dateString[7] != '-' || t_dateString[10] != '/' || t_dateString[13] != ':')
		return Date("0000-00-00/00:00");
 
	Date temp(t_dateString);
	if (isValid(temp))
		return temp;
	return Date("0000-00-00/00:00");
}

std::string Date::dateToString(const Date &t_date) {

	if (!isValid(t_date))
		return "0000-00-00/00:00";

	stringstream t_str;
	t_str << setw(4) << setfill('0') << t_date.m_year << "-" << setw(2) << setfill('0') << t_date.m_month << "-" << setw(2) << setfill('0') << t_date.m_day 
	<< "/" << setw(2) << setfill('0') << t_date.m_hour << ":" << setw(2) << setfill('0') << t_date.m_minute;

	string tmp = t_str.str();
	return tmp;
}

Date &Date::operator=(const Date &t_date) {
	m_year = t_date.m_year;
	m_month = t_date.m_month;
	m_day = t_date.m_day;
	m_hour = t_date.m_hour;
	m_minute = t_date.m_minute;
	return *this;
}

bool Date::operator==(const Date &t_date) const {

	if (m_year != t_date.m_year)
		return false;
	else {
		if (m_month != t_date.m_month)
			return false;
		else {
			if (m_day != t_date.m_day)
				return false;
			else {
				if (m_hour != t_date.m_hour)
					return false;
				else {
					if (m_minute != t_date.m_minute)
						return false;
					else 
						return true;
				}
			}
		}
	}

}

bool Date::operator>(const Date &t_date) const {

	if(m_year > t_date.m_year) {
		return true;
	}
	else if (m_year < t_date.m_year) {
		return false;
	}
	else {
		if (m_month > t_date.m_month) {
			return true;
		}
		else if (m_month < t_date.m_month)
			return false;
		else {
			if (m_day > t_date.m_day)
				return true;
			else if (m_day < t_date.m_day)
				return false;
			else {
				if (m_hour > t_date.m_hour)
					return true;
				else if (m_hour < t_date.m_hour)
					return false;
				else {
					if (m_minute > t_date.m_minute)
						return true;
					else
						return false;
				}
			}
		}
	}

}

bool Date::operator<(const Date &t_date) const {
	if (*this > t_date || *this == t_date)
		return false;
	return true;
}

bool Date::operator>=(const Date &t_date) const {
	if (*this > t_date || *this == t_date)
		return true;
	return false;
}

bool Date::operator<=(const Date &t_date) const {
	if (*this > t_date)
		return false;
	return true;
}
