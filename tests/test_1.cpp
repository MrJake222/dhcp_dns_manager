#include <gtest/gtest.h>

#include "../libs/machine.hpp"
#include "../libs/machinevect.hpp"

#include <string>

TEST (ParserTest, TestSimple) {
    MachineVect mvect("192.168", "", "fd00");
    mvect.parse_machine_file("tests/test_1_simple.txt");
    ASSERT_EQ(mvect.size(), 1);
    ASSERT_EQ(mvect[0]->get_mac(), "11:22:33:aa:bb:cc");
    ASSERT_EQ(mvect[0]->get_ipv4(), "192.168.1.2");
    ASSERT_EQ(mvect[0]->get_ipv6(), "fd00::2d");
    ASSERT_EQ(mvect[0]->get_name(), "npc");
    ASSERT_TRUE(mvect[0]->has_flag("nosth"));
    ASSERT_TRUE(mvect[0]->has_flag("dosth"));
    ASSERT_FALSE(mvect[0]->has_flag("not-this-flag"));
}

TEST (ParserTest, TestDuplicate) {
    MachineVect mvect("192.168", "", "fd00");
    ASSERT_THROW({
        try {
            mvect.parse_machine_file("tests/test_1_duplicate.txt");
        } catch (const std::runtime_error& e) {
            ASSERT_STREQ(e.what(), "duplicate mac address");
            throw;
        }
    }, std::runtime_error);
}

TEST (ParserTest, TestDuplicateName) {
    MachineVect mvect("192.168", "", "fd00");
    ASSERT_THROW({
        try {
            mvect.parse_machine_file("tests/test_1_duplicate_name.txt");
        } catch (const std::runtime_error& e) {
            ASSERT_STREQ(e.what(), "duplicate name");
            throw;
        }
    }, std::runtime_error);
}

TEST (ParserTest, TestFlags) {
    MachineVect mvect("192.168", "", "fd00");
    mvect.parse_machine_file("tests/test_1_flags.txt");
    ASSERT_EQ(mvect.size(), 3);

    ASSERT_TRUE(mvect[0]->has_flag("dosth"));
    ASSERT_FALSE(mvect[0]->has_flag("nosth"));

    ASSERT_TRUE(mvect[1]->has_flag("dosth"));
    ASSERT_TRUE(mvect[1]->has_flag("nosth"));

    ASSERT_FALSE(mvect[2]->has_flag("dosth"));
    ASSERT_TRUE(mvect[2]->has_flag("nosth"));
}

TEST (ParserTest, TestNameMapping) {
    MachineVect mvect("192.168", "", "fd00");
    mvect.parse_machine_file("tests/test_1_names.txt");
    ASSERT_EQ(mvect.size(), 3);

    ASSERT_EQ(mvect.for_name("npca2")->get_ipv4(), "192.168.1.2");
    ASSERT_EQ(mvect.for_name("np6")->get_ipv4(), "192.168.1.6");
    ASSERT_EQ(mvect.for_name("npc7")->get_ipv4(), "192.168.1.7");
    ASSERT_EQ(mvect.get_name_max_len(), 5);
}

TEST (ParserTest, TestFormattingComments) {
    MachineVect mvect("192.168", "", "fd00");
    mvect.parse_machine_file("tests/test_1_formatting.txt");
    ASSERT_EQ(mvect.size(), 5);
}

TEST (ParserTest, TestNoMac) {
    MachineVect mvect("192.168", "", "fd00");
    mvect.parse_machine_file("tests/test_1_nomac.txt");
    ASSERT_EQ(mvect.size(), 5);
}

TEST (ParserTest, TestNoMacErr) {
    MachineVect mvect("192.168", "", "fd00");
    ASSERT_THROW({
        try {
            mvect.parse_machine_file("tests/test_1_nomac_err.txt");
        } catch (const std::runtime_error& e) {
            ASSERT_STREQ(e.what(), "duplicate mac address");
            throw;
        }
    }, std::runtime_error);
}