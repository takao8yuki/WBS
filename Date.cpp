#include "Date.h"
#include <sstream>
#include <iomanip>

// デフォルトコンストラクタ（現在の日付に設定）
Date::Date() {
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    year = timeinfo.tm_year + 1900;
    month = timeinfo.tm_mon + 1;
    day = timeinfo.tm_mday;
}

// パラメータ付きコンストラクタ
Date::Date(int year, int month, int day) : year(year), month(month), day(day) {
    if (!isValid()) {
        // 無効な日付の場合は現在の日付に設定
        *this = getCurrentDate();
    }
}

// 文字列からのコンストラクタ（YYYY-MM-DD形式）
Date::Date(const std::string& dateString) {
    std::istringstream iss(dateString);
    std::string token;
    
    // '-'で分割
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

// 文字列形式に変換
std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << year << "-"
        << std::setw(2) << month << "-"
        << std::setw(2) << day;
    return oss.str();
}

// 日付の妥当性をチェック
bool Date::isValid() const {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    // 月ごとの日数チェック
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // うるう年の計算
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeapYear && day <= 29) return true;
        if (!isLeapYear && day <= 28) return true;
        return false;
    }
    
    return day <= daysInMonth[month - 1];
}

// 現在の日付を取得
Date Date::getCurrentDate() {
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    return Date(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
}

// 演算子の実装
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