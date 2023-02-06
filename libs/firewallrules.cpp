#include "firewallrules.hpp"

void FirewallRules::failed_exception(const std::string& field_name) {
    throw std::runtime_error("failed to read field \"" + field_name + "\"");
}

std::istream &operator>>(std::istream &is, FirewallRules &rules) {

    int internal, external;
    std::string protocol;

    if (is.eof()) rules.failed_exception("internal");
    is >> internal;

    if (is.eof()) rules.failed_exception("external");
    is >> external;

    if (is.eof()) rules.failed_exception("protocol");
    is >> protocol;

    FirewallRule rule(internal, external, protocol);
    if (rules.contains(rule)) {
        throw std::runtime_error("duplicate firewall rule");
    }

    rules.rules.push_back(rule);

    return is;
}
