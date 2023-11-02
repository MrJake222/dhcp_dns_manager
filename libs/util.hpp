#pragma once

#include <vector>
#include <string>
#include "machine.hpp"

void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);

std::string pad(const std::string& str, size_t to);
std::string zfill(const std::string& str, size_t to);
void strip_comment(std::string& str);
void to_lower_str(std::string& str);

void dns_record(std::ostream &os, const std::string& name, int name_max_len, const std::string& record_type, const std::string& value);