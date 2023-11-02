#include "util.hpp"

#include <algorithm>
#include <cctype>
#include <locale>

// trim from start (in place)
void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

std::string pad(const std::string& str, size_t to) {
    std::string copy(str);
    while (copy.length() < to) {
        copy += " ";
    }

    return copy;
}

std::string zfill(const std::string& str, size_t to) {
    std::string copy(str);
    while (copy.length() < to) {
        copy = '0' + copy;
    }

    return copy;
}

void strip_comment(std::string& str) {
    size_t pos = str.find('#');
    if (pos != std::string::npos) {
        str.erase(pos);
    }
}

void to_lower_str(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
}

void dns_record(std::ostream &os, const std::string& name, int name_max_len, const std::string& record_type, const std::string& value) {
    // LAPTOP-CO9OHV8O		A	192.168.1.179
    os << pad(name, name_max_len + 4);
    os << record_type << "       ";
    os << value;
    os << std::endl;
}