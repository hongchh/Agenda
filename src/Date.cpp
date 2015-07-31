#include <string>
#include "Date.h"

Date::Date(): year_(0), month_(0), day_(0), hour_(0), minute_(0) {}

Date::Date(int y, int m, int d, int h, int mi): year_(y),
           month_(m), day_(d), hour_(h), minute_(mi) {}

int Date::getYear() const {
    return year_;
}

void Date::setYear(int year) {
    year_ = year;
}

int Date::getMonth() const {
    return month_;
}

void Date::setMonth(int month) {
    month_ = month;
}

int Date::getDay() const {
    return day_;
}

void Date::setDay(int day) {
    day_ = day;
}

int Date::getHour() const {
    return hour_;
}

void Date::setHour(int hour) {
    hour_ = hour;
}

int Date::getMinute() const {
    return minute_;
}

void Date::setMinute(int minute) {
    minute_ = minute;
}

bool Date::isValid(Date date) {
    int y = date.getYear();
    if (!(y >= 1000 && y <= 9999)) return false;
    int m = date.getMonth();
    int d = date.getDay();
    int h = date.getHour();
    int mi = date.getMinute();
    if (m == 1 || m == 3 || m == 5 || m == 7
        || m == 8 || m == 10 || m == 12) {
        return (d >= 1 && d <= 31 && h >= 0
                && h < 24 && mi >= 0 && mi < 60);
    } else if (m == 2) {
        if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) {
            return (d >= 1 && d <= 29 && h >= 0
                    && h < 24 && mi >= 0 && mi < 60);
        } else {
            return (d >= 1 && d <= 28 && h >= 0
                    && h < 24 && mi >= 0 && mi < 60);
        }
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        return (d >= 1 && d <= 30 && h >= 0
                && h < 24 && mi >= 0 && mi < 60);
    } else {
        return false;
    }
}

Date Date::stringToDate(std::string dateString) {
    int y = 0, m = 0, d = 0, h = 0, mi = 0;
    for (int i = 0; i < 4; ++i) y = y*10+(dateString[i]-'0');
    for (int i = 5; i < 7; ++i) m = m*10+(dateString[i]-'0');
    for (int i = 8; i < 10; ++i) d = d*10+(dateString[i]-'0');
    for (int i = 11; i < 13; ++i) h = h*10+(dateString[i]-'0');
    for (int i = 14; i < 16; ++i) mi = mi*10+(dateString[i]-'0');
    return Date(y, m, d, h, mi);
}

std::string Date::dateToString(Date date) {
    int y = date.getYear();
    int m = date.getMonth();
    int d = date.getDay();
    int h = date.getHour();
    int mi = date.getMinute();
    std::string dateString = "";
    int div[4] = {1000, 100, 10, 1};
    for (int i = 0; i < 4; ++i) {
        dateString += (y/div[i]+'0');
        y %= div[i];
    }
    dateString += '-';
    for (int i = 2; i < 4; ++i) {
        dateString += (m/div[i]+'0');
        m %= div[i];
    }
    dateString += '-';
    for (int i = 2; i < 4; ++i) {
        dateString += (d/div[i]+'0');
        d %= div[i];
    }
    dateString += '/';
    for (int i = 2; i < 4; ++i) {
        dateString += (h/div[i]+'0');
        h %= div[i];
    }
    dateString += ':';
    for (int i = 2; i < 4; ++i) {
        dateString += (mi/div[i]+'0');
        mi %= div[i];
    }
    return dateString;
}

Date& Date::operator=(const Date& date) {
    year_ = date.getYear();
    month_ = date.getMonth();
    day_ = date.getDay();
    hour_ = date.getHour();
    minute_ = date.getMinute();
    return *this;
}

bool Date::operator==(const Date& date) const {
    return (year_ == date.getYear() &&
            month_ == date.getMonth() &&
            day_ == date.getDay() &&
            hour_ == date.getHour() &&
            minute_ == date.getMinute());
}

bool Date::operator>(const Date& date) const {
    if (year_ > date.getYear()) {
        return true;
    } else if (year_ == date.getYear()) {
        if (month_ > date.getMonth()) {
            return true;
        } else if (month_ == date.getMonth()) {
            if (day_ > date.getDay()) {
                return true;
            } else if (day_ == date.getDay()) {
                if (hour_ > date.getHour()) {
                    return true;
                } else if (hour_ == date.getHour()) {
                    if (minute_ > date.getMinute()) return true;
                    else return false;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Date::operator<(const Date& date) const {
    return date > *this;
}

bool Date::operator>=(const Date& date) const {
    return (*this > date || *this == date);
}

bool Date::operator<=(const Date& date) const {
    return date >= *this;
}

