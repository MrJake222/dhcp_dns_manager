#pragma once

#include <string>
#include <vector>
#include <memory>

#include "machineflags.hpp"
#include "firewallrules.hpp"

class Machine {

    const std::string& v4_prefix;
    const std::string& v6_prefix;

    std::string mac;
    std::string ipv4;
    std::string ipv6;
    std::string name;
    MachineFlags flags;
    FirewallRules firewall_rules;

    static void failed_exception(const std::string& field_name);

public:
    Machine() = delete;
    Machine(const Machine& other) = delete;
    Machine(Machine&& other) = default;
    Machine(const std::string& v4_prefix_, const std::string& v6_prefix_)
        : v4_prefix(v4_prefix_)
        , v6_prefix(v6_prefix_) { }

    void print() const;

    std::string get_mac() const { return mac; }
    std::string get_ipv4() const { return ipv4; }
    std::string get_ipv6() const { return ipv6; }
    std::string get_name() const { return name; }
    bool has_flag(const std::string& flag) const { return flags.has(flag); }

    // return last added rule
    FirewallRule parse_rule(std::istream& is) { is >> firewall_rules; return firewall_rules[firewall_rules.size()-1]; }
    const FirewallRules& get_firewall_rules() const { return firewall_rules; }

    bool operator<(const Machine& rhs) const;
    friend bool operator==(const Machine& lhs, const Machine& rhs);
    friend std::istream& operator>>(std::istream& is, Machine& machine);
};

using MachinePtr = std::shared_ptr<Machine>;
using MachinePtrConst = std::shared_ptr<const Machine>;