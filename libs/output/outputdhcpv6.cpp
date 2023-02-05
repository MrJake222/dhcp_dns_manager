#include "outputdhcpv6.hpp"

#include "../util.hpp"

void OutputDHCPv6::write(std::ostream& os, MachinePtrConst m, const MachineVect& mvect) const {

    if (m->has_flag("nov6"))
        return;

    if (m->has_flag("static"))
        return;

    // host NorbertPC { hardware ethernet 4C:CC:6A:22:AA:9F; fixed-address6 fd00::1; }
    os << "host " << pad(m->get_name(), mvect.get_name_max_len() + 1) << " { ";
    os << "hardware ethernet " << m->get_mac() << "; ";
    os << "fixed-address6 " << m->get_ipv6() << "; ";
    os << "}" << std::endl;
}
