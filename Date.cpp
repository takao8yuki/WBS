#include "Date.h"
#include <sstream>
#include <iomanip>

// �f�t�H���g�R���X�g���N�^�i���݂̓��t�ɐݒ�j
Date::Date() {
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    year = timeinfo.tm_year + 1900;
    month = timeinfo.tm_mon + 1;
    day = timeinfo.tm_mday;
}

// �p�����[�^�t���R���X�g���N�^
Date::Date(int year, int month, int day) : year(year), month(month), day(day) {
    if (!isValid()) {
        // �����ȓ��t�̏ꍇ�͌��݂̓��t�ɐݒ�
        *this = getCurrentDate();
    }
}

// �����񂩂�̃R���X�g���N�^�iYYYY-MM-DD�`���j
Date::Date(const std::string& dateString) {
    std::istringstream iss(dateString);
    std::string token;
    
    // '-'�ŕ���
    if (std::getline(iss, token, '-')) {
        year = std::stoi(token);
    }
    if (std::getline(iss, token, '-')) {
        month = std::stoi(token);
    }
    if (std::getline(iss, token)) {
        day = std::stoi(token);
    }
    
    if (!isValid()) {
        *this = getCurrentDate();
    }
}

// ������`���ɕϊ�
std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << year << "-"
        << std::setw(2) << month << "-"
        << std::setw(2) << day;
    return oss.str();
}

// ���t�̑Ó������`�F�b�N
bool Date::isValid() const {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    // �����Ƃ̓����`�F�b�N
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // ���邤�N�̌v�Z
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeapYear && day <= 29) return true;
        if (!isLeapYear && day <= 28) return true;
        return false;
    }
    
    return day <= daysInMonth[month - 1];
}

// ���݂̓��t���擾
Date Date::getCurrentDate() {
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    return Date(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
}

// ���Z�q�̎���
bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator>(const Date& other) const {
    return other < *this;
}