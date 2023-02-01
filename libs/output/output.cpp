#include "output.hpp"

std::ostream &operator<<(std::ostream& os, const Output& out) {

    for (MachinePtrConst m : out.mvect) {
        out.write(os, m, out.mvect);
    }

    return os;
}




