#pragma once
#include <string>
#include <ctime>

class Date {
private:
    int year;
    int month;
    int day;

public:
    Date();
    Date(int year, int month, int day);
    Date(const std::string& dateString); // "YYYY-MM-DD" format
    
    // Getters
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    
    // Setters
    void setYear(int year) { this->year = year; }
    void setMonth(int month) { this->month = month; }
    void setDay(int day) { this->day = day; }
    
    // Utility methods
    std::string toString() const;
    bool isValid() const;
    static Date getCurrentDate();
    
    // Operators
    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
};