#include <gtest/gtest.h>

#include "../libs/machine.hpp"
#include "../libs/machinevect.hpp"

TEST (FirewallTest, TestSimple) {
    MachineVect mvect("192.168", "", "fd00", "home.local");
    mvect.parse_machine_file("tests/hosts.txt");
    mvect.parse_firewall_file("tests/test_2_simple.txt");

    ASSERT_EQ(mvect.for_name("npc")->get_firewall_rules().size(), 1);
    ASSERT_EQ(mvect.for_name("mpc")->get_firewall_rules().size(), 1);
    ASSERT_EQ(mvect.for_name("npc")->get_firewall_rules()[0].get_internal_port(), 22);
    ASSERT_EQ(mvect.for_name("npc")->get_firewall_rules()[0].get_external_port(), 0);
    ASSERT_EQ(mvect.for_name("mpc")->get_firewall_rules()[0].get_internal_port(), 25565);
    ASSERT_EQ(mvect.for_name("mpc")->get_firewall_rules()[0].get_external_port(), 25565);
}

TEST (FirewallTest, TestMultipleProtocols) {
    MachineVect mvect("192.168", "", "fd00", "home.local");
    mvect.parse_machine_file("tests/hosts.txt");
    mvect.parse_firewall_file("tests/test_2_tcp_udp.txt");

    ASSERT_EQ(mvect.for_name("npc")->get_firewall_rules().size(), 3);
    ASSERT_EQ(mvect.for_name("mpc")->get_firewall_rules().size(), 3);
    ASSERT_EQ(mvect.for_name("npc")->get_firewall_rules()[0].get_protocol(), "tcp");
    ASSERT_EQ(mvect.for_name("npc")->get_firewall_rules()[1].get_protocol(), "udp");
    ASSERT_EQ(mvect.for_name("mpc")->get_firewall_rules()[0].get_protocol(), "tcp");
    ASSERT_EQ(mvect.for_name("mpc")->get_firewall_rules()[1].get_protocol(), "udp");
}

TEST (FirewallTest, TestDuplicateEntry) {
    MachineVect mvect("192.168", "", "fd00", "home.local");
    mvect.parse_machine_file("tests/hosts.txt");

    ASSERT_THROW({
        try {
            mvect.parse_firewall_file("tests/test_2_duplicate_entry.txt");
        } catch (const std::runtime_error& e) {
            ASSERT_STREQ(e.what(), "duplicate firewall rule");
            throw;
        }
    }, std::runtime_error);
}

TEST (FirewallTest, TestDuplicateGlobal) {
    MachineVect mvect("192.168", "", "fd00", "home.local");
    mvect.parse_machine_file("tests/hosts.txt");

    ASSERT_THROW({
        try {
            mvect.parse_firewall_file("tests/test_2_duplicate_global.txt");
        } catch (const std::runtime_error& e) {
            ASSERT_STREQ(e.what(), "duplicate external v4 port, set to 0 to disable (v6-only accessible)");
            throw;
        }
    }, std::runtime_error);
}

TEST (FirewallTest, TestNonexistingHosts) {
    MachineVect mvect("192.168", "", "fd00", "home.local");
    mvect.parse_machine_file("tests/hosts.txt");

    ASSERT_THROW({
        try {
            mvect.parse_firewall_file("tests/test_2_nonexisting_hosts.txt");
         } catch (const std::runtime_error& e) {
            ASSERT_STREQ(e.what(), "no such hostname to add firewall rule");
            throw;
        }
    }, std::runtime_error);
}