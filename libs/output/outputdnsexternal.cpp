#include "outputdnsexternal.hpp"

#include "../util.hpp"

void OutputDNSExternal::write(std::ostream &os, MachinePtrConst m, const MachineVect& mvect) const {
    for (auto name : m->get_names())
        dns_record(os, name, mvect.get_name_max_len(), "A", mvect.get_v4_external());

    if (!m->has_flag("nov6")) {
        for (auto name : m->get_names())
            dns_record(os, name, mvect.get_name_max_len(), "AAAA", m->get_ipv6().get_original());
    }
}