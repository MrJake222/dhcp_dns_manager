#pragma once

#include <set>
#include <string>
#include <istream>
#include <ostream>


class MachineFlags {

    std::set<std::string> flags;

public:
    bool has(const std::string& flag) const;

    friend std::istream& operator>>(std::istream& is, MachineFlags& flags);
    friend std::ostream& operator<<(std::ostream& os, const MachineFlags& flags);
};