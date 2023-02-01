#include "outputdhcpv6.hpp"

#include "../util.hpp"

void OutputDHCPv6::write(std::ostream& os, MachinePtrConst m, const MachineVect& mvect) const {

    if (m->has_flag("nov6"))
        return;

    // host NorbertPC { hardware ethernet 4C:CC:6A:22:AA:9F; fixed-address 192.168.1.2; }
    os << "host " << pad(m->get_name(), mvect.get_name_max_len() + 1) << " { ";
    os << "hardware ethernet " << m->get_mac() << "; ";
    os << "fixed-address " << m->get_ipv6() << "; "; // TODO probably another option
    os << "}" << std::endl;
}
