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
    is >> machine.ipv6;
    to_lower_str(machine.ipv6);
    machine.ipv6 = machine.v6_prefix + machine.ipv6;

    if (is.eof()) machine.failed_exception("name");
    is >> machine.name;

    if (!is.eof()) {
        is >> machine.flags;
    }

    return is;
}



