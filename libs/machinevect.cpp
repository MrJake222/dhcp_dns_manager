#include "machinevect.hpp"

#include "util.hpp"
#include <sstream>
#include <functional>

#include <iostream>
using std::cout;
using std::endl;

void read_file_line_by_line(const std::string& path, const std::function<void(std::stringstream)>& parse_line) {

    std::ifstream file(path);
    if (file.fail()) {
        throw std::runtime_error("failed to open file " + path);
    }

    std::string line;
    size_t line_no = 0;
    while (std::getline(file, line)) {
        line_no++;
        strip_comment(line);
        trim(line);

        if (line.empty())
            continue;

        try {
            parse_line(std::stringstream(line));
        }
        catch (const std::runtime_error& err) {
            cout << path << ", line " << line_no << ": " << err.what() << endl;
            throw err;
        }
    }

    file.close();
}

void MachineVect::parse_machine_file(const std::string& path) {

    mac_set.clear();
    mvect.clear();
    name_map.clear();

    name_max_len = 0;

    read_file_line_by_line(path, [this](std::stringstream line_stream) {
        MachinePtr machine(new Machine(v4_prefix, v6_prefix));

        line_stream >> *machine;
        // eof can happen for malformed input
        // if this happens we don't catch anything just bubble up the exception

        if (!machine->has_flag("static")) {
            if (mac_set.count(machine->get_mac())) {
                throw std::runtime_error("duplicate mac address");
            }

            mac_set.insert(machine->get_mac());
        }

        if (name_map.count(machine->get_name())) {
            throw std::runtime_error("duplicate name");
        }

        mvect.push_back(machine);
        name_map[machine->get_name()] = machine;
        name_max_len = std::max(name_max_len, machine->get_name().length());
    });
}

void MachineVect::parse_firewall_file(const std::string &path) {

    per_proto_external_ports.clear();

    read_file_line_by_line(path, [this](std::stringstream line_stream) {
        std::string name;
        line_stream >> name;

        if (name_map.count(name) == 0) {
            throw std::runtime_error("no such hostname to add firewall rule");
        }

        MachinePtr m = name_map.at(name);
        FirewallRule new_rule = m->parse_rule(line_stream);

        std::unordered_set<int>& external_ports = per_proto_external_ports[new_rule.get_protocol()];

        if (new_rule.should_pass_v4_external() && external_ports.count(new_rule.get_external_port()) > 0) {
            throw std::runtime_error("duplicate external v4 port, set to 0 to disable (v6-only accessible)");
        }
        external_ports.insert(new_rule.get_external_port());
    });
}
