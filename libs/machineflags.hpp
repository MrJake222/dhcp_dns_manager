#pragma once

#include <map>
#include <vector>
#include <string>
#include <istream>
#include <ostream>


class MachineFlags {

    std::map<std::string, std::vector<std::string>> flags;

public:
    bool has(const std::string& flag) const;
    std::vector<std::string> get(const std::string& flag) const;

    friend std::istream& operator>>(std::istream& is, MachineFlags& flags);
    friend std::ostream& operator<<(std::ostream& os, const MachineFlags& flags);
};