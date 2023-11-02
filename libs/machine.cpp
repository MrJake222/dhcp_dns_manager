#include "machine.hpp"

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
#include "util.hpp"
#include "machineflags.hpp"

void Machine::print() const {
    cout << "mac=" << mac << ", v4=" << ipv4 << ", v6=" << ipv6 << ", name=" << name << ", flags=" << flags << endl;
}

bool operator==(const Machine &lhs, const Machine &rhs) {
    // mac equality
    return lhs.mac == rhs.mac;
}

bool Machine::operator<(const Machine &rhs) const {
    // order by mac address
    return this->mac < rhs.mac;
}

void Machine::failed_exception(const std::string& field_name) {
    throw std::runtime_error("failed to read field \"" + field_name + "\"");
}

std::istream& operator>>(std::istream& is, Machine& machine) {
    if (is.eof()) machine.failed_exception("mac");
    is >> machine.mac;
    to_lower_str(machine.mac);

    if (is.eof()) machine.failed_exception("ipv4");
    is >> machine.ipv4;
    machine.ipv4 = machine.v4_prefix + machine.ipv4;

    if (is.eof()) machine.failed_exception("ipv6");
    std::string ipv6;
    is >> ipv6;
    to_lower_str(ipv6);
    machine.ipv6 = IPv6(machine.v6_prefix + ipv6);

    if (is.eof()) machine.failed_exception("name");
    is >> machine.name;
    machine.set_fqdn();

    if (!is.eof()) {
        is >> machine.flags;
    }

    return is;
}

std::vector<std::string> Machine::get_names() const {
    std::vector<std::string> names;
    names.push_back(get_name());
    if (has_flag("alias")) {
        std::copy(get_flag("alias").begin(), get_flag("alias").end(), names.end());
    }
    return names;
}



