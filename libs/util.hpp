#pragma once

#include <string>

void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);

std::string pad(const std::string& str, size_t to);
std::string zfill(const std::string& str, size_t to);
void strip_comment(std::string& str);
void to_lower_str(std::string& str);