#include "outputnftables.hpp"

#include "../util.hpp"

// TODO export this as configuration
const std::string FILTER_FORWARD = "inet filter FORWARD";
const std::string NAT_PREROUTING = "ip nat PREROUTING";

void OutputNftables::write(std::ostream& os, MachinePtrConst m, const MachineVect& mvect) const {

    for (const FirewallRule &rule: m->get_firewall_rules()) {

        if (!m->has_flag("nov6")) {
            // ipv6 forward rule
            // add rule inet filter forward ip6 daddr 2001:470:6166::1:1 tcp dport 22 accept
            os << "add rule " << FILTER_FORWARD << " ip6 daddr " << m->get_ipv6() << " " << rule.get_protocol() << " dport " << rule.get_internal_port() << " accept" << std::endl;
        }

        // ipv4 forward rule
        // add rule inet filter forward ip daddr 172.16.1.1 tcp dport 22 accept
        os << "add rule " << FILTER_FORWARD << " ip daddr " << m->get_ipv4() << " " << rule.get_protocol() << " dport " << rule.get_internal_port() << " accept" << std::endl;

        // ipv4 nat
        // add rule ip nat prerouting ip saddr != $INTERNAL tcp dport 222 dnat to 172.16.1.1:22
        if (rule.should_pass_v4_external()) {
            os << "add rule " << NAT_PREROUTING << " ip saddr != $INTERNAL " << rule.get_protocol() << " dport " << rule.get_external_port() << " dnat to " << m->get_ipv4() << ":" << rule.get_internal_port() << std::endl;
        }
    }
}
