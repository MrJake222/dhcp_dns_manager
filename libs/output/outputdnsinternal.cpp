#include "outputdnsinternal.hpp"

#include "../util.hpp"

void OutputDNSInternal::write(std::ostream &os, MachinePtrConst m, const MachineVect& mvect) const {
    // LAPTOP-CO9OHV8O		A	192.168.1.179
    os << pad(m->get_name(), mvect.get_name_max_len() + 4);
    os << "A       ";
    os << m->get_ipv4();
    os << std::endl;

    if (!m->has_flag("nov6")) {
        os << pad(m->get_name(), mvect.get_name_max_len() + 4);
        os << "AAAA    ";
        os << m->get_ipv6();
        os << std::endl;
    }
}