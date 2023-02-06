#pragma once

#include <istream>
#include <utility>
#include <vector>
#include <set>
#include <algorithm>

class FirewallRule {

    int internal_port;
    int external_port;   // v4-only, 0 if not enabled
    std::string protocol;

public:
    int get_internal_port() const { return internal_port; }
    int get_external_port() const { return external_port; }
    bool should_pass_v4_external() const { return external_port != 0; }
    std::string get_protocol() const { return protocol; }

    FirewallRule(int internal, int external, std::string proto)
        : internal_port(internal)
        , external_port(external)
        , protocol(std::move(proto)) { }

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

    static void failed_exception(const std::string& field_name);

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
