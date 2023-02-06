#include <gtest/gtest.h>

#include "../libs/machine.hpp"
#include "../libs/machinevect.hpp"

#include <string>

#include "../libs/ipv6.hpp"

TEST (v6_test, TestSimple) {
    IPv6 ip6("fe80:abcd:ea:125:fe80:123:3454:125");
    ASSERT_EQ(ip6.get_reverse_dns(64), "5.2.1.0.4.5.4.3.3.2.1.0.0.8.e.f");
}

TEST (v6_test, TestDouble) {
    IPv6 ip6("fe80::1");
    ASSERT_EQ(ip6.get_reverse_dns(64), "1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0");
}

TEST (v6_test, TestNet) {
    IPv6 ip6("fe80::");
    ASSERT_EQ(ip6.get_reverse_dns(64), "0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0");
}

TEST (v6_test, TestHostOtherMask) {
    IPv6 ip6("fe80::1");
    ASSERT_EQ(ip6.get_reverse_dns(48), "1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0");
    ASSERT_EQ(ip6.get_reverse_dns(56), "1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0");
}