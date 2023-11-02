#include "machineflags.hpp"

#include <sstream>
#include "util.hpp"

bool MachineFlags::has(const std::string& flag) const {
    return flags.count(flag) > 0;
}

std::vector<std::string> MachineFlags::get(const std::string& flag) const {
    return flags.at(flag);
}

std::istream& operator>>(std::istream& is, MachineFlags& flags) {

    std::string key;
    std::string value;
    while (std::getline(is, key, ',')) {
        trim(key);
        size_t t = key.find('=');

        if (t == std::string::npos) {
            // no delimiter
            value = "";
        }
        else {
            value = key.substr(t+1, std::string::npos);
            key = key.substr(0, t);
        }

        flags.flags[key].push_back(value);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const MachineFlags &flags) {

    os << "[";
    for (auto entry: flags.flags) {
        os << "<" << entry.first << "=";
        for (auto entry2: entry.second) {
            os << entry2 << ",";
        }
        os << ">,";
    }
    os << "]";

    return os;
}
