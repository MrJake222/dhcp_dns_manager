#pragma once

#include <istream>
#include <vector>
#include <set>
#include <algorithm>

class FirewallRule {

    int internal_port;
    int external_port;   // v4-only, 0 if not enabled

public:
    int get_internal_port() const { return internal_port; }
    int get_external_port() const { return external_port; }
    bool should_pass_v4_external() const { return external_port != 0; }

    FirewallRule(int internal, int external)
        : internal_port(internal)
        , external_port(external) { }

    bool operator==(const FirewallRule& other) const {
        return internal_port == other.internal_port &&
               external_port == other.external_port;
    }
};

class FirewallRules {
    // TODO add std::set for faster duplicate detection
    std::vector<FirewallRule> rules;

    bool contains(FirewallRule& rule) const {
        return std::find(rules.begin(), rules.end(), rule) != rules.end();
    }

public:
    FirewallRules() = default;
    FirewallRules(const FirewallRules& other) = delete;
    FirewallRules(FirewallRules&& other) = default;


    size_t size() const { return rules.size(); }
    std::vector<FirewallRule>::const_iterator begin() const { return rules.cbegin(); }
    std::vector<FirewallRule>::const_iterator end() const { return rules.cend(); }
    const FirewallRule& operator[](std::size_t idx) const { return rules[idx]; }

    // adds one firewall rule
    friend std::istream& operator>>(std::istream& is, FirewallRules& rules);
};
