#pragma once

#include <vector>
#include <string>

class IPv6 {

    std::string original;
    std::vector<std::string> groups;

    void parse(const std::string &ip6);

public:
    IPv6() = default;
    IPv6(const std::string& ip6)
        : original(ip6) { parse(ip6); }

    std::string get_reverse_dns(int mask) const;
    const std::string& get_group(int idx) const { return groups[idx]; }
    const std::string& get_original() const { return original; }

    friend std::ostream& operator<<(std::ostream& os, const IPv6& ip6);
};
