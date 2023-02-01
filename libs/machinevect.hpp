#pragma once

#include "machine.hpp"
#include <unordered_set>
#include <map>
#include <utility>
#include <vector>
#include <fstream>
#include <string>

class MachineVect {

    const std::string v4_prefix;
    const std::string v4_external;

    const std::string v6_prefix;

    std::unordered_set<std::string> mac_set; // used for duplicate detection
    std::vector<MachinePtr> mvect;
    std::map<std::string, MachinePtr> name_map;
    size_t name_max_len = 0;

    std::unordered_set<int> external_ports;

public:
    MachineVect(std::string  v4_prefix_,
                std::string  v4_external_,
                std::string  v6_prefix_)
        : v4_prefix(std::move(v4_prefix_))
        , v4_external(std::move(v4_external_))
        , v6_prefix(std::move(v6_prefix_)) { }

    class const_iterator {
    private:
        std::vector<MachinePtr> mvect;
        size_t index;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type = MachinePtrConst;
        using pointer = MachinePtrConst*;
        using reference = MachinePtrConst&;
        using iterator_category = std::output_iterator_tag;

        const_iterator() : index(0) { }
        const_iterator(const std::vector<MachinePtr>& mvect_, size_t index_) : mvect(mvect_), index(index_) { }

        const_iterator& operator++() { index++; return *this; }                                 // prefix
        const_iterator operator++(int) { const_iterator tmp = *this; index++; return *this; };  // postfix
        bool operator!=(const const_iterator& other) const { return index != other.index; }
        MachinePtrConst operator*() const { return mvect[index]; }
    };

    void parse_machine_file(const std::string& path);
    void parse_firewall_file(const std::string& path);

    size_t size() const { return mvect.size(); }
    size_t get_name_max_len() const { return name_max_len; }
    const std::string& get_v4_external() const { return v4_external; }

    MachinePtrConst for_name(const std::string& name) const { return name_map.at(name); }

    const_iterator begin() const { return {mvect, 0}; }
    const_iterator end() const { return {mvect, size()}; }
    MachinePtrConst operator[](std::size_t idx) const { return mvect[idx]; }
};



