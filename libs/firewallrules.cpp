#include "firewallrules.hpp"


std::istream &operator>>(std::istream &is, FirewallRules &rules) {

    int internal, external;
    is >> internal;
    is >> external;

    FirewallRule rule(internal, external);
    if (rules.contains(rule)) {
        throw std::runtime_error("duplicate firewall rule");
    }

    rules.rules.push_back(rule);

    return is;
}
