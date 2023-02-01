#include "outputdnsexternal.hpp"

#include "../util.hpp"

void OutputDNSExternal::write(std::ostream &os, MachinePtrConst m, const MachineVect& mvect) const {
    // LAPTOP-CO9OHV8O		A	192.168.1.179
    os << pad(m->get_name(), mvect.get_name_max_len() + 4);
    os << "A       ";
    os << mvect.get_v4_external();
    os << std::endl;

    if (!m->has_flag("nov6")) {
        os << pad(m->get_name(), mvect.get_name_max_len() + 4);
        os << "AAAA    ";
        os << m->get_ipv6();
        os << std::endl;
    }
}