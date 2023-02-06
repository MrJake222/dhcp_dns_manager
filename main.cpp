#include <iostream>
using std::cout;
using std::endl;

#include "libs/util.hpp"
#include "libs/machinevect.hpp"
#include "libs/output/outputdhcp.hpp"
#include "libs/output/outputdhcpv6.hpp"
#include "libs/output/outputdnsinternal.hpp"
#include "libs/output/outputdnsexternal.hpp"
#include "libs/output/outputnftables.hpp"
#include "libs/output/outputdnsreversev6.hpp"

void usage(char* pgm_name) {
    cout << "Usage: " << pgm_name << endl;
    cout << "\t[hosts file]" << endl;
    cout << "\t[firewall file]" << endl;
    cout << "\t[v4-prefix]" << endl;
    cout << "\t[v4-external]" << endl;
    cout << "\t[v6-prefix]" << endl;
    cout << "\t[domain]" << endl;
    cout << "\t[config to output: dhcp|dhcpv6|dnsint|dnsext|nftables|rev6]" << endl;
}

int main(int argc, char** argv) {

    if (argc != 8) {
        cout << "expected 7 arguments, " << argc-1 << " given." << endl;
        usage(argv[0]);
        return 1;
    }

    std::string hosts_file(argv[1]);
    std::string firewall_file(argv[2]);
    std::string v4_prefix(argv[3]);
    std::string v4_external(argv[4]);
    std::string v6_prefix(argv[5]);
    std::string domain(argv[6]);
    std::string config_to_output(argv[7]);

    to_lower_str(v6_prefix);

    MachineVect mvect(v4_prefix, v4_external, v6_prefix, domain);
    mvect.parse_machine_file(hosts_file);
    mvect.parse_firewall_file(firewall_file);

    if (config_to_output == "dhcp")             cout << OutputDHCP(mvect);
    else if (config_to_output == "dhcpv6")      cout << OutputDHCPv6(mvect);
    else if (config_to_output == "dnsint")      cout << OutputDNSInternal(mvect);
    else if (config_to_output == "dnsext")      cout << OutputDNSExternal(mvect);
    else if (config_to_output == "nftables")    cout << OutputNftables(mvect);
    else if (config_to_output == "rev6")        cout << OutputDNSReversev6(mvect);

    else {
        cout << "invalid [config to output]" << endl;
        usage(argv[0]);
        return 2;
    }
}
