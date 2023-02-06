#include "ipv6.hpp"

#include "util.hpp"

#include <iostream>
using std::cout;
using std::endl;

/*unsigned short hex_to_short(const std::string& hex) {

    unsigned short res = 0;

    for (char x : hex) {
        if (x >= 'a' && x <= 'f')
            x = x - 'a' + 10;
        else
            x -= '0';

        res *= 16;
        res += x;
    }

    return res;
}*/

void IPv6::parse(const std::string& ip6) {

    std::string current_group;

    int idx = 0;
    int expand_idx = -1;

    for (char x : ip6) {
        if (x == ':') {
            if (current_group.empty()) {
                // double :
                expand_idx = idx;
            }
            else {
                groups.push_back(zfill(current_group, 4));
                current_group.clear();
                idx++;
            }
        }
        else {
            current_group += x;
        }
    }

    groups.push_back(zfill(current_group, 4));

    while (groups.size() < 8) {
        groups.insert(groups.begin() + expand_idx, "0000");
    }

    /*for (std::string& grp : groups) {
        cout << grp << endl;
    }*/
}

std::string IPv6::get_reverse_dns(int mask) const {

    std::string out;

    for (int i=7; i>=0; i--) {
        for (int j=3; j>=0; j--) {
            out += groups[i][j];
            out += ".";

            if ((i*4 + j)*4 == mask)
                goto end;
        }
    }

end:
    out.pop_back(); // remove trailing dot

    return out;
}

std::ostream& operator<<(std::ostream &os, const IPv6 &ip6) {

    os << ip6.original;

    return os;
}
