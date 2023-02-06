#include "outputdnsreversev6.hpp"

#include "../util.hpp"

void OutputDNSReversev6::write(std::ostream& os, MachinePtrConst m, const MachineVect& mvect) const {
    // 1.0.0.0.1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0         PTR             c1.k21a.mrwski.eu.

    os << m->get_ipv6().get_reverse_dns(64) << "        PTR        ";
    os << m->get_fqdn() << "." << std::endl;
}
