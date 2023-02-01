#include "outputiptables.hpp"

#include "../util.hpp"

void OutputIpTables::write(std::ostream& os, MachinePtrConst m, const MachineVect& mvect) const {
    // host NorbertPC { hardware ethernet 4C:CC:6A:22:AA:9F; fixed-address 192.168.1.2; }
//    os << "host " << pad(m->get_name(), mvect.get_name_max_len() + 1) << " { ";
//    os << "hardware ethernet " << m->get_mac() << "; ";
//    os << "fixed-address " << m->get_ipv4() << "; ";
//    os << "}" << std::endl;
    // TODO write iptables rules
}
