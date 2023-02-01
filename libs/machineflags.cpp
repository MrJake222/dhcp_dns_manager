#include "machineflags.hpp"

#include <sstream>
#include "util.hpp"

bool MachineFlags::has(const std::string& flag) const {
    return flags.count(flag) > 0;
}

std::istream& operator>>(std::istream& is, MachineFlags& flags) {

    std::string flag;
    while (std::getline(is, flag, ',')) {
        trim(flag);
        flags.flags.insert(flag);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const MachineFlags &flags) {

    os << "[";
    for (auto entry : flags.flags)
        os << entry << " ";
    os << "]";

    return os;
}
